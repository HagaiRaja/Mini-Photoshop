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

void Histogram_dialog::drawHistogram() {
    QBarSeries *barChartSeries = new QBarSeries();

    QBarSet *pixelCountSet = new QBarSet("Pixel Count");

    for (int i = 0; i<256; i++) {
        *pixelCountSet << pixelCount[0][i];
        cout << "CountSet = " << pixelCount[0][i] << endl;
        fflush(stdout);
    }

    barChartSeries->append(pixelCountSet);

    QChart *chart = new QChart();
    chart->addSeries(barChartSeries);
    chart->setTitle("Image Histogram");

//    QStringList categories;

//    categories << "0" << "1" << "2" << "3" << "4";
//    for (int i = 0; i < 256; i++) {
//        std::ostringstream cat;
//        cat << i;
//        categories << cat.str().c_str();
//    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
    axisX->setRange("0","255");
    chart->addAxis(axisX, Qt::AlignBottom);
    barChartSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,highestPixelCount[0]);
    chart->addAxis(axisY, Qt::AlignLeft);
    barChartSeries->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);
}

void Histogram_dialog::on_buttonBox_accepted()
{

}
