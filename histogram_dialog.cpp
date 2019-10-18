#include "histogram_dialog.h"
#include "ui_histogram_dialog.h"
#include <QtCharts>
#include <string>

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

    for (int i = 1; i<3; i++) {
        *pixelCountSet << i*500;
    }

    barChartSeries->append(pixelCountSet);

    QChart *chart = new QChart();
    chart->addSeries(barChartSeries);
    chart->setTitle("Image Histogram");

    QStringList categories;
    categories << "0" << "1";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    barChartSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,1000);
    chart->addAxis(axisY, Qt::AlignLeft);
    barChartSeries->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);
}

void Histogram_dialog::on_buttonBox_accepted()
{

}
