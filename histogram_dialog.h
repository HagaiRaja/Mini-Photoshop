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

    void drawHistogram();

    int currGraylevel = 0;
    int highestPixelCount = 0;
    int pixelCount[3][256];
    int type; // 0 = Binary, 1 = Grayscale, 2 = Coloured

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Histogram_dialog *ui;
};

#endif // HISTOGRAM_DIALOG_H
