#ifndef _NEWTON_RAPHSON_H
#define _NEWTON_RAPHSON_H

#include <cmath>

template <typename T, 
            double(T::*g) (double)const,
            double(T::*g_prime) (double) const>

double newton_raphson(  double y_target,       //Valor alvo de y
                        double init,           //Valor inicial de x
                        double epsilon,        //Tolerância
                        const T& root_func) {  //Objeto da função
    
    //Definir os preços iniciais e a volatilidade
    double y = (root_func.*g)(init); // Preço de opções iniciais
    double x = init;                    // Volatilidade inicial
                        
    //Enquanto y e y_target não forem similares
    //pegue o Vega da opção e recalcule um novo preço 
    //baseado na melhor aproximação linear no volume valor particular
    while (fabs(y - y_target) > epsilon) {
        double d_x = (root_func.*g_prime)(x);
        x += (y_target - y)/d_x;
        y = (root_func.*g)(x);
    }

    return x;

}

#endif