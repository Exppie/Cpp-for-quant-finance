#include "black_scholes.hpp"

//Precificando uma call vanilla com o método de monte-carlo
//Criando 3 caminhos separados - incremento, não incremento e decremento, com base em delta_S

void monte_carlo_call_price(const int num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S, double& price_Sp, double& price_S, double& price_Sm) {

    //Necessário criar 3 paths ajustados para a ação em cada incremento/decremento do ativo

    double Sp_adjust = (S + delta_S) * exp(T * (r - 0.5 * v * v));
    double S_adjust = S * exp(T * (r - 0.5 * v * v));
    double Sm_adjust = (S - delta_S) * exp(T * (r - 0.5 * v * v));

    //Pay-offs para o preço final
    double payoff_sum_p = 0.0;
    double payoff_sum = 0.0;
    double payoff_sum_m = 0.0;

    //Loop sobre o número de simulações
    for (int i = 0; i < num_sims; i++){
        double gauss_bm = gaussian_box_muller(); //sorteio aleatório de gauss

        //Ajustar 3 caminhos da ação
        double expgauss = exp(sqrt(v * v * T) * gauss_bm); //Pré - calcule
        Sp_cur = Sp_adjust * expgauss;
        S_cur = S_adjust * expgauss;
        Sm_cur = Sm_adjust * expgauss;
    }
}