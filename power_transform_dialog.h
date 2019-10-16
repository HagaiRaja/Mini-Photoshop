#ifndef POWER_TRANSFORM_DIALOG_H
#define POWER_TRANSFORM_DIALOG_H

#include <QDialog>

namespace Ui {
class Power_transform_dialog;
}

class Power_transform_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Power_transform_dialog(QWidget *parent = 0);
    ~Power_transform_dialog();

    double gamma;
    int constant;

private slots:
    void on_gamma_input_textChanged(const QString &arg1);

    void on_constant_input_textChanged(const QString &arg1);

private:
    Ui::Power_transform_dialog *ui;
};

#endif // POWER_TRANSFORM_DIALOG_H
