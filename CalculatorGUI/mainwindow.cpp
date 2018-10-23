#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(420,520);
    setStyleSheet("QMainWindow{ background-color: #333333 }");
}

MainWindow::~MainWindow()
{
    delete ui;
}


