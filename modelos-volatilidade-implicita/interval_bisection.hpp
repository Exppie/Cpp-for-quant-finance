#ifndef __INTERVAL_BISECTION_H
#define __INTERVAL_BISECTION_H

#include <cmath>

//Criando template da função
//Encontrando um x tal que |g(x) - y| < epsilon
//Começando com o intervalo (m, n)

template<typename T>

double interval_bisection(  double y_target,  //Valor y alvo 
                            double m,        //Valor do intervalo esquerdo
                            double n,       //Valor do intervalo direito 
                            double epsilon,//Tolerância
                            T g){         //Função objeto de tipo T, nome g 

    double x = 0.5 * (m + n); //Cria o valor mid-point x
    double y = g(x);         //Encontra o valor y mapeado de g(x)


    //Enquanto a diferença entre y e y_target for maior que epsilon
    //Continue subdividindo o intervalo em metades e revalore o novo y

    do {
        if ( y < y_target) {
            m = x;
        }

        if (y > y_target){
            n = x;
        }

        x = 0.5 * (m + n);
        y = g(x);

    } while (fabs(y - y_target) > epsilon);
        
        
    return x;

}

#endif