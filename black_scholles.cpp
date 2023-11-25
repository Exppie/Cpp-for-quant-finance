#include "black_scholes.hpp"

int main(int argc, char **argv) {

    //Criando os parametros da lista
    double S = 100.00;
    double K = 100.00;
    double r = 0.1275;
    double v = 0.35;
    double T = 1.0;

    //Calculando valor call/put dos simbolos
    double call = call_price(S, K, r, v, T);
    double call_delta_v = call_delta(S, K, r, v, T);
    double call_gamma_v = call_gamma(S, K, r, v, T);
    double call_vega_v = call_vega(S, K, r, v, T);
    double call_theta_v = call_theta(S, K, r, v, T);
    double call_rho_v = call_rho(S, K, r, v, T);

    double put = call_price(S, K, r, v, T);
    double put_delta_v = call_delta(S, K, r, v, T);
    double put_gamma_v = call_gamma(S, K, r, v, T);
    double put_vega_v = call_vega(S, K, r, v, T);
    double put_theta_v = call_theta(S, K, r, v, T);
    double put_rho_v = call_rho(S, K, r, v, T);


    //Output
    std::cout << "Underlying: " << S << std::endl;
    std::cout << "Strike: " << K << std::endl;
    std::cout << "Taxa livre de risco: " << r << std::endl;
    std::cout << "Volatilidade: " << v << std::endl;
    std::cout << "Maturidade: " << T << std::endl;
    
    std::cout << "Preço da Call: " << call << std::endl;
    std::cout << "Call Delta: " << call_delta_v << std::endl;
    std::cout << "Call Gamma: " << call_gamma_v << std::endl;
    std::cout << "Call Vega: " << call_vega_v << std::endl;
    std::cout << "Call Theta: " << call_theta_v << std::endl;
    std::cout << "Call Rho: " << call_rho_v << std::endl;

    std::cout << "Preço da Put: " << put << std::endl;
    std::cout << "Put Delta: " << put_delta_v << std::endl;
    std::cout << "Put Gamma: " << put_gamma_v << std::endl;
    std::cout << "Put Vega: " << put_vega_v << std::endl;
    std::cout << "Put Theta: " << put_theta_v << std::endl;
    std::cout << "Put Rho: " << put_rho_v << std::endl;

    return 0;

}