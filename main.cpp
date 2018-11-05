#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <QVector>

std::vector<bool> BinStrToVectorBool(std::string binStr) {
    std::vector<bool> bits;
    for (auto ch : binStr) {
        bits.emplace(bits.begin(), ch - '0');
    }
    return bits;
}

void HandleCommandlineArgs(std::ifstream & input, std::ofstream & output) {
	std::string inputString;
	QString qstr;
	QStringList tokensList;
	bool isBin = 0, isDec = 0, isHex = 0;
	QInt operand1, operand2, result;

	while (input.peek() != EOF) {
		std::getline(input, inputString, '\n');
		qstr = QString::fromStdString(inputString);
		tokensList = qstr.split(" ");
		if (tokensList.size() == 3)
		{
			if (tokensList[0] == "10" && tokensList[1] == "2")
				output << QInt(tokensList[2].toStdString()) << std::endl;
			if (tokensList[0] == "2" && tokensList[1] == "10")
				output << QInt(BinStrToVectorBool(tokensList[2].toStdString())) << std::endl;
			if (tokensList[0] == "10" && tokensList[1] == "16")
				output << QInt(tokensList[2].toStdString()).to_hex() << std::endl;
			if (tokensList[0] == "16" && tokensList[1] == "10")
				output << QInt::HexToQint(tokensList[2].toStdString()) << std::endl;
			if (tokensList[0] == "2" && tokensList[1] == "16")
				output << QInt(BinStrToVectorBool(tokensList[2].toStdString())).to_hex() << std::endl;
			if (tokensList[0] == "16" && tokensList[1] == "2")
				output << QInt::HextoBin(tokensList[2].toStdString()) << std::endl;
		} else {
			if (tokensList.size() == 4) {
				isBin = (tokensList[0] == "2");
				isDec = (tokensList[0] == "10");
				isHex = (tokensList[0] == "16");
				if (isBin) {
					operand1 = QInt(BinStrToVectorBool(tokensList[1].toStdString()));
					operand2 = QInt(BinStrToVectorBool(tokensList[3].toStdString()));
				}
				if (isHex) {
					operand1 = QInt::HexToQint(tokensList[1].toStdString());
					operand2 = QInt::HexToQint(tokensList[3].toStdString());
				}

				if (tokensList[2] == "+")
					result = operand1 + operand2;
				if (tokensList[2] == "-")
					result = operand1 + operand2;
				if (tokensList[2] == "*")
					result = operand1 + operand2;
				if (tokensList[2] == "/")
					result = operand1 + operand2;
				if (tokensList[2] == "&")
					result = operand1 + operand2;
				if (tokensList[2] == "|")
					result = operand1 + operand2;
				if (tokensList[2] == "^")
					result = operand1 + operand2;
				if (tokensList[2] == "<<")
					result = operand1 + operand2;
				if (tokensList[2] == ">>")
					result = operand1 + operand2;
				// (tokensList[2] == "+") //PLACEHOLDER FOR ROR
					result = operand1 + operand2;
				//if (tokensList[2] == "+") //PLACEHOLDER FOR ROR
					result = operand1 + operand2;
				//if (tokensList[2] == "+") //PLACEHOLDER FOR NOT
					result = operand1 + operand2;
			}
		}
	}
}
int main(int argc, char *argv[])
{
    if (argc > 0) {
        QApplication a(argc, argv);
        MainWindow window;
        window.show();
        return a.exec();
    } else {

    }

}
