#ifndef BINARYMATRIX_H
#define BINARYMATRIX_H

#include <QImage>
#include <QColor>
#include <QDebug>

//Clase para almacenar la binarización de
//la imagen original
class BinaryMatrix
{

    //Almacena la imagen original
    QImage image;

    //Almacena la imagen binaria
    QImage binaryImage;

    //Almacena la imagen binarizada como enteros (Matriz de W x H)
    int ** matrix;

    //Hue a distinguir
    int hue;

    //Saturacion a distinguir
    int saturation;

    //Value a distinguir
    int value;

    //Tolerancia
    int tolerance;


     //Libera la memoria pedida por una matriz
     void freeMatrixMemory()
     {
         for(int i = 0; i < this->image.height(); i++)
         {
             delete this->matrix[i];
         }
         delete this->matrix;
     }


public:

    //Constructor
    BinaryMatrix()
    {        

    }

    //Destructor
    ~BinaryMatrix()
    {
        //Borro la matriz binaria
        this->freeMatrixMemory();
    }

    //Metodo para setear una imagen a binarizar
    void setOriginalImage(QImage img)
    {
        this->image = img;
        this->binaryImage = img;
    }

    //Metodo para obtener la imagen en formato dibujable
    QImage getOriginalImage()
    {
        return this->image;
    }

    //Metodo para obtener la imagen binaria en formato dibujable
    QImage getBinaryImage()
    {
        return this->binaryImage;
    }

    //Permite setear el color a dejar en negro
    //Algo mas inteligente sería poder hacer un algoritmo que busque
    //tonalidades mas repetidas y establezca solo el intervalo
    //a eliminar. Por ahora hay que setearlo a mano
    void setHue(int col)
    {
        this->hue = col;
    }

    //Permite setear un valor de luminosidad a eliminar
    //Ayuda a no eliminar negros que se deseen conservar
    //dentro de la imagen, pero que posean hue en el rango de fondo

    void setValue(int val)
    {
        this->value = val;
    }

    //Permite setear un valor de saturación a eliminar
    //Ayuda a consevar blancos que se deseen en la imagen
    //pero que por poseer hue en el rango del fonfo, se pierden

    void setSaturation(int sat)
    {
        this->saturation = sat;
    }

    //Permite decirle al algoritmo de binarización,
    //el grado de tolerancia
    void setTolerance(int tol)
    {
        this->tolerance = tol;
    }

    //Binarizacion de la imagen - Importante llamarlo antes de borrar un objeto de esta clase
    void createBinaryImage()
    {
        //Creo la matriz del tamaño de la imagen
        this->matrix = new int * [image.height()];
        for(int i = 0; i < this->image.height(); i++)
        {
            this->matrix[i] = new int[image.width()];
        }

        //Recorro la imagen de arriba a abajo, de izquiera a derecha
        //Al acceder al image, accedo como par j,i porque j se mueve sobre X (ancho)
        //e i se mueve sobre Y (alto)

        //Por cada fila
        for(int i = 0; i < this->image.height();i++)
        {
            //Por cada columna
            for(int j = 0; j < this->image.width();j++)
            {
                //Obtengo el color de un pixel
                QColor c(this->image.pixel(j,i));

                //Preguto por la luminosidad y por la saturacion
                //Si esta demasiado oscuro como para distinguir el color
                //a eliminar, o esta muy poco saturado, lo dejo blanco
                if((c.value() <= this->value)||(c.hsvSaturation() <= this->saturation))
                {
                    //La matriz[fila][columna] se vuelve blanca, es decir 255
                    this->matrix[i][j] = 255;
                }
                else
                {
                    //Si esta iluminado bien, y puedo distinguir...
                    //Pregunto por el hue del HSV, si es igual al hue que quiero distinguir + - tolerancia
                    if((c.hsvHue() <= (this->hue + this->tolerance)) and (c.hsvHue() >= (this->hue - this->tolerance)))
                    {
                        //La matriz[fila][columna] se vuelve negra, es decir 0
                        this->matrix[i][j] = 0;
                    }
                    else
                    {
                        //La matriz[fila][columna] se vuelve blanca, es decir 255
                        this->matrix[i][j] = 255;
                    }
                }
            }
        }
        //Proceso la matriz para tener una version mostrable de la imagen binaria
        this->processMatrixToImage();
    }


    //Convierte la imagen en la matriz, a una imagen mostrable QImage
    void processMatrixToImage()
    {
        //Por cada fila
        for(int i = 0; i < this->image.height();i++)
        {
            //Por cada columna
            for(int j = 0; j < this->image.width();j++)
            {
                uint c = 0;
                //Si la matriz tiene un cero
                if(this->matrix[i][j] == 0)
                {
                    //Almaceno un Negro
                    c = QColor(0,0,0).rgb();
                }
                else
                {
                    //Sino almaceno blanco
                    c = QColor(255,255,255).rgb();
                }

                //Seteo el pixel en la imagen binaria
                this->binaryImage.setPixel(j,i,c);
            }
        }
    }







};

#endif // BINARYMATRIX_H
