#include "translate_dialog.h"
#include "ui_translate_dialog.h"
#include <string>
using namespace std;

Translate_dialog::Translate_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Translate_dialog)
{
    ui->setupUi(this);
}

Translate_dialog::~Translate_dialog()
{
    delete ui;
}


void Translate_dialog::setTranslateRange(uint width, uint height, int x, int y) {
    ui->x_max->setText(QString(to_string(int(width)).c_str()));
    ui->x_val->setText(QString(to_string(x).c_str()));
    ui->x_min->setText(QString(to_string(-int(width)).c_str()));
    ui->y_max->setText(QString(to_string(int(height)).c_str()));
    ui->y_val->setText(QString(to_string(y).c_str()));
    ui->y_min->setText(QString(to_string(-int(height)).c_str()));
    ui->x_slider->setMaximum(int(width));
    ui->x_slider->setMinimum(-int(width));
    ui->x_slider->setValue(x);
    ui->y_slider->setMaximum(int(height));
    ui->y_slider->setMinimum(-int(height));
    ui->y_slider->setValue(y);
    translateX = x;
    translateY = y;
}

void Translate_dialog::on_buttonBox_accepted()
{
}

void Translate_dialog::on_y_slider_sliderMoved(int position)
{
    ui->y_val->setText(QString(to_string(position).c_str()));
    translateY = position;
}

void Translate_dialog::on_x_slider_sliderMoved(int position)
{
    ui->x_val->setText(QString(to_string(position).c_str()));
    translateX = position;
}

void Translate_dialog::on_from_ori_toggled(bool checked)
{
    from_ori = checked;
}
