#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

namespace Ui {
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

    Image* open_second_image();

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

private:
    Ui::MainWindow *ui;
    QMdiArea * mdiArea;  // Area in which windows will be added
};

#endif // MAINWINDOW_H
