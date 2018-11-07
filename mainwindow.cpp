#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint |Qt::WindowCloseButtonHint);
    ui->setupUi(this);

    setMinimumSize(420,520);
    setStyleSheet("QMainWindow{ background-color: #333333 }");
    QWidget::setWindowTitle("Calculator");
    GroupDigitButtons();
    GroupCharButtons();
    GroupMathButton();
    //TrackHistory();
    wasRadDec = true;
	ui->History->setAlignment(Qt::AlignRight);
	QInt loremIpsumVal("0");
    ui->BinScreen->setText(Normalize(loremIpsumVal.to_string()));
    ui->Bt_percent->setEnabled(false);
    ui->Bt_mod->setEnabled(false);
    ui->Bt_dot->setEnabled(false);
    ui->RadBt_bin->setEnabled(true);
    ui->RadBt_dec->setEnabled(true);
    ui->RadBt_hex->setEnabled(true);
    on_RadBt_dec_toggled(true);
}

QString MainWindow::Normalize(std::string x){
    QInt tempQInt(x);
    std::string binStr = tempQInt.to_binary_string();
    std::string part1 = binStr.substr(0, 32), part2 = binStr.substr(32, 32), part3 = binStr.substr(64, 32), part4 = binStr.substr(96, 32);
    int diff = 0;
    std::string space = "     ";
    for (int i = 4; i < 32; i = i + 4, diff = diff + 5) {
        part1.insert(part1.begin() + i + diff, space.begin(), space.end());
        part2.insert(part2.begin() + i + diff, space.begin(), space.end());
        part3.insert(part3.begin() + i + diff, space.begin(), space.end());
        part4.insert(part4.begin() + i + diff, space.begin(), space.end());
    }

    std::string after = part1 + "\n\n" + part2 + "\n\n" + part3 + "\n\n" + part4;


    return QString::fromStdString(after);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Set-enable Buttons
void MainWindow::EnableAtoF(bool enable){
    ui->Bt_A->setEnabled(enable);
    ui->Bt_B->setEnabled(enable);
    ui->Bt_C->setEnabled(enable);
    ui->Bt_D->setEnabled(enable);
    ui->Bt_E->setEnabled(enable);
    ui->Bt_F->setEnabled(enable);
}

void MainWindow::Enable2to9(bool enable){
    ui->Bt_2->setEnabled(enable);
    ui->Bt_3->setEnabled(enable);
    ui->Bt_4->setEnabled(enable);
    ui->Bt_5->setEnabled(enable);
    ui->Bt_6->setEnabled(enable);
    ui->Bt_7->setEnabled(enable);
    ui->Bt_8->setEnabled(enable);
    ui->Bt_9->setEnabled(enable);
    ui->Bt_dot->setEnabled(enable);
}

//Postfix Conversion
int MainWindow::OperPriority(QString op){
    if(op == "Not")
        return 7;
    if(op == "x" || op == "÷")
        return 6;
    if(op == "+" || op == "-")
        return 5;
    if(op == "Lsh" || op == "Rsh" || op == "RoR" || op == "RoL")
        return 4;
    if(op == "Xor")
        return 3;
    if(op == "And")
        return 2;
    if(op == "Or")
        return 1;
    return 0;
}

bool MainWindow::isOperator(QString op){
    return OperPriority(op);
}

std::vector<QString> MainWindow::ConvertToPostfix(){
    QStack <QString> ExpStack;
    std::vector<QString> number;
	for(auto iter = Exp.begin(); iter != Exp.end(); ++iter) {
        if(!isOperator(*iter)){
            number.emplace_back(*iter);
        } else if(*iter == '('){
            ExpStack.push(*iter);
        } else if(*iter == ')'){
            while(!ExpStack.empty() && ExpStack.top() != '('){
                number.emplace_back(ExpStack.pop());
                ExpStack.pop_back();
            }
            if(ExpStack.empty())
                throw new std::logic_error("wrong syntax");
        }
		else
			if (ExpStack.empty()){
				ExpStack.push(*iter);
			}
			else
                if(OperPriority(*iter) <= OperPriority(ExpStack.top())){
                    number.emplace_back(ExpStack.pop());
                    ExpStack.push(*iter);
                } else {
                    ExpStack.push(*iter);
                }
    }

    while(!ExpStack.empty())
        number.emplace_back(ExpStack.pop());

    return number;
}

//Characters 
void MainWindow::GroupDigitButtons(){
    QPushButton *DigitButton[10];
    for(int i = 0; i<10;i++){
        QString ButtonName = "Bt_" + QString::number(i);
        DigitButton[i] = MainWindow::findChild<QPushButton*>(ButtonName);
        connect(DigitButton[i], SIGNAL(clicked()), this, SLOT(Bt_digits_clicked()));
    }
}

void MainWindow::GroupCharButtons()
{
    connect(ui->Bt_A, SIGNAL(clicked()),this,SLOT(Bt_chars_clicked()));
    connect(ui->Bt_B, SIGNAL(clicked()),this,SLOT(Bt_chars_clicked()));
    connect(ui->Bt_C, SIGNAL(clicked()),this,SLOT(Bt_chars_clicked()));
    connect(ui->Bt_D, SIGNAL(clicked()),this,SLOT(Bt_chars_clicked()));
    connect(ui->Bt_E, SIGNAL(clicked()),this,SLOT(Bt_chars_clicked()));
    connect(ui->Bt_F, SIGNAL(clicked()),this,SLOT(Bt_chars_clicked()));
}

void MainWindow::Bt_chars_clicked(){
	if (wasEqualClicked) {
		display_val = "";
		Exp.clear();
		wasEqualClicked = false;
		i = 0;
	}
    ui->RadBt_bin->setEnabled(ui->RadBt_bin->isChecked());
    ui->RadBt_dec->setEnabled(ui->RadBt_dec->isChecked());
    ui->RadBt_hex->setEnabled(ui->RadBt_hex->isChecked());
    wasOperatorClicked = false;
    QPushButton *button = static_cast<QPushButton *>(sender());
    display_val = display_val + button->text();
    ui->Screen->setText(display_val);
	QInt intToNormalize;
	intToNormalize = QInt::HexToQint(display_val.toStdString());
	ui->BinScreen->setText(Normalize(intToNormalize.to_string()));
}

void MainWindow::Bt_digits_clicked(){
	if (wasEqualClicked) {
		display_val = "";
		Exp.clear();
		wasEqualClicked = false;
		i = 0;
	}

	isBin = ui->RadBt_bin->isChecked();
	isDec = ui->RadBt_dec->isChecked();
	isHex = ui->RadBt_hex->isChecked();

    ui->RadBt_bin->setEnabled(ui->RadBt_bin->isChecked());
    ui->RadBt_dec->setEnabled(ui->RadBt_dec->isChecked());
    ui->RadBt_hex->setEnabled(ui->RadBt_hex->isChecked());

    wasOperatorClicked = false;
	QPushButton *button = static_cast<QPushButton *>(sender());
    if(display_val.toDouble() < DBL_EPSILON && display_val.length() < 2 && !ui->RadBt_bin->isChecked())
    {
        ui->Screen->setText(button->text());
        display_val = button->text();
    }
    else{
        display_val = display_val + button->text();
        ui->Screen->setText(display_val);
    }

	QInt intToNormalize;
	if (isBin) {
		intToNormalize = QInt(BinStrToVectorBool(display_val.toStdString()));
		ui->BinScreen->setText(Normalize(intToNormalize.to_string()));
	}
	if (isDec) {
		ui->BinScreen->setText(Normalize(display_val.toStdString()));
	}
	if (isHex) {
		intToNormalize = QInt::HexToQint(display_val.toStdString());
		ui->BinScreen->setText(Normalize(intToNormalize.to_string()));
	}
}

void MainWindow::on_Bt_dot_clicked(){
    if(dot_count == 1)
        return;
    if(display_val.toDouble() < DBL_EPSILON){
        display_val = display_val + "0";
        display_val = display_val + ".";
    }
    else{
        display_val = display_val + ".";
    }
    ui->Screen->setText(display_val);
    dot_count = 1;
}

void MainWindow::resetMemory(){
    Exp.resize(0);
    display_val = "";
    dot_count = i = 0;
	wasEqualClicked = false;
    ui->RadBt_bin->setEnabled(true);
    ui->RadBt_dec->setEnabled(true);
    ui->RadBt_hex->setEnabled(true);
    ui->BinScreen->setText(Normalize(QInt("0").to_binary_string()));
}

//math operations
void MainWindow::GroupMathButton(){
    connect(ui->Bt_plus, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_minus, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_multiply, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_divide, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_and, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_or, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_xor, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_lsh, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_rsh, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_RoR, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_RoL, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
}
void MainWindow::Bt_math_operators_clicked(){
	wasEqualClicked = false;
    if(wasOperatorClicked)
        return;
    wasOperatorClicked = true;
	if(display_val == "" && Exp.size() == 0){
        return;
    }
    else{
        QPushButton *button = static_cast<QPushButton *>(sender());
		if (display_val != "")
			Exp.emplace_back(display_val);
        Exp.emplace_back(button->text());
        display_val = "";
        dot_count = 0;
        ui->History->append(Exp[i]);
        ui->History->append(Exp[++i]);
        i++;
    }
}

void MainWindow::on_Bt_plus_minus_clicked(){
	if (wasOperatorClicked)
		return;
	if (display_val == "" || display_val == "0"){
        return;
	}

	isBin = ui->RadBt_bin->isChecked();
	isDec = ui->RadBt_dec->isChecked();
	isHex = ui->RadBt_hex->isChecked();

	if (isBin) {
		QInt tempQInt(BinStrToVectorBool(display_val.toStdString()));
		tempQInt.to2ndComplement();
		display_val = QString::fromStdString(tempQInt.to_binary_string());
		ui->Screen->setText(display_val);
		ui->BinScreen->setText(Normalize(tempQInt.to_string()));
	} else {
		if(isHex) {
			QInt tempQInt = QInt::HexToQint(display_val.toStdString());
			tempQInt.to2ndComplement();
			display_val = QString::fromStdString(tempQInt.to_hex());
			ui->Screen->setText(display_val);
			ui->BinScreen->setText(Normalize(tempQInt.to_string()));
		}
		else {
			if (display_val[0] != '-')
			{
				display_val.prepend("-");
				ui->Screen->setText(display_val);
				ui->BinScreen->setText(Normalize(QInt(display_val.toStdString()).to_string()));
			}
			else {
				display_val.remove(0,1);
				ui->Screen->setText(display_val);
				ui->BinScreen->setText(Normalize(QInt(display_val.toStdString()).to_string()));
			}
		}
	}
}

void MainWindow::on_Bt_equals_clicked(){
    isBin = false; isDec = false; isHex = false;
    QInt tempVar;

    wasEqualClicked = true;
    wasOperatorClicked = false;
    ui->RadBt_bin->setEnabled(true);
    ui->RadBt_dec->setEnabled(true);
    ui->RadBt_hex->setEnabled(true);

    if (Exp.size() == 0 && display_val != "") {
        isBin = ui->RadBt_bin->isChecked();
        isDec = ui->RadBt_dec->isChecked();
        isHex = ui->RadBt_hex->isChecked();
        Exp.resize(0);
        ui->History->append("_____________\n");
        ui->History->append(display_val);
        ui->Screen->setText(display_val);
        if (isDec)
            tempVar = QInt(display_val.toStdString());
        if (isBin)
            tempVar = QInt(BinStrToVectorBool(display_val.toStdString()));
        if (isHex)
            tempVar = QInt::HexToQint(display_val.toStdString());
        ui->BinScreen->setText(this->Normalize(tempVar.to_string()));
        Exp.emplace_back(display_val);
        i = 1;
        ui->History->append("\n------------------------------\n");
        return;
    }

    if(display_val == "" && Exp.empty())
        return;
    else{
        isBin = ui->RadBt_bin->isChecked();
        isDec = ui->RadBt_dec->isChecked();
        isHex = ui->RadBt_hex->isChecked();
        Exp.emplace_back(display_val);
        display_val = "";
        dot_count = 0;
        ui->Screen->setText(display_val);
        ui->History->append(Exp[i]);
        i++;
		if(Exp.size() > 1)
            Exp = ConvertToPostfix();

        QStack<QString> EvalueStack;
		std::string res;
		QInt operand_1;
		QInt operand_2;

        for(auto iter = Exp.begin(); iter != Exp.end(); ++iter){
            if(!isOperator(*iter))
                EvalueStack.push(*iter);
            else{
                if (isDec) {
                    operand_1 = QInt(EvalueStack.pop().toStdString());
                    operand_2 = QInt(EvalueStack.pop().toStdString());
                }

                if (isBin) {
                    operand_1 = QInt(BinStrToVectorBool(EvalueStack.pop().toStdString()));
                    operand_2 = QInt(BinStrToVectorBool(EvalueStack.pop().toStdString()));
                }

                if (isHex) {
                    operand_1 = QInt::HexToQint(EvalueStack.pop().toStdString());
                    operand_2 = QInt::HexToQint(EvalueStack.pop().toStdString());
                }
                if(*iter == "+"){
                    res = (operand_1 + operand_2).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "-"){
					res = (operand_2 - operand_1).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "x"){
                    res = (operand_1 * operand_2).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "÷"){
					res = (operand_2 / operand_1).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "And"){
                    res = (operand_1 & operand_2).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "Or"){
                    res = (operand_1 | operand_2).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "Xor"){
                    res = (operand_1 ^ operand_2).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "Lsh"){
					res = (operand_2 << operand_1).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "Rsh"){
					res = (operand_2 >> operand_1).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "RoR"){
					res = (operand_2.ror(operand_1)).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
                if(*iter == "RoL"){
					res = (operand_2.rol(operand_1)).to_string();
                    EvalueStack.push_back(QString::fromStdString(res));
                }
				EvalueStack.pop();
                tempVar = QInt(res);
                if (isDec)
                    display_val = QString::fromStdString(res);
                if (isBin)
                    display_val = QString::fromStdString(QInt(res).to_binary_string());
                if (isHex)
                    display_val = QString::fromStdString(QInt(res).to_hex());
                EvalueStack.push(display_val);
            }
        }
    }
    Exp.resize(0);
	ui->History->append("_____________\n");
    ui->History->append(display_val);
    ui->Screen->setText(display_val);
    ui->BinScreen->setText(this->Normalize(tempVar.to_string()));

	Exp.emplace_back(display_val);
    i = 1;
	ui->History->append("\n------------------------------\n");
}

void MainWindow::on_Bt_percent(){
    if(display_val == "")
        return;
    QInt tempQInt(display_val.toStdString());
    std::string percent = (tempQInt /= 100).to_string();
    ui->Screen->setText(QString::fromStdString(percent));
}

//base
void MainWindow::on_RadBt_dec_toggled(bool checked)
{
    EnableAtoF(!checked);
    ui->RadBt_bin->setEnabled(!checked);
    ui->RadBt_hex->setEnabled(!checked);

    QInt tempQInt;
    if (wasRadBin)
        tempQInt = QInt(BinStrToVectorBool(display_val.toStdString()));
    if (wasRadHex)
        tempQInt = QInt::HexToQint(display_val.toStdString());
    wasRadDec = true;
    wasRadBin = wasRadHex = false;

    ui->Screen->setText(QString::fromStdString(tempQInt.to_string()));
}

void MainWindow::on_RadBt_bin_toggled(bool checked)
{
    EnableAtoF(!checked);
    Enable2to9(!checked);

    ui->RadBt_dec->setEnabled(!checked);
    ui->RadBt_hex->setEnabled(!checked);
    ui->Bt_dot->setEnabled(!checked);
    QInt tempQInt;

    std::string bin = tempQInt.to_binary_string();
    ui->Screen->setText(QString::fromStdString(bin));
    ui->BinScreen->setText(Normalize(bin));
;}

void MainWindow::on_RadBt_hex_toggled(bool checked)
{
    EnableAtoF(checked);

    ui->RadBt_bin->setEnabled(!checked);
    ui->RadBt_dec->setEnabled(!checked);
    ui->Bt_dot->setEnabled(!checked);
    QInt tempQInt(display_val.toStdString());
    std::string hex = tempQInt.to_hex();
    ui->Screen->setText(QString::fromStdString(hex));
}

//functional buttons

void MainWindow::on_Bt_erase_clicked(){
    resetMemory();
    ui->Screen->setText(display_val);
    //clear on-screen input but keep memory

}

void MainWindow::on_Bt_clear_clicked(){
    resetMemory();
    ui->Screen->setText(display_val);
    //clear screen and memory

}

void MainWindow::on_Bt_backspace_clicked(){
    if(display_val.length() == 0)
        return;

    if(display_val[display_val.length() - 1] == "."){
        dot_count = 0;
    }
    display_val.remove(display_val.length()-1, 1);
    ui->Screen->setText(display_val);
}

void MainWindow::on_Bt_not_clicked()
{
    if (display_val.length() == 0 || wasOperatorClicked)
        return;
    isBin = ui->RadBt_bin->isChecked();
    isDec = ui->RadBt_dec->isChecked();
    isHex = ui->RadBt_hex->isChecked();

    if (isBin) {
        QInt tempQInt(BinStrToVectorBool(display_val.toStdString()));
        tempQInt = ~tempQInt;
        display_val = QString::fromStdString(tempQInt.to_binary_string());
        ui->Screen->setText(display_val);
        ui->BinScreen->setText(Normalize(tempQInt.to_string()));
    } else {
        if(isHex) {
            QInt tempQInt = QInt::HexToQint(display_val.toStdString());
            tempQInt = ~tempQInt;
            display_val = QString::fromStdString(tempQInt.to_hex());
            ui->Screen->setText(display_val);
            ui->BinScreen->setText(Normalize(tempQInt.to_string()));
        }
        else {
            QInt tempQInt(display_val.toStdString());
            tempQInt = ~tempQInt;
            display_val = QString::fromStdString(tempQInt.to_string());
            ui->Screen->setText(display_val);
            ui->BinScreen->setText(Normalize(tempQInt.to_string()));
        }
    }
}
