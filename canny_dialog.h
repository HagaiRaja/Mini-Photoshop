#ifndef CANNY_DIALOG_H
#define CANNY_DIALOG_H

#include <QDialog>

namespace Ui {
class Canny_dialog;
}

class Canny_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Canny_dialog(QWidget *parent = 0);
    ~Canny_dialog();
    int threshold;

private slots:
    void on_t_slider_valueChanged(int value);

private:
    Ui::Canny_dialog *ui;
};

#endif // CANNY_DIALOG_H
