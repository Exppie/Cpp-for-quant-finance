#include "black_scholes.hpp"

//Aproximação da diferença a termo para calcular o Delta de uma call

double call_delta_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S ) {
    return (call_price(S + delta_S, K, r, v, T ) - call_price(S, K, r, v, T)) / delta_S;
}

//Aproximação de diferença central para calcular Gamma

double call_gamma_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S ) {
    return (call_price(S + delta_S, K, r, v, T) - 2 * call_price(S, K, r, v, T) + call_price(S - delta_S, K, r, v, T))/ (delta_S * delta_S);
}