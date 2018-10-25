#include "mainwindow.h"
#include "ui_mainwindow.h"

QString value = "";
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

void AddToGroup(){

}
//Characters
void MainWindow::on_Bt_digits_clicked(){

}
void MainWindow::on_Bt_0_clicked(){
    value = value + "0";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_1_clicked()
{
    value = value + "1";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_2_clicked()
{
    value = value + "2";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_3_clicked(){
    value = value + "3";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_4_clicked(){
    value = value + "4";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_5_clicked(){
    value = value + "5";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_6_clicked(){
    value = value + "6";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_7_clicked(){
    value = value + "7";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_8_clicked(){
    value = value + "8";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_9_clicked(){
    value = value + "9";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_A_clicked(){
    value = value + "A";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_B_clicked(){
    value = value + "B";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_C_clicked(){
    value = value + "C";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_D_clicked(){
    value = value + "D";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_E_clicked(){
    value = value + "E";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_F_clicked(){
    value = value + "F";
    ui->Screen->setText(value);
}
void MainWindow::on_Bt_dot_clicked(){
    value = value + ".";
    ui->Screen->setText(value);
}
//math operations
void MainWindow::on_Bt_plus_clicked(){

}
void MainWindow::on_Bt_minus_clicked(){

}
void MainWindow::on_Bt_multiply_clicked(){

}
void MainWindow::on_Bt_divide_clicked(){

}
void MainWindow::on_Bt_plus_minus_clicked(){

}
void MainWindow::on_Bt_equals_clicked(){

}
void MainWindow::on_Bt_percent(){

}
//base
void MainWindow::on_Bt_dec_clicked(){

}
void MainWindow::on_Bt_bin_clicked(){

}
void MainWindow::on_Bt_hex_clicked(){

}
void MainWindow::on_Bt_oct_clicked(){

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
    value = "";
    ui->Screen->setText(value);
    //clear on-screen input but keep memory

}
void MainWindow::on_Bt_clear_clicked(){
    value = "";
    ui->Screen->setText(value);
    //clear screen and memory

}
void MainWindow::on_Bt_backspace_clicked(){
    value.remove(value.length()-1, 1);
    ui->Screen->setText(value);
}
