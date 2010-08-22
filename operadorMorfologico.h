#ifndef OPERADORMORFOLOGICO_H
#define OPERADORMORFOLOGICO_H

#include <ImageHandler.h>

class OperadorMorfologico{

    bool ** mascaraVecinos;//considero que la mascara maxima es de 3x3

protected:
    //retorna la mascara de vecinos.
    bool** getMascaraDeVecinos(){
        return this->mascaraVecinos;
    }


public:

    //genera una mascara a partir de una matriz booleana.
    OperadorMorfologico(bool ** v){
        this->mascaraVecinos = v;
    }

    virtual ImageHandler * aplicarOperador(ImageHandler *)= 0;

    ~OperadorMorfologico(){
         freeMascaraMemory();
    }

    //Libera la memoria pedida por una matriz
    void freeMascaraMemory()
    {
        if (mascaraVecinos != NULL){
            for(int i = 0; i < 3; i++)//aca esta hard------------------
            {
                delete this->mascaraVecinos[i];
            }
            delete this->mascaraVecinos;
        }
    }
};

#endif // OPERADORMORFOLOGICO_H
