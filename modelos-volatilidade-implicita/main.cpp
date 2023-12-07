#ifndef __MAIN_CPP
#define __MAIN_CPP

#include "black-scholes.hpp"
#include "interval_bisection.hpp"
#include <iostream>

int main(int argc, char **argv){
    double S = 100.00;
    double K = 100.00;
    double r = 0.1225;
    double T = 1.0;
    double C_M = 10.5; //Preço de mercado da opção

    //Black-Scholes call functor
    BlackScholesCall bsc(S, K, r, T); //bsc é um parametro genérico


    //Parametros do intervalo bisseccional
    double low_vol = 0.05;
    double high_vol = 0.35;
    double episilon = 0.001;

    //Calculando a volatilidade implícita
    double sigma = interval_bisection(C_M, low_vol, high_vol, episilon, bsc);

    //Output
    std::cout <<"Volatilidade Implicíta: " << sigma << std::endl;


    return 0;

}

#endif