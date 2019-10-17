#include "contrast_stretching_dialog.h"
#include "ui_contrast_stretching_dialog.h"
#include <QtCharts>
#include <string>
using namespace std;

Contrast_stretching_dialog::Contrast_stretching_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contrast_stretching_dialog)
{
    ui->setupUi(this);

    drawChart();
}

void Contrast_stretching_dialog::drawChart() {
    QLineSeries *series = new QLineSeries();

    *series << QPointF(0, 0) << QPointF(double(x1), double(y1)) << QPointF(double(x2), double(y2)) << QPointF(255, 255);
//    *series << QPointF(0, 0) << QPointF(100, 50) << QPointF(200, 200) << QPointF(255, 255);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(gradient);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Grayscale level transformation");
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 255);
    chart->axisY()->setRange(0, 255);

    ui->chartView->setChart(chart);
}

Contrast_stretching_dialog::~Contrast_stretching_dialog()
{
    delete ui;
}

void Contrast_stretching_dialog::on_horizontalSlider_valueChanged(int value)
{
    if (ui->x2_slider->value() < value) ui->x2_slider->setValue(value);
    x1 = ui->horizontalSlider->value();
    x2 = ui->x2_slider->value();
    ui->X1_val->setText(QString(to_string(x1).c_str()));
    ui->X2_val->setText(QString(to_string(x2).c_str()));
    drawChart();
}

void Contrast_stretching_dialog::on_y1_slider_valueChanged(int value)
{
    if (ui->y2_slider->value() < value) ui->y2_slider->setValue(value);
    y1 = ui->y1_slider->value();
    y2 = ui->y2_slider->value();
    ui->Y1_val->setText(QString(to_string(y1).c_str()));
    ui->Y2_val->setText(QString(to_string(y2).c_str()));
    drawChart();
}

void Contrast_stretching_dialog::on_x2_slider_valueChanged(int value)
{
    if (ui->horizontalSlider->value() > value) ui->horizontalSlider->setValue(value);
    x1 = ui->horizontalSlider->value();
    x2 = ui->x2_slider->value();
    ui->X1_val->setText(QString(to_string(x1).c_str()));
    ui->X2_val->setText(QString(to_string(x2).c_str()));
    drawChart();
}

void Contrast_stretching_dialog::on_y2_slider_valueChanged(int value)
{
    if (ui->y1_slider->value() > value) ui->y1_slider->setValue(value);
    y1 = ui->y1_slider->value();
    y2 = ui->y2_slider->value();
    ui->Y1_val->setText(QString(to_string(y1).c_str()));
    ui->Y2_val->setText(QString(to_string(y2).c_str()));
    drawChart();
}

void Contrast_stretching_dialog::on_buttonBox_accepted()
{

}
