#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QImage>
#include <QColor>
#include <QDebug>

//Clase para almacenar una matriz binarizada y
//la imagen asociada a dicha matriz.
class ImageHandler {

    //Almacena la imagen binaria.
    QImage image;

    //Almacena la imagen en forma matricial.(Matriz de W x H)
    bool ** matrix;

    //Libera la memoria pedida por una matriz
     void freeMatrixMemory(){
         //Si existe la matriz
         if (matrix != NULL){
             for(int i = 0; i < this->image.height(); i++){
                 delete this->matrix[i];
             }
             delete this->matrix;
         }
     }

public:
    ImageHandler(QImage img, bool ** mat){
        //contructor, generador de la imagen a partir de la matriz
        //

        this->image = img;
        this->matrix = mat;

        if (this->matrix != NULL){
        //Por cada fila
            for(int i = 0; i < this->image.height();i++){
            //Por cada columna
                for(int j = 0; j < this->image.width();j++){
                    uint c = 0;
                    //Si la matriz tiene un cero
                    if(this->matrix[i][j]){
                        //Almaceno un Negro
                        c = QColor(0,0,0).rgb();
                    }
                    else{
                        //Sino almaceno blanco
                        c = QColor(255,255,255).rgb();
                    }

                    //Seteo el pixel en la imagen binaria
                    this->image.setPixel(j,i,c);
                }
            }
        }
    }

    ~ImageHandler(){
    //Borro la matriz binaria
        this->freeMatrixMemory();
    }


    QImage getImage(){
    //Metodo para obtener la imagen binaria en formato dibujable
        return this->image;
    }

    bool ** getMatrix(){
    //Metodo para obtener la imagen en formato de matriz
        return this->matrix;
    }

};




#endif // IMAGEHANDLER_H
