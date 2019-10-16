#ifndef TRANSLATE_DIALOG_H
#define TRANSLATE_DIALOG_H

#include <QDialog>

namespace Ui {
class Translate_dialog;
}

class Translate_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Translate_dialog(QWidget *parent = 0);
    ~Translate_dialog();

    void setTranslateRange(uint width, uint height, int x, int y);

    int translateX, translateY;

    bool from_ori;

private slots:
    void on_buttonBox_accepted();

    void on_y_slider_sliderMoved(int position);

    void on_x_slider_sliderMoved(int position);

    void on_from_ori_toggled(bool checked);

private:
    Ui::Translate_dialog *ui;
};

#endif // TRANSLATE_DIALOG_H
