#include "brightnessslider.h"
#include "ui_brightnessslider.h"
#include <string>

using namespace std;

brightnessSlider::brightnessSlider(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::brightnessSlider)
{
    ui->setupUi(this);
}

brightnessSlider::~brightnessSlider()
{
    delete ui;
}

void brightnessSlider::on_horizontalSlider_sliderMoved(int position)
{
   ui->value->setText(QString(to_string(position).c_str()));
   value = position;
}

void brightnessSlider::on_buttonBox_accepted()
{

}
