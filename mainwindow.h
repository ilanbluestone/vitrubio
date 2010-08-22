#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <binaryMatrix.h>
#include <ImageHandler.h>
//#include <OperadorMorfologico.h>
#include <Erosion.h>
#include <Dilatacion.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    ImageHandler * iH1;
    ImageHandler * iH2;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);

private slots:
    void on_load_clicked();
    void on_binary_clicked();
    void on_erosion_clicked();
    void on_dilatacion_clicked();

private:
    Ui::MainWindow *ui;

    //Imagen binaria
    BinaryMatrix * bImage;
};

#endif // MAINWINDOW_H
