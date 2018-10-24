#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    setMinimumSize(420,520);
    setStyleSheet("QMainWindow{ background-color: #333333 }");
    ui->textBrowser_2->setText("nekoshotaiscutemeowmeowlovenekochan");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ui->textBrowser_2->setText(std::to_string(value).c_str());
}
