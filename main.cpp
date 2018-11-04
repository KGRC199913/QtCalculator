#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	if (argc > 0) {
		QApplication a(argc, argv);
		MainWindow window;
		window.show();
		return a.exec();
	} else {
		//TODO: input from commandline
	}

	//QInt x("6");
	//QInt y("3");
	//std::cout << (x / y) << std::endl;
}
