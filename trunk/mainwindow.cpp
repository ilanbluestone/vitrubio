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
    //Creo un ImageHandler, de la imagen sin fondo.
    ImageHandler * imageSinFondo;
    //Creo imagen binaria
    imageSinFondo = bImage->createBinaryImage();
    //La muestro en el canvas B
    ui->canvasLabelB->setPixmap(QPixmap::fromImage(imageSinFondo->getImage()).scaled(ui->canvasLabelB->width(),ui->canvasLabelB->height(),Qt::KeepAspectRatio));
    //Elimino la matriz
    delete bImage;
    iH1 = imageSinFondo;
    //delete imageSinFondo;
}

void MainWindow::on_erosion_clicked()
{
    //genero la mascara.
    //Creo la matriz del tamaño de la mascara
    bool ** m = new bool * [3];
    for(int i = 0; i < 3; i++){
        m[i] = new bool [3];
    }
    //Seteo los valores de la misma.
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if ( (i == 1) & (j == 1) )
                m[i][j] = true;
            else m[i][j] = false; //todos los vecinos
        }
    }
    //genero el operador morfologico.
    OperadorMorfologico * patito;
    patito = new Erosion(m);
    iH2 = patito->aplicarOperador(iH1);

    //La muestro en el canvas B
    ui->canvasLabel->setPixmap(QPixmap::fromImage(iH2->getImage()).scaled(ui->canvasLabel->width(),ui->canvasLabel->height(),Qt::KeepAspectRatio));
    //Elimino la matriz
    //delete iH1;
    delete iH2;
}

void MainWindow::on_dilatacion_clicked()
{
    //genero la mascara.
    //Creo la matriz del tamaño de la mascara
    bool ** m = new bool * [3];
    for(int i = 0; i < 3; i++){
        m[i] = new bool [3];
    }
    //Seteo los valores de la misma.
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if ( (i == 1) & (j == 1) )
                m[i][j] = true;
            else m[i][j] = false; //todos los vecinos
        }
    }
    //genero el operador morfologico.
    OperadorMorfologico * patito;
    patito = new Dilatacion(m);
    iH2 = patito->aplicarOperador(iH1);

    //La muestro en el canvas B
    ui->canvasLabelB->setPixmap(QPixmap::fromImage(iH2->getImage()).scaled(ui->canvasLabelB->width(),ui->canvasLabelB->height(),Qt::KeepAspectRatio));
    //Elimino la matriz
    //delete iH1;
    delete iH2;
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
        bImage = new BinaryMatrix(img);
        //La muestro en el canvas
        ui->canvasLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->canvasLabel->width(),ui->canvasLabel->height(),Qt::KeepAspectRatio));
    }
}
