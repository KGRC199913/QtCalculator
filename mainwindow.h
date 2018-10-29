#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>
#include <QKeyEvent>
#include <iostream>
#include <vector>
#include <QStack>
#include "QInt.h"

#include "QInt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Characters
    void GroupDigitButtons();
    void GroupCharButtons();
    void Bt_digits_clicked();
    void Bt_chars_clicked();
    void on_Bt_dot_clicked();
    void resetMemory();
    //math operations
    void GroupMathButton();
    void Bt_math_operators_clicked();
    void on_Bt_plus_minus_clicked();
    void on_Bt_equals_clicked();
    void on_Bt_percent();
    //base
    void on_RadBt_dec_toggled(bool checked);
    void on_RadBt_bin_toggled(bool checked);
    void on_RadBt_hex_toggled(bool checked);
    //logical math
    void on_Bt_and_clicked();
    void on_Bt_or_clicked();
    void on_Bt_xor_clicked();
    void on_Bt_not_clicked();
    void on_Bt_lsh_clicked();
    void on_Bt_rsh_clicked();
    void on_Bt_RoL_clicked();
    void on_Bt_RoR_clicked();
    //functional button
    void on_Bt_mod_clicked();
    void on_Bt_erase_clicked();
    void on_Bt_clear_clicked();

    void on_Bt_backspace_clicked();

    void EnableAtoF(bool enable);
    void Enable2to9(bool enable);
    int OperPriority(QString op);
    bool isOperator(QString op);
    void ConvertToPostfix();

private:
    Ui::MainWindow *ui;
    bool plusTrigger = false, minusTrigger = false, mulTrigger = false, divTrigger = false;
    QString display_val = "";
    std::vector<QString> Exp;
    int i = 0;
    int dot_count = 0;
};

#endif // MAINWINDOW_H
