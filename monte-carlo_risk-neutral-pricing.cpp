#include <algorithm>
#include <cmath>
#include <iostream>

//Implementação simples do algoritmo Box-Muller usado para gerar gaussian random numbers - necessários para Monte-carlo
double gaussian_box_muller() {
    double x = 0.0;
    double y = 0.0;
    double euclid_sq = 0.0;

//Continue gerando duas variáveis uniformes aleatórias até que o quadrado da distância euclidiana seja menos que a unidade
do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
    euclid_sq = x * x + y * y;
} while (euclid_sq <= 1.0);

return x * sqrt(-2 * log(euclid_sq) / euclid_sq);

}

//Precificando uma Call europeia com o método de Monte Carlo
double monte_carlo_call_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T) {
    double S_adjust = S * exp(T * (r - 0.5 * v * v));
    double S_cur = 0.0;
    double payoff_sum = 0.0; // soma de todos os payoffs das opções

    for (int i = 0; i <num_sims; i++){
        double gauss_bm = gaussian_box_muller();
        S_cur = S_adjust * exp(sqrt(v * v * T) * gauss_bm);
        payoff_sum += std::max(S_cur - K, 0.0); // Adiciona o payoff da opção ao resto dos valores
    }

    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

//Precificando uma Put europeia com o método de Monte Carlo
double monte_carlo_put_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T) {
    double S_adjust = S * exp(T * (r - 0.5 * v * v));
    double S_cur = 0.0;
    double payoff_sum = 0.0;

    for (int i = 0; i <num_sims; i++){
        double gauss_bm = gaussian_box_muller();
        S_cur = S_adjust * exp(sqrt(v * v * T) * gauss_bm);
        payoff_sum += std::max(K - S_cur, 0.0);
    }

    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r * T);
}

int main(int argc, char **argv) {
    int num_sims = 10000000; //número de caminhos de ativos simulados
    double S = 100.00;
    double K = 100.00;
    double r = 0.1225;
    double v = 0.2;
    double T = 1.0;

    //Calculando call/put via Monte Carlo
    double call = monte_carlo_call_price(num_sims, S, K, r, v, T);
    double put = monte_carlo_put_price(num_sims, S, K, r, v, T);

    std::cout << "N de caminhos: " << num_sims << std::endl;
    std::cout << "Underlying: " << S  << std::endl;
    std::cout << "Strike: " << K  << std::endl;
    std::cout << "Taxa livre de risco: " << r  << std::endl;
    std::cout << "Volatilidade: " << v  << std::endl;
    std::cout << "Maturidade: " << T  << std::endl;

    std::cout << "Call Price: " << call << std::endl;
    std::cout << "Put Price: " << put << std::endl;

    return 0;
}