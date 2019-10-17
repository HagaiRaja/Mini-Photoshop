#ifndef CONTRAST_STRETCHING_DIALOG_H
#define CONTRAST_STRETCHING_DIALOG_H

#include <QDialog>

namespace Ui {
class Contrast_stretching_dialog;
}

class Contrast_stretching_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Contrast_stretching_dialog(QWidget *parent = 0);
    ~Contrast_stretching_dialog();
    void drawChart();

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_y1_slider_valueChanged(int value);

    void on_x2_slider_valueChanged(int value);

    void on_y2_slider_valueChanged(int value);

    void on_buttonBox_accepted();

private:
    Ui::Contrast_stretching_dialog *ui;
};

#endif // CONTRAST_STRETCHING_DIALOG_H
