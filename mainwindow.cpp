#include "mainwindow.h"
#include "image.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <QStringBuilder>
#include <brightnessslider.h>
#include "translate_dialog.h"
#include "power_transform_dialog.h"
#include "graylevel_slicing_dialog.h"
#include "contrast_stretching_dialog.h"
#include "logtransformdialog.h"
#include <cmath>
#include <QtCharts>
using namespace std;

const QString picturesFolder = "/home/hagairaja/Documents/Pengcit/miniphotoshop/test";
Image *picture;
QString fileTitle;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea(this); // init QMdiArea
    // configure scrollbars
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // Set Mdi Area as the central widget
    setCentralWidget(mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QDir dir1(picturesFolder);
    QString path = (dir1.exists()) ? picturesFolder : QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", path,
                                                    tr("Image (*.pgm *.ppm *.pbm *.bmp *.raw)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    // IMPLEMENT READ FILE HEREE
    QByteArray ba = fileName.toLocal8Bit();
    char *c_str2 = ba.data();
    picture = new Image(c_str2);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QStringList pieces = fileName.split("/");
    fileTitle = pieces.value(pieces.length() - 1);
    widget->setWindowTitle(fileTitle);
    // And show the widget
    widget->show();

    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    QByteArray ba = fileName.toLocal8Bit();
    char *c_str2 = ba.data();
    picture->save(c_str2);
    QStringList pieces = fileName.split("/");
    fileTitle = pieces.value(pieces.length() - 1);
    setWindowTitle(fileTitle);
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNegative_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->negatify();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString negative("Negative - ");
    widget->setWindowTitle(negative % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionGrayscale_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->grayscale();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("Grayscale - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionFlip_Vertical_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->flip_vertical();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("Flip Vertical - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionFlip_Horizontal_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->flip_horizontal();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("Flip Horizontal - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionRotate_90_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->rotate_90_clockwise();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("Rotate 90° - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionRotate_91_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->rotate_90_c_clockwise();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("Rotate -90° - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionBrightness_triggered()
{
    brightnessSlider bSlider;
    bSlider.setModal(true);
    bSlider.setWindowTitle("Add Brigthness Value");

    if (bSlider.exec() == QDialog::Accepted)
    {
        // Create a widget that will be a window
        QWidget *widget = new QWidget(mdiArea);
        // Adding layout to it
        QGridLayout *gridLayout = new QGridLayout(widget);
        widget->setLayout(gridLayout);
        // Adding an label with the picture to the widget
        QLabel *label = new QLabel(widget);
        picture->change_brightness(bSlider.value);
        label->setPixmap(QPixmap::fromImage(picture->getImage()));
        gridLayout->addWidget(label);

        // Adding a widget as a sub window in the Mdi Area
        mdiArea->addSubWindow(widget);
        // Set the window title
        QString title_info("Brightness Change - ");
        widget->setWindowTitle(title_info % fileTitle);
        // And show the widget
        widget->show();
    }
}

Image *MainWindow::open_second_image()
{
    QDir dir1(picturesFolder);
    QString path = (dir1.exists()) ? picturesFolder : QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", path,
                                                    tr("Image (*.pgm *.ppm *.pbm *.bmp *.raw)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return NULL;
    }

    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    // IMPLEMENT READ FILE HEREE
    QByteArray ba = fileName.toLocal8Bit();
    char *c_str2 = ba.data();
    Image *second_picture = new Image(c_str2);
    label->setPixmap(QPixmap::fromImage(second_picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QStringList pieces = fileName.split("/");
    QString secondFileTitle = pieces.value(pieces.length() - 1);
    widget->setWindowTitle(secondFileTitle);
    // And show the widget
    widget->show();

    file.close();

    return second_picture;
}

void MainWindow::on_actionOR_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    Image *second_picture = this->open_second_image();

    picture->operation_bool(second_picture, true);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("OR operation - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionAND_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    Image *second_picture = this->open_second_image();

    picture->operation_bool(second_picture, false);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("AND operation - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionNOT_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->operation_not();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("NOT operation - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionADD_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    Image *second_picture = this->open_second_image();

    picture->operation_arithmetic(second_picture);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString title_info("ADD operation - ");
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionTranslate_triggered()
{
    Translate_dialog translate_dialog;
    translate_dialog.setModal(true);
    translate_dialog.setWindowTitle("Translate Image");
    translate_dialog.setTranslateRange(picture->w, picture->h, picture->translate_x, picture->translate_y);

    if (translate_dialog.exec() == QDialog::Accepted) //Check if they clicked Ok
    {
        cout << translate_dialog.translateX << " " << translate_dialog.translateY << endl;
        fflush(stdout);
        picture->translate_x = translate_dialog.translateX;
        picture->translate_y = translate_dialog.translateY;

        // Create a widget that will be a window
        QWidget *widget = new QWidget(mdiArea);
        // Adding layout to it
        QGridLayout *gridLayout = new QGridLayout(widget);
        widget->setLayout(gridLayout);
        // Adding an label with the picture to the widget
        QLabel *label = new QLabel(widget);

        picture->update_translate(translate_dialog.from_ori);
        label->setPixmap(QPixmap::fromImage(picture->getImage()));
        gridLayout->addWidget(label);

        // Adding a widget as a sub window in the Mdi Area
        mdiArea->addSubWindow(widget);
        // Set the window title
        QString title_info("Translate result - ");
        widget->setWindowTitle(title_info % fileTitle);
        // And show the widget
        widget->show();
    }
}

void MainWindow::showZoom(int percentage)
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->zoom(percentage);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    string title = "Zoom ";
    title.append(to_string(percentage));
    title.append(" - ");
    QString title_info(title.c_str());
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_action33_triggered()
{
    this->showZoom(33);
}

void MainWindow::on_action200_triggered()
{
    this->showZoom(200);
}

void MainWindow::on_action50_triggered()
{
    this->showZoom(50);
}

void MainWindow::on_action100_triggered()
{
    this->showZoom(100);
}

void MainWindow::on_action133_triggered()
{
    this->showZoom(133);
}

void MainWindow::on_action150_triggered()
{
    this->showZoom(150);
}

void MainWindow::on_action500_triggered()
{
    this->showZoom(500);
}

void MainWindow::on_action1000_triggered()
{
    this->showZoom(1000);
}

void MainWindow::on_action2000_triggered()
{
    this->showZoom(2000);
}

void MainWindow::on_actionPower_triggered()
{
    Power_transform_dialog transform_dialog;
    transform_dialog.setModal(true);
    transform_dialog.setWindowTitle("Power Transform Image");

    if (transform_dialog.exec() == QDialog::Accepted) //Check if they clicked Ok
    {
        cout << transform_dialog.gamma << " " << transform_dialog.constant << endl;
        fflush(stdout);

        // Create a widget that will be a window
        QWidget *widget = new QWidget(mdiArea);
        // Adding layout to it
        QGridLayout *gridLayout = new QGridLayout(widget);
        widget->setLayout(gridLayout);
        // Adding an label with the picture to the widget
        QLabel *label = new QLabel(widget);

        picture->transform_gamma(transform_dialog.gamma, transform_dialog.constant);
        label->setPixmap(QPixmap::fromImage(picture->getImage()));
        gridLayout->addWidget(label);

        // Adding a widget as a sub window in the Mdi Area
        mdiArea->addSubWindow(widget);
        // Set the window title
        QString title_info("Power Transformation result - ");
        widget->setWindowTitle(title_info % fileTitle);
        // And show the widget
        widget->show();
    }
}

void MainWindow::on_actionGraylevel_Slicing_triggered()
{
    Graylevel_slicing_dialog dialog;
    dialog.setModal(true);
    dialog.setWindowTitle("Gray-level Slicing");

    if (dialog.exec() == QDialog::Accepted) //Check if they clicked Ok
    {
        cout << dialog.start << " " << dialog.end << " " << dialog.preserve << endl;
        fflush(stdout);

        // Create a widget that will be a window
        QWidget *widget = new QWidget(mdiArea);
        // Adding layout to it
        QGridLayout *gridLayout = new QGridLayout(widget);
        widget->setLayout(gridLayout);
        // Adding an label with the picture to the widget
        QLabel *label = new QLabel(widget);

        picture->graylevel_slicing(dialog.start, dialog.end, dialog.preserve);
        label->setPixmap(QPixmap::fromImage(picture->getImage()));
        gridLayout->addWidget(label);

        // Adding a widget as a sub window in the Mdi Area
        mdiArea->addSubWindow(widget);
        // Set the window title
        QString title_info("Gray-level Slicing result - ");
        widget->setWindowTitle(title_info % fileTitle);
        // And show the widget
        widget->show();
    }
}

void MainWindow::showBitSlicing(uint kernel, int level)
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->bit_slicing(kernel);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    string title = "Bit-level Slicing ";
    title.append(to_string(level));
    title.append(" - ");
    QString title_info(title.c_str());
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionPlane_0_triggered()
{
    showBitSlicing(1, 0);
}

void MainWindow::on_actionPlane_1_triggered()
{
    showBitSlicing(2, 1);
}

void MainWindow::on_actionPlane_2_triggered()
{
    showBitSlicing(4, 2);
}

void MainWindow::on_actionBitplane_3_triggered()
{
    showBitSlicing(8, 3);
}

void MainWindow::on_actionBitplane_4_triggered()
{
    showBitSlicing(16, 4);
}

void MainWindow::on_actionBitplane_5_triggered()
{
    showBitSlicing(32, 5);
}

void MainWindow::on_actionBitplane_6_triggered()
{
    showBitSlicing(64, 6);
}

void MainWindow::on_actionBitplane_7_triggered()
{
    showBitSlicing(128, 7);
}

void MainWindow::on_actionReset_triggered()
{
    picture->reset();
}

void MainWindow::on_actionAll_triggered()
{
    for (int i = 0; i < 8; i++)
    {
        showBitSlicing(uint(pow(2, i)), i);
        picture->reset();
    }
}

void MainWindow::on_actionContrast_Stretching_triggered()
{
    Contrast_stretching_dialog dialog_stretching;
    dialog_stretching.setModal(true);
    dialog_stretching.setWindowTitle("Contrast Stretching");

    if (dialog_stretching.exec() == QDialog::Accepted) //Check if they clicked Ok
    {
        // Create a widget that will be a window
        QWidget *widget = new QWidget(mdiArea);
        // Adding layout to it
        QGridLayout *gridLayout = new QGridLayout(widget);
        widget->setLayout(gridLayout);
        // Adding an label with the picture to the widget
        QLabel *label = new QLabel(widget);

        picture->contrast_stretching(dialog_stretching.x1, dialog_stretching.y1, dialog_stretching.x2, dialog_stretching.y2);
        label->setPixmap(QPixmap::fromImage(picture->getImage()));
        gridLayout->addWidget(label);

        // Adding a widget as a sub window in the Mdi Area
        mdiArea->addSubWindow(widget);
        // Set the window title
        QString title_info("Contrast Stretching - ");
        widget->setWindowTitle(title_info % fileTitle);
        // And show the widget
        widget->show();
    }
}

void MainWindow::show_convolution(double kernel[], int dimension, double divident) {
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->konvolusi(kernel, dimension, divident);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    string title = "Convolution - ";
    QString title_info(title.c_str());
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionGaussian_2_triggered()
{
    double kernel[] = {
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    };

    show_convolution(kernel, 3, 16);
}

void MainWindow::on_actionGaussian_triggered()
{
    double kernel[] = {
        0, 1, 0,
        1, -4, 1,
        0, 1, 0
    };

    show_convolution(kernel, 3, 0);
}

void MainWindow::on_actionLaplace_triggered()
{
    double kernel[] = {
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    };

    show_convolution(kernel, 3, 0);
}

void MainWindow::on_actionLoG_triggered()
{
    double gaussian_kernel[] = {
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    };

    double laplace_kernel[] = {
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    };

    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->konvolusi(gaussian_kernel, 3, 16);
    picture->konvolusi(laplace_kernel, 3, 0);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    string title = "Convolution - ";
    QString title_info(title.c_str());
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionSobel_triggered()
{
    double kernel_x[] = {
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    };

    double kernel_y[] = {
        1, 2, 1,
        0, 0, 0,
        -1, -2, -1
    };

    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->cross_convolution(kernel_x, kernel_y, 3);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    string title = "Convolution - ";
    QString title_info(title.c_str());
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}

void MainWindow::on_actionPrewitt_triggered()
{
    double kernel_x[] = {
        -1, 0, 1,
        -1, 0, 1,
        -1, 0, 1
    };

    double kernel_y[] = {
        1, 1, 1,
        0, 0, 0,
        -1, -1, -1
    };

    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->cross_convolution(kernel_x, kernel_y, 3);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    string title = "Convolution - ";
    QString title_info(title.c_str());
    widget->setWindowTitle(title_info % fileTitle);
    // And show the widget
    widget->show();
}
void MainWindow::on_actionLog_Transformation_triggered()
{
    LogTransformDialog dialog;
    dialog.setModal(true);
    dialog.setWindowTitle("Log Transformation");

    if (dialog.exec() == QDialog::Accepted) //Check if they clicked Ok
    {
        // Create a widget that will be a window
        QWidget *widget = new QWidget(mdiArea);
        // Adding layout to it
        QGridLayout *gridLayout = new QGridLayout(widget);
        widget->setLayout(gridLayout);
        // Adding an label with the picture to the widget
        QLabel *label = new QLabel(widget);

        picture->log_transform(dialog.constant, dialog.inverse);
        label->setPixmap(QPixmap::fromImage(picture->getImage()));
        gridLayout->addWidget(label);

        // Adding a widget as a sub window in the Mdi Area
        mdiArea->addSubWindow(widget);

        // Adding a widget as a sub window in the Mdi Area
        // Set the window title
        QString inverse("Inverse ");
        QString title_info("Log Transformation - ");
        if (!dialog.inverse) {
            widget->setWindowTitle(inverse % title_info % fileTitle);
        } else {
            widget->setWindowTitle(title_info % fileTitle);
        }

        // And show the widget
        widget->show();
    }

}

