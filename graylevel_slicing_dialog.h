#ifndef GRAYLEVEL_SLICING_DIALOG_H
#define GRAYLEVEL_SLICING_DIALOG_H

#include <QDialog>

namespace Ui {
class Graylevel_slicing_dialog;
}

class Graylevel_slicing_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Graylevel_slicing_dialog(QWidget *parent = 0);
    ~Graylevel_slicing_dialog();

    int start, end;
    bool preserve;

private slots:
    void on_left_valueChanged(int value);

    void on_right_valueChanged(int value);

    void on_radioButton_clicked(bool checked);

private:
    Ui::Graylevel_slicing_dialog *ui;
};

#endif // GRAYLEVEL_SLICING_DIALOG_H
