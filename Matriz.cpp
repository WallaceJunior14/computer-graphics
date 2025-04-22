#include "Matriz.h"
#include <stdexcept>
#include <cmath>
#include <random>
#include <iostream>

// Construtor para matriz vazia
Matriz::Matriz() : linhas(0), colunas(0) {}

// Construtor para matriz com dimensões específicas
Matriz::Matriz(int lin, int col, double valorPadrao) : linhas(lin), colunas(col) {
    if (lin <= 0 || col <= 0) {
        throw std::invalid_argument("Dimensões devem ser positivas.");
    }

    matriz.resize(linhas, std::vector<double>(colunas, valorPadrao));
}

// Impressão
void Matriz::imprimir() const {
    for (const auto& linha : matriz) {
        for (double val : linha) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// Matriz identidade
Matriz Matriz::identidade(int tamanho) {
    if (tamanho <= 0) throw std::invalid_argument("Tamanho inválido.");
    Matriz id(tamanho, tamanho, 0);
    for (int i = 0; i < tamanho; ++i)
        id[i][i] = 1.0;
    return id;
}

// Matriz de translação 2D (para coordenadas homogêneas)
Matriz Matriz::translacao2D(double tx, double ty) {
    Matriz t = identidade(3);
    t[0][2] = tx;
    t[1][2] = ty;
    return t;
}

// Matriz de escala 2D (para coordenadas homogêneas)
Matriz Matriz::escala2D(double sx, double sy) {
    Matriz s = identidade(3);
    s[0][0] = sx;
    s[1][1] = sy;
    return s;
}

Matriz Matriz::rotacao2D(double anguloGraus) {
    Matriz r = identidade(3);
    double rad = anguloGraus * M_PI / 180.0;
    r[0][0] = std::cos(rad);
    r[0][1] = -std::sin(rad);
    r[1][0] = std::sin(rad);
    r[1][1] = std::cos(rad);
    return r;
}

// Matriz de translação 3D (para coordenadas homogêneas)
Matriz Matriz::translacao3D(double tx, double ty, double tz) {
    Matriz t = identidade(4);
    t[0][3] = tx;
    t[1][3] = ty;
    t[2][3] = tz;
    return t;
}

// Matriz de escala 3D (para coordenadas homogêneas)
Matriz Matriz::escala3D(double sx, double sy, double sz) {
    Matriz s = identidade(4);
    s[0][0] = sx;
    s[1][1] = sy;
    s[2][2] = sz;
    return s;
}

// Matriz de rotação em torno do eixo X (para coordenadas homogêneas 3D)
Matriz Matriz::rotacaoX3D(double anguloGraus) {
    Matriz r = identidade(4);
    double rad = anguloGraus * M_PI / 180.0;
    r[1][1] = std::cos(rad);
    r[1][2] = -std::sin(rad);
    r[2][1] = std::sin(rad);
    r[2][2] = std::cos(rad);
    return r;
}

// Matriz de rotação em torno do eixo Y (para coordenadas homogêneas 3D)
Matriz Matriz::rotacaoY3D(double anguloGraus) {
    Matriz r = identidade(4);
    double rad = anguloGraus * M_PI / 180.0;
    r[0][0] = std::cos(rad);
    r[0][2] = std::sin(rad);
    r[2][0] = -std::sin(rad);
    r[2][2] = std::cos(rad);
    return r;
}

// Matriz de rotação em torno do eixo Z (para coordenadas homogêneas 3D)
Matriz Matriz::rotacaoZ3D(double anguloGraus) {
    Matriz r = identidade(4);
    double rad = anguloGraus * M_PI / 180.0;
    r[0][0] = std::cos(rad);
    r[0][1] = -std::sin(rad);
    r[1][0] = std::sin(rad);
    r[1][1] = std::cos(rad);
    return r;
}

// Multiplicação de matrizes
Matriz Matriz::multiplicar(const Matriz& outra) const {
    if (colunas != outra.linhas) {
        throw std::invalid_argument("Dimensões incompatíveis para multiplicação.");
    }

    Matriz res(linhas, outra.colunas, 0);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < outra.colunas; ++j) {
            for (int k = 0; k < colunas; ++k) {
                res[i][j] += matriz[i][k] * outra[k][j];
            }
        }
    }
    return res;
}

Matriz Matriz::operator*(const Matriz& outra) const {
    return multiplicar(outra);
}

// Matrizes aleatórias
Matriz Matriz::aleatoria(int lin, int col, double minValor, double maxValor) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(minValor, maxValor);

    Matriz m(lin, col);
    for (int i = 0; i < lin; ++i)
        for (int j = 0; j < col; ++j)
            m[i][j] = dist(gen);

    return m;
}

// Redimensionamento
void Matriz::redimensionar(int novasLinhas, int novasColunas) {
    std::vector<std::vector<double>> novaMatriz(novasLinhas, std::vector<double>(novasColunas, 0.0));
    for (int i = 0; i < std::min(linhas, novasLinhas); ++i)
        for (int j = 0; j < std::min(colunas, novasColunas); ++j)
            novaMatriz[i][j] = matriz[i][j];

    matriz = novaMatriz;
    linhas = novasLinhas;
    colunas = novasColunas;
}

// Verificações
bool Matriz::mesmasDimensoes(const Matriz& outra) const {
    return linhas == outra.linhas && colunas == outra.colunas;
}

bool Matriz::ehQuadrada() const {
    return linhas == colunas;
}


