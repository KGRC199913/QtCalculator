#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <QVector>
#include <QAction>

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
	bool isNotOperator = false;

	while (input.peek() != EOF) {
		std::getline(input, inputString, '\n');
		if (inputString.find_first_of('~') != std::string::npos)
			isNotOperator = true;
		else
			isNotOperator = false;

		qstr = QString::fromStdString(inputString);
		tokensList = qstr.split(" ");
		if (tokensList.size() == 3 && !isNotOperator)
		{
			if (tokensList[0] == "10" && tokensList[1] == "2")
				output << QInt(tokensList[2].toStdString()).to_binary_string() << std::endl;
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
				if (isDec){
					operand1 = QInt(tokensList[1].toStdString());
					operand2 = QInt(tokensList[3].toStdString());
				}

				if (tokensList[2] == "+")
					result = operand1 + operand2;
				if (tokensList[2] == "-")
					result = operand1 - operand2;
				if (tokensList[2] == "*")
					result = operand1 * operand2;
				if (tokensList[2] == "/")
					result = operand1 / operand2;
				if (tokensList[2] == "&")
					result = operand1 & operand2;
				if (tokensList[2] == "|")
					result = operand1 | operand2;
				if (tokensList[2] == "^")
					result = operand1 ^ operand2;
				if (tokensList[2] == "<<")
					result = operand1 << operand2;
				if (tokensList[2] == ">>")
					result = operand1 >> operand2;



				if (isDec)
					output << result << std::endl;
				if (isBin)
					output << result.to_binary_string() << std::endl;
				if (isHex)
					output << result.to_hex() << std::endl;
			}
			else {
				if (isNotOperator) {
					isBin = (tokensList[0] == "2");
					isDec = (tokensList[0] == "10");
					isHex = (tokensList[0] == "16");

					if (isBin) {
						output << ~QInt(BinStrToVectorBool(tokensList[2].toStdString())) << std::endl;
					}
					if (isHex) {
						output << ~QInt::HexToQint(tokensList[2].toStdString()) << std::endl;
					}
					if (isDec){
						output << ~QInt(tokensList[2].toStdString()) << std::endl;
					}
				}
			}
		}
	}
}
int main(int argc, char *argv[])
{
	if (argc == 1) {
		QApplication a(argc, argv);
		MainWindow window;
		window.show();
		return a.exec();
	}
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);
	HandleCommandlineArgs(input, output);

	return 0;
}
