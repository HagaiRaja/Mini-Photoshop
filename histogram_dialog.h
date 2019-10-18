#ifndef HISTOGRAM_DIALOG_H
#define HISTOGRAM_DIALOG_H

#include <QDialog>

namespace Ui {
class Histogram_dialog;
}

class Histogram_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Histogram_dialog(QWidget *parent = nullptr);
    ~Histogram_dialog();

    Histogram_dialog& operator =(const Histogram_dialog& h2);

    void drawHistogram(uint& type, uint colour);

    uint currGraylevel [3];
    uint highestPixelCount [3];
    uint pixelCount[3][256];
    uint type = 0; // 0 = Binary, 1 = Grayscale, 2 = Coloured

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Histogram_dialog *ui;
};

#endif // HISTOGRAM_DIALOG_H
