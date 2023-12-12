#ifndef __MAIN_CPP
#define __MAIN_CPP

#include "black-scholes.hpp"
#include "newton_raphson.hpp"
#include <iostream>

int main(int argc, char **argv){
    double S = 100.00;
    double K = 100.00;
    double r = 0.1225;
    double T = 1.0;
    double C_M = 10.5; //Preço de mercado da opção

    //Black-Scholes call functor
    BlackScholesCall bsc(S, K, r, T); //bsc é um parametro genérico


    //Parâmetros para o modelo Newton Raphson
    double init = 0.3;  //Estimativa de volatilidade implícita de 30%
    double epsilon = 0.001;

    //Calculando a volatilidade implícita
    double sigma =  newton_raphson  <BlackScholesCall, 
                                    &BlackScholesCall::option_price,
                                    &BlackScholesCall::option_vega>
        (C_M, init, epsilon, bsc);

    //Output
    std::cout <<"Volatilidade Implicíta: " << sigma << std::endl;


    return 0;

}

#endif