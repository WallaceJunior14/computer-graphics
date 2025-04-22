#include "Matriz.h"
#include <stdexcept>
#include <cmath>
#include <random>
#include <iostream>

using namespace std;

// Construtor para matriz vazia
Matriz::Matriz() : linhas(0), colunas(0) {}

// Construtor para matriz com dimensões específicas
Matriz::Matriz(int lin, int col, int valorPadrao) : linhas(lin), colunas(col) {
    if (lin < 0 || col < 0) {
        throw std::invalid_argument("Dimensões da matriz não podem ser negativas");
    }

    this->resize(lin);
    for (int i = 0; i < lin; i++) {
        (*this)[i].resize(col, valorPadrao);
    }
}

// Métodos para obter dimensões da matriz
int Matriz::getLinhas() const {
    return linhas;
}

int Matriz::getColunas() const {
    return colunas;
}

// Imprimir matriz
void Matriz::imprimir() const {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << (*this)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Matriz identidade
Matriz Matriz::identidade(int tamanho) {
    if (tamanho <= 0) {
        throw std::invalid_argument("Tamanho da matriz identidade deve ser positivo");
    }

    Matriz id(tamanho, tamanho, 0);
    for (int i = 0; i < tamanho; i++) {
        id[i][i] = 1;
    }
    return id;
}

// Matriz de translação 2D (para coordenadas homogêneas)
Matriz Matriz::translacao2D(int tx, int ty) {
    Matriz t = identidade(3);
    t[0][2] = tx;
    t[1][2] = ty;
    return t;
}

// Matriz de escala 2D (para coordenadas homogêneas)
Matriz Matriz::escala2D(int sx, int sy) {
    Matriz s = identidade(3);
    s[0][0] = sx;
    s[1][1] = sy;
    return s;
}

// Matriz de rotação 2D (para coordenadas homogêneas)
Matriz Matriz::rotacao2D(double anguloGraus) {
    Matriz r = identidade(3);
    double anguloRad = anguloGraus * M_PI / 180.0;

    r[0][0] = cos(anguloRad);
    r[0][1] = -sin(anguloRad);
    r[1][0] = sin(anguloRad);
    r[1][1] = cos(anguloRad);

    return r;
}

// Matriz de translação 3D (para coordenadas homogêneas)
Matriz Matriz::translacao3D(int tx, int ty, int tz) {
    Matriz t = identidade(4);
    t[0][3] = tx;
    t[1][3] = ty;
    t[2][3] = tz;
    return t;
}

// Matriz de escala 3D (para coordenadas homogêneas)
Matriz Matriz::escala3D(int sx, int sy, int sz) {
    Matriz s = identidade(4);
    s[0][0] = sx;
    s[1][1] = sy;
    s[2][2] = sz;
    return s;
}

// Matriz de rotação em torno do eixo X (para coordenadas homogêneas 3D)
Matriz Matriz::rotacaoX3D(double anguloGraus) {
    Matriz r = identidade(4);
    double anguloRad = anguloGraus * M_PI / 180.0;

    r[1][1] = static_cast<int>(std::round(std::cos(anguloRad)));
    r[1][2] = static_cast<int>(std::round(-std::sin(anguloRad)));
    r[2][1] = static_cast<int>(std::round(std::sin(anguloRad)));
    r[2][2] = static_cast<int>(std::round(std::cos(anguloRad)));

    return r;
}

// Matriz de rotação em torno do eixo Y (para coordenadas homogêneas 3D)
Matriz Matriz::rotacaoY3D(double anguloGraus) {
    Matriz r = identidade(4);
    double anguloRad = anguloGraus * M_PI / 180.0;

    r[0][0] = static_cast<int>(std::round(std::cos(anguloRad)));
    r[0][2] = static_cast<int>(std::round(std::sin(anguloRad)));
    r[2][0] = static_cast<int>(std::round(-std::sin(anguloRad)));
    r[2][2] = static_cast<int>(std::round(std::cos(anguloRad)));

    return r;
}

// Matriz de rotação em torno do eixo Z (para coordenadas homogêneas 3D)
Matriz Matriz::rotacaoZ3D(double anguloGraus) {
    Matriz r = identidade(4);
    double anguloRad = anguloGraus * M_PI / 180.0;

    r[0][0] = static_cast<int>(std::round(std::cos(anguloRad)));
    r[0][1] = static_cast<int>(std::round(-std::sin(anguloRad)));
    r[1][0] = static_cast<int>(std::round(std::sin(anguloRad)));
    r[1][1] = static_cast<int>(std::round(std::cos(anguloRad)));

    return r;
}

// Multiplicação de matrizes
Matriz Matriz::multiplicar(const Matriz& outra) const {
    if (colunas != outra.linhas) {
        throw std::invalid_argument("Dimensões incompatíveis para multiplicação: (" +
                                    std::to_string(linhas) + "x" + std::to_string(colunas) + ") * (" +
                                    std::to_string(outra.linhas) + "x" + std::to_string(outra.colunas) + ")");
    }

    Matriz resultado(linhas, outra.colunas, 0);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < outra.colunas; j++) {
            for (int k = 0; k < colunas; k++) {
                resultado[i][j] += (*this)[i][k] * outra[k][j];
            }
        }
    }

    return resultado;
}

// Operador para multiplicação de matrizes
Matriz Matriz::operator*(const Matriz& outra) const {
    return this->multiplicar(outra);
}

// Método para criar matrizes com valores aleatórios
Matriz Matriz::aleatoria(int lin, int col, int minValor, int maxValor) {
    if (lin <= 0 || col <= 0) {
        throw std::invalid_argument("Dimensões da matriz devem ser positivas");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(minValor, maxValor);

    Matriz resultado(lin, col);
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            resultado[i][j] = distrib(gen);
        }
    }

    return resultado;
}

// Verificar se duas matrizes têm as mesmas dimensões
bool Matriz::mesmasDimensoes(const Matriz& outra) const {
    return (linhas == outra.linhas && colunas == outra.colunas);
}

// Verificar se é uma matriz quadrada
bool Matriz::ehQuadrada() const {
    return (linhas == colunas);
}

void Matriz::redimensionar(int novasLinhas, int novasColunas) {
    std::vector<std::vector<double>> novaMatriz(novasLinhas, std::vector<double>(novasColunas, 0));

    int linhasExistentes = std::min(novasLinhas, getLinhas());
    int colunasExistentes = std::min(novasColunas, getColunas());

    // Copia os valores existentes que ainda cabem na nova matriz
    for (int i = 0; i < linhasExistentes; ++i) {
        for (int j = 0; j < colunasExistentes; ++j) {
            novaMatriz[i][j] = this->matriz[i][j];
        }
    }

    // Substitui a matriz atual pela nova
    this->matriz = novaMatriz;
}
