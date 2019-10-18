#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QMdiArea>
#include <QLabel>
#include <QSlider>
#include <QDialogButtonBox>
#include "image.h"
using namespace std;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionNegative_triggered();

    void on_actionGrayscale_triggered();

    void on_actionFlip_Vertical_triggered();

    void on_actionFlip_Horizontal_triggered();

    void on_actionRotate_90_triggered();

    void on_actionRotate_91_triggered();

    void on_actionBrightness_triggered();

    void on_actionOR_triggered();

    void on_actionAND_triggered();

    Image *open_second_image();

    void on_actionNOT_triggered();

    void on_actionADD_triggered();

    void on_actionTranslate_triggered();

    void on_action33_triggered();

    void on_action200_triggered();

    void showZoom(int percentage);

    void on_action50_triggered();

    void on_action100_triggered();

    void on_action133_triggered();

    void on_action150_triggered();

    void on_action500_triggered();

    void on_action1000_triggered();

    void on_action2000_triggered();

    void on_actionPower_triggered();

    void on_actionGraylevel_Slicing_triggered();

    void on_actionBit_level_Slicing_triggered() {}

    void showBitSlicing(uint kernel, int level);

    void on_actionPlane_0_triggered();

    void on_actionPlane_1_triggered();

    void on_actionPlane_2_triggered();

    void on_actionBitplane_3_triggered();

    void on_actionBitplane_4_triggered();

    void on_actionBitplane_5_triggered();

    void on_actionBitplane_6_triggered();

    void on_actionBitplane_7_triggered();

    void on_actionReset_triggered();

    void on_actionAll_triggered();

    void on_actionContrast_Stretching_triggered();

    void on_actionGaussian_2_triggered();

    void show_convolution(double kernel[], int dimension, double divident, string name);

    void on_actionGaussian_triggered();

    void on_actionLaplace_triggered();

    void on_actionLoG_triggered();

    void on_actionSobel_triggered();

    void on_actionPrewitt_triggered();

    void on_actionLog_Transformation_triggered();

    void on_actionRoberts_triggered();

    void on_actionCanny_triggered();

    void on_actionGradient_triggered();

    void on_actionHistogram_triggered();

private:
    Ui::MainWindow *ui;
    QMdiArea *mdiArea; // Area in which windows will be added
};

#endif // MAINWINDOW_H
