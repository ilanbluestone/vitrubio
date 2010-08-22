#ifndef EROSION_H
#define EROSION_H

#include <OperadorMorfologico.h>

class Erosion : public OperadorMorfologico{
//operador que realiza erosion sobre una imagen binarizada,
//generando una nueva matriz y retornando el resultado.

public:

    //Constructor, utiliza el constructor heredado.
    Erosion( bool ** v) : OperadorMorfologico(v){};

    //tenemos la altura maxima, el ancho maximo, la matriz de filtro
    //aplicamos la erosion al ImgeHandler, generando un nuevo ImageHandler.
    ImageHandler * aplicarOperador(ImageHandler * iH){

       if (iH != NULL){

           //variables auxiliares del tamaño de la imagen.
           int height = iH->getImage().height();
           int width = iH->getImage().width();

           //puntero auxiliar donde almacena la matriz,
           //booleana sobre la que itero.
           bool ** mat = iH->getMatrix();

           //Creo la matriz del tamaño de la imagen
           bool ** matErosionada = new bool * [height];
           for(int i = 0; i < height; i++){
               matErosionada[i] = new bool[width];
           }

           //varible auxiliar del valor
           //utilizada para almacenar el valor booleano
           //del pixel analizandoce.
           bool val;

           bool **vecinos = this->getMascaraDeVecinos();//--------------------------

           //Recorro la imagen de arriba a abajo, de izquiera a derecha
           //Al acceder a la matriz binarizada, accedo como par j,i
           //evitando los elementos del borde.

           //recorro las filas
           for(int i = 0; i < height -1; i++){
               //recorro las columnas
               for(int j = 0; j <width -1; j++){
                   if (i == 0 || i == height || j == 0 || j == width){
                   //si se encuentra sobre el borde conserva su valor.
                   //revisar si escorrecto.------------------------------------------
                       val = mat[i][j];
                   }
                   else{
                       val = true;
                       //recorro la vecindad.
                       for(int k = -1; k<2; k++){
                           for(int w =-1; w<2; w++){
                               //si el elemento forma parte de la mascara.
                               if (vecinos[k+1][w+1] == true)
                                   //todos los vecinos -
                                   val = (val & (vecinos[k+1][w+1] & mat[i+k][j+w]));
                           }
                       }
                   }

                   //la nueva matriz toma el valor de la valuacion.
                   matErosionada[i][j] = val;
               }
           }

           //genero el nuevo ImageHandler, a partir de la nueva Matriz.
           ImageHandler * iHe = new ImageHandler(iH->getImage(), matErosionada);

           return iHe;

       }
       return NULL;
   }

};

#endif // EROSION_H
