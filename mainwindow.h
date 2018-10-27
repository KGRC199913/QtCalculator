#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>

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
    void on_Bt_digits_clicked();
    void on_Bt_0_clicked();
    void on_Bt_1_clicked();
    void on_Bt_2_clicked();
    void on_Bt_3_clicked();
    void on_Bt_4_clicked();
    void on_Bt_5_clicked();
    void on_Bt_6_clicked();
    void on_Bt_7_clicked();
    void on_Bt_8_clicked();
    void on_Bt_9_clicked();
    void on_Bt_A_clicked();
    void on_Bt_B_clicked();
    void on_Bt_C_clicked();
    void on_Bt_D_clicked();
    void on_Bt_E_clicked();
    void on_Bt_F_clicked();
    void on_Bt_dot_clicked();
    //math operations
    void on_Bt_plus_clicked();
    void on_Bt_minus_clicked();
    void on_Bt_multiply_clicked();
    void on_Bt_divide_clicked();
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
