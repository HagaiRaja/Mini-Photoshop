#ifndef BRIGHTNESSSLIDER_H
#define BRIGHTNESSSLIDER_H

#include <QDialog>

namespace Ui {
class brightnessSlider;
}

class brightnessSlider : public QDialog
{
    Q_OBJECT

public:
    explicit brightnessSlider(QWidget *parent = nullptr);
    ~brightnessSlider();

    int value = 0;

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_buttonBox_accepted();

private:
    Ui::brightnessSlider *ui;
};

#endif // BRIGHTNESSSLIDER_H
