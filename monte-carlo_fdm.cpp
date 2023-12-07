#include "black_scholes.hpp"

//Precificando uma call vanilla com o método de monte-carlo
//Criando 3 caminhos separados - incremento, não incremento e decremento, com base em delta_S

void monte_carlo_call_price(const long num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S, double& price_Sp, double& price_S, double& price_Sm) {

    //Necessário criar 3 paths ajustados para a ação em cada incremento/decremento do ativo

    double Sp_adjust = (S + delta_S) * exp(T * (r - 0.5 * v * v));
    double S_adjust = S * exp(T * (r - 0.5 * v * v));
    double Sm_adjust = (S - delta_S) * exp(T * (r - 0.5 * v * v));


    //Armazenar os preços correntes conforme a simulação é carregada
    double Sp_cur = 0.0;
    double S_cur = 0.0;
    double Sm_cur = 0.0;

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

        //Calculando o pay-off continuo para cada incremento/decremento
        payoff_sum_p += std::max(Sp_cur - K, 0.0);
        payoff_sum += std::max(S_cur - K, 0.0);
        payoff_sum_m += std::max(Sm_cur - K, 0.0);
    }

    //Três preços separados
    price_Sp = (payoff_sum_p / static_cast <double> (num_sims)) * exp(-r * T);
    price_S = (payoff_sum / static_cast <double> (num_sims)) * exp (-r * T);
    price_Sm = (payoff_sum_m / static_cast <double> (num_sims)) * exp (-r * T);
}

double call_delta_mc(const long num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S) {

    //Valores populados pela função monte_carlo_call_price
    //Representam o incremento, não incremento e decremento dos preços

    double price_Sp = 0.0;
    double price_S = 0.0;
    double price_Sm = 0.0;

    monte_carlo_call_price(num_sims, S, K, r, v, T, delta_S, price_Sp, price_S, price_Sm);
    
    return (price_Sp - price_S)/delta_S; //necessários apenas dois valores para delta
}

double call_gamma_mc(const long num_sims, const double S, const double K, const double r, const double v, const double T, const double delta_S){

    //Populados pela função monte_carlo_call_price

    double price_Sp = 0.0;
    double price_S = 0.0;
    double price_Sm = 0.0;

    //Chama a função para todo caminho do ativo
    monte_carlo_call_price(num_sims, S, K, r, v, T, delta_S, price_Sp, price_S, price_Sm);

    return(price_Sp - 2*price_S + price_Sm) / (delta_S * delta_S); //Gamma necessita dos três valores
}

int main(int argc, char **argv) {

    double S = 100.0;
    double delta_S = 0.001;
    double K = 100.0;
    double r = 0.1225;
    double v = 0.68;    
    double T = 1.0;
    int num_sims = 1000000000;


    double call_delta_m = call_delta_mc(num_sims, S, K, r, v, T, delta_S);
    double call_gamma_m = call_gamma_mc(num_sims, S, K, r, v, T, delta_S);


    //Output
    std::cout << "Qtd. Simulações:   " << num_sims << std::endl;
    std::cout << "Underlying:        " << S << std::endl;
    std::cout << "Delta underlying:  " << delta_S << std::endl;
    std::cout << "Strike:            " << K << std::endl;
    std::cout << "RF rate:           " << r << std::endl;
    std::cout << "Volatilidade:      " << v << std::endl;
    std::cout << "Maturidade:        " << T << std::endl;

    std::cout << "Call Delta:  " << call_delta_m << std::endl;
    std::cout << "Call Gamma:  " << call_gamma_m << std::endl;
}