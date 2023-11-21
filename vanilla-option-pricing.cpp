#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

//Função de densidade de probabilidade normal
double norm_pdf(const double& x ) {
    return (1.0 / (pow(2*M_PI, 0.5))) *exp(-0.5*x*x);
}

//Aproximação para a função de distribuição cumulativa para probabilidade normal
double norm_cdf(const double& x) {
    double k = 1.0/(1.0 + 0.2316419 * x);
    double k_sum = k*(0.319381530 + k * (-0.356563782 + k * ( 1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) {
        return (1.0 - (1.0 / pow(2 * M_PI, 0.5)) * exp (-0.5 * x * x) * k_sum);
    } else {
        return 1.0 - norm_cdf(-x);
    }
}

// Calcula d_j, for j in {1,2} - Termo que aparece na solução fechada para o preço de uma call e put europeia
double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
    return (log(S/K) + (r + (pow(-1, j - 1)) * 0.5 * v * v) * T) / (v * (pow(T, 0.5)));
}

// Calculando o preço da call com base em S, K, r, v
double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return S * norm_cdf(d_j(1, S, K, r, v, T)) - K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
} 

// Calculando o preço da put com base em S, K, r, v
double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return - S*norm_cdf(-d_j(1, S, K, r, v, T)) + K * exp (-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

int main(int argc, char **argv) {
    //Criando lista de parametros
    double S = 100.0; // Preço da opção
    double K = 100.0; //Preço de strike
    double r = 0.1275; // taxa de juros livre de risco
    double v = 0.35; // Volatilidade do ativo
    double T  = 1.0; // Um ano até a expiração

//Calculando o valor put/call
double call = call_price(S, K, r, v, T);
double put = put_price(S, K, r, v, T);

std::cout << "Underlying: " << S  << std::endl;
std::cout << "Strike: " << K  << std::endl;
std::cout << "Taxa livre de risco: " << r  << std::endl;
std::cout << "Volatilidade: " << v  << std::endl;
std::cout << "Maturidade: " << T  << std::endl;

std::cout << "Call Price: " << call << std::endl;
std::cout << "Put Price: " << put  << std::endl;

return 0;
}