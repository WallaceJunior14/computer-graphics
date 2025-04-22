#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <stdexcept>
#include <iostream>

class Matriz : public std::vector<std::vector<int>> {
private:
    int linhas;
    int colunas;
    std::vector<std::vector<double>> matriz;

public:
    // Construtores
    Matriz();
    Matriz(int lin, int col, double valorPadrao = 0.0);

    // Getters
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }

    // Acesso a elementos (como operador de matriz)
    std::vector<double>& operator[](int i) {
        return matriz[i];
    }

    const std::vector<double>& operator[](int i) const {
        return matriz[i];
    }

    // Impressão
    void imprimir() const;

    // Transformações 2D
    static Matriz translacao2D(double tx, double ty);
    static Matriz escala2D(double sx, double sy);
    static Matriz rotacao2D(double anguloGraus);

    // Outros métodos (redimensionar, aleatória, etc.)
    void redimensionar(int novasLinhas, int novasColunas);

    // Matriz identidade
    static Matriz identidade(int tamanho);

    // Matrizes de transformação 3D (coordenadas homogêneas)
    static Matriz translacao3D(double tx, double ty, double tz);
    static Matriz escala3D(double sx, double sy, double sz);
    static Matriz rotacaoX3D(double anguloGraus);
    static Matriz rotacaoY3D(double anguloGraus);
    static Matriz rotacaoZ3D(double anguloGraus);

    // Multiplicação de matrizes
    Matriz multiplicar(const Matriz& outra) const;
    Matriz operator*(const Matriz& outra) const;

    // Método para criar matrizes com valores aleatórios
    static Matriz aleatoria(int lin, int col, double minValor = 0.0, double maxValor = 10.0);

    // Verificar se duas matrizes têm as mesmas dimensões
    bool mesmasDimensoes(const Matriz& outra) const;

    // Verificar se é uma matriz quadrada
    bool ehQuadrada() const;
};

#endif // MATRIZ_H
