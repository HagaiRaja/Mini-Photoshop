#include "histogram_dialog.h"
#include "ui_histogram_dialog.h"
#include <QtCharts>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

Histogram_dialog::Histogram_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Histogram_dialog)
{
    ui->setupUi(this);

//    drawHistogram();
}

Histogram_dialog::~Histogram_dialog()
{
    delete ui;
}

void Histogram_dialog::drawHistogram(uint& type, uint colour) {
    int c = colour;

    QBarSeries *barChartSeries = new QBarSeries();

    QBarSet *pixelCountSet = new QBarSet("Pixel Count");

    double total = 0, n = 0;
    double variance = 0;
    for (int i = 0; i<256; i++) {
        if (type == 0) {
            if (i == 0 || i == 255) {
                *pixelCountSet << pixelCount[c][i];
            }
        }
        else {
            *pixelCountSet << pixelCount[c][i];
        }

        total += i * ((double) pixelCount[c][i]);
        n += double(pixelCount[c][i]);
    }

    double mean = total / n;

    for (int i = 0; i <256; i++) {
        variance += (((double)i)-mean) * (((double)i) - mean) * ((double) pixelCount[c][i]);
    }

    double sDeviasi = pow(variance, 0.5);

    barChartSeries->append(pixelCountSet);

    QChart *chart = new QChart();
    chart->addSeries(barChartSeries);
    chart->setTitle("Image Histogram");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
    if (type != 0) {
        axisX->setRange("0","255");
    }
    else {
        axisX->setRange("0","1");
    }
    chart->addAxis(axisX, Qt::AlignBottom);
    barChartSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,highestPixelCount[c]);
    chart->addAxis(axisY, Qt::AlignLeft);
    barChartSeries->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    if (c == 0) {
        ui->Hist_r->setChart(chart);
        ui->ValMean_r->setText(QString(to_string(mean).c_str()));
        ui->ValVariansi_r->setText(QString(to_string(variance).c_str()));
        ui->StdrD_r->setText(QString(to_string(sDeviasi).c_str()));

    }
    else if (c == 1) {
        ui->Hist_g->setChart(chart);
        ui->ValMean_g->setText(QString(to_string(mean).c_str()));
        ui->ValVariansi_g->setText(QString(to_string(variance).c_str()));
        ui->StdrD_g->setText(QString(to_string(sDeviasi).c_str()));
    }
    else {
        ui->Hist_b->setChart(chart);
        ui->ValMean_b->setText(QString(to_string(mean).c_str()));
        ui->ValVariansi_b->setText(QString(to_string(variance).c_str()));
        ui->StdrD_b->setText(QString(to_string(sDeviasi).c_str()));
    }

}

void Histogram_dialog::on_buttonBox_accepted()
{

}
