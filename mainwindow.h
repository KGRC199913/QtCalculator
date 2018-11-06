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
    //functional button
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
	int i = 0;
	int dot_count = 0;
    bool wasEqualClicked = false, wasOperatorClicked = false;
	bool isBin = false, isDec = false, isHex = false;
    bool wasRadBin = false, wasRadDec = false, wasRadHex = false;
    QString display_val = "";
    QQueue<QString> __history;
    std::vector<QString> Exp;
    QString calculate();
};

#endif // MAINWINDOW_H
