#ifndef __BLACK_SCHOLES_CPP
#define __BLACK_SCHOLES_CPP

#include "black-scholes.hpp"
#include "bs_prices.hpp"

BlackScholesCall::BlackScholesCall(double _S, double _K, double _r, double _T):
    S(_S), K(_K), r(_r), T(_T) {}

double BlackScholesCall::option_price(double sigma) const {
    return call_price(S, K, r, sigma, T);
}

//Novo metodo que chama call_vega para obter o preço
double BlackScholesCall::option_vega(double sigma) const{
    return call_vega(S, K, r, sigma, T);
    
}

#endif