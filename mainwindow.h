#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_MEM 10
#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>
#include <QKeyEvent>
#include <iostream>
#include <vector>
#include <QQueue>
#include <QStack>
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
    //Track History
    void TrackHistory();
    //Keyboard events
    //void keyPressEvent(QKeyEvent *event);
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
    std::vector<QString> ConvertToPostfix();
    QString Normalize(std::string x);

private:
    Ui::MainWindow *ui;
    bool plusTrigger = false, minusTrigger = false, mulTrigger = false, divTrigger = false;
    QString display_val = "";
    QQueue<QString> __history;
    std::vector<QString> Exp;
    QString result ="";
    int i = 0;
    int dot_count = 0;
    QString calculate();
};

#endif // MAINWINDOW_H
