#include "black_scholes.hpp"

//Aproximação da diferença a termo para calcular o Delta de uma call

double call_delta_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S ) {
    return (call_price(S + delta_S, K, r, v, T ) - call_price(S, K, r, v, T)) / delta_S;
}

//Aproximação de diferença central para calcular Gamma

double call_gamma_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S ) {
    return (call_price(S + delta_S, K, r, v, T) - 2 * call_price(S, K, r, v, T) + call_price(S - delta_S, K, r, v, T))/ (delta_S * delta_S);
}

int main(int argc, char **argv) {

    double S = 100.00;
    double delta_S = 0.001;
    double K = 100.00;
    double r = 0.05;
    double v = 0.2;
    double T = 1.0;

    double call_delta_f = call_delta_fdm(S, K, r, v, T, delta_S);
    double call_gamma_f = call_delta_fdm(S, K, r, v, T, delta_S);

    std::cout << "Underlying: " << S << std::endl;
    std::cout << "Delta underlying: " << delta_S << std::endl;
    std::cout << "Strike: " << K << std::endl;
    std::cout << "Taxa livre de risco: " << r << std::endl;
    std::cout << "Volatilidade: " << v << std::endl;
    std::cout << "Maturidade: " << T << std::endl;

    std::cout << "Call Delta: " << call_delta_f << std::endl;
    std::cout << "Call Gamma: " << call_gamma_f << std::endl;



}