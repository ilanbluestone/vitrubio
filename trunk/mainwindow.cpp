#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::paintEvent(QPaintEvent *)
{

}

//Metodo para llamar a pintar
void MainWindow::on_binary_clicked()
{
    //Seteo Hue, Value, Saturation y tolerancia
    bImage->setHue(120);
    bImage->setTolerance(50);
    bImage->setValue(70);
    bImage->setSaturation(50);
    //Creo imagen binaria
    bImage->createBinaryImage();
    //La muestro en el canvas B
    ui->canvasLabelB->setPixmap(QPixmap::fromImage(bImage->getBinaryImage()).scaled(ui->canvasLabelB->width(),ui->canvasLabelB->height(),Qt::KeepAspectRatio));
    //Elimino la matriz
    delete bImage;
}



//Metodo para cargar una imagen
//Solo de prueba... despues volara
void MainWindow::on_load_clicked()
{
    //Dialogo para cargar una imagen
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),"../", tr("Images (*.*)"));
    //Si eligio un path
    if(path != "")
    {
        //Creo una QImage a partir de la ruta
        QImage img(path);
        //Creo una nueva imagen binaria
        bImage = new BinaryMatrix;
        //Seteo la Imagen en el objeto imagen binaria
        bImage->setOriginalImage(img);
        //La muestro en el canvas
        ui->canvasLabel->setPixmap(QPixmap::fromImage(bImage->getOriginalImage()).scaled(ui->canvasLabel->width(),ui->canvasLabel->height(),Qt::KeepAspectRatio));
    }
}
