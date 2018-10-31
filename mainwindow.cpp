#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint |Qt::WindowCloseButtonHint);
    ui->setupUi(this);   
    setMinimumSize(420,520);
    setStyleSheet("QMainWindow{ background-color: #333333 }");
    GroupDigitButtons();
    GroupCharButtons();
    GroupMathButton();
    //TrackHistory();
    on_RadBt_dec_toggled(true);
    //ConvertToPostfix();

    ui->BinScreen->setText(Normalize("1753109"));
}

QString MainWindow::Normalize(std::string x){
    QInt tempQInt(x);
    std::string binStr = tempQInt.to_binary_string();
    std::string part1 = binStr.substr(0, 32), part2 = binStr.substr(32, 32), part3 = binStr.substr(64, 32), part4 = binStr.substr(96, 32);
    int diff = 0;
    std::string space = "    ";
    for (int i = 4; i < 32; i = i + 4, ++++++++diff) {
        part1.insert(part1.begin() + i + diff, space.begin(), space.end());
        part2.insert(part2.begin() + i + diff, space.begin(), space.end());
        part3.insert(part3.begin() + i + diff, space.begin(), space.end());
        part4.insert(part4.begin() + i + diff, space.begin(), space.end());
    }

    std::string after = part1 + "\n\n" + part2 + "\n\n" + part3 + "\n\n" + part4;


    return QString::fromStdString(after);
}
void MainWindow::TrackHistory(){
    QQueue<QString> tempQueue;
    for(int i = 0; i<MAX_MEM; i++){
     //   __history.enqueue();
    }

    while (!__history.empty()) {
        ui->History->append(__history.front());
        tempQueue.enqueue(__history.dequeue());
    }

    while (!tempQueue.empty()) {
        __history.enqueue(tempQueue.dequeue());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Keyboard events

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
    if(op == "x" || op == "÷")
        return 3;
    else if(op == "+" || op == "-")
        return 1;
    return 0;
}

bool MainWindow::isOperator(QString op){
    return OperPriority(op);
}

std::vector<QString> MainWindow::ConvertToPostfix(){
    QStack <QString> ExpStack;
    std::vector<QString> number;
    for(auto iter = Exp.begin(); iter != Exp.end(); ++iter){
        if(isOperator(*iter)){
            number.emplace_back(*iter);
        } else if(*iter == '('){
            ExpStack.push(*iter);
        } else if(*iter == ')'){
            while(!ExpStack.empty() && ExpStack.top() != '('){
                number.emplace_back(ExpStack.pop());
            }
            if(!ExpStack.empty())
                throw new std::logic_error("wrong syntax");
        }
        else if(!ExpStack.empty() && OperPriority(*iter) >= OperPriority(ExpStack.top())){
            number.emplace_back(ExpStack.pop());
        }
    }
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
    QPushButton *button = static_cast<QPushButton *>(sender());
    display_val = display_val + button->text();
    ui->Screen->setText(display_val);
}

void MainWindow::Bt_digits_clicked(){
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
    display_val = "";
    dot_count = 0;
}

//math operations
void MainWindow::GroupMathButton(){
    connect(ui->Bt_plus, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_minus, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_multiply, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
    connect(ui->Bt_divide, SIGNAL(clicked()),this, SLOT(Bt_math_operators_clicked()));
}
void MainWindow::Bt_math_operators_clicked(){
    Exp.emplace_back(display_val);

    QPushButton *button = static_cast<QPushButton *>(sender());
    if(button->text() == "+")
        plusTrigger = true;
    if(button->text() == "-")
        minusTrigger = true;
    if(button->text() == "x")
        mulTrigger = true;
    if(button->text() == "÷")
        divTrigger = true;
    Exp.emplace_back(button->text());
    resetMemory();
    ui->History->append(Exp[i++]);
}

void MainWindow::on_Bt_plus_minus_clicked(){

}
void MainWindow::on_Bt_equals_clicked(){
    if(result == ""){

    }
    resetMemory();
    ui->Screen->setText(display_val);
}

void MainWindow::on_Bt_percent(){

}

//base
void MainWindow::on_RadBt_dec_toggled(bool checked)
{
    EnableAtoF(!checked);
}

void MainWindow::on_RadBt_bin_toggled(bool checked)
{
    EnableAtoF(!checked);
    Enable2to9(!checked);
    ui->Bt_dot->setEnabled(!checked);
}

void MainWindow::on_RadBt_hex_toggled(bool checked)
{
    EnableAtoF(checked);
    ui->Bt_dot->setEnabled(!checked);
}

//logical math
void MainWindow::on_Bt_and_clicked(){

}
void MainWindow::on_Bt_or_clicked(){

}
void MainWindow::on_Bt_xor_clicked(){

}
void MainWindow::on_Bt_not_clicked(){

}
void MainWindow::on_Bt_lsh_clicked(){

}
void MainWindow::on_Bt_rsh_clicked(){

}
void MainWindow::on_Bt_RoL_clicked(){

}
void MainWindow::on_Bt_RoR_clicked(){

}
//functional button
void MainWindow::on_Bt_mod_clicked(){

}

void MainWindow::on_Bt_erase_clicked(){
    resetMemory();
    ui->Screen->setText(display_val);
    //clear on-screen input but keep memory

}

void MainWindow::on_Bt_clear_clicked(){
    display_val = "";
    ui->Screen->setText(display_val);
    //clear screen and memory

}

void MainWindow::on_Bt_backspace_clicked(){
    if(display_val[display_val.length() - 1] == "."){
        dot_count = 0;
    }
        display_val.remove(display_val.length()-1, 1);
        ui->Screen->setText(display_val);
}

//Postfix conversion
