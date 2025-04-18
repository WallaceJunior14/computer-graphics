#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <string>

class Matriz : public std::vector<std::vector<int>> {
private:
    int linhas;
    int colunas;
    std::vector<std::vector<double>> matriz;

public:
    // Construtores
    Matriz();
    Matriz(int lin, int col, int valorPadrao = 0);

    // Métodos para obter dimensões da matriz
    int getLinhas() const;
    int getColunas() const;

    // Imprimir matriz
    void imprimir() const;

    // Matriz identidade
    static Matriz identidade(int tamanho);

    // Matrizes de transformação 2D (coordenadas homogêneas)
    static Matriz translacao2D(int tx, int ty);
    static Matriz escala2D(int sx, int sy);
    static Matriz rotacao2D(double anguloGraus);

    // Matrizes de transformação 3D (coordenadas homogêneas)
    static Matriz translacao3D(int tx, int ty, int tz);
    static Matriz escala3D(int sx, int sy, int sz);
    static Matriz rotacaoX3D(double anguloGraus);
    static Matriz rotacaoY3D(double anguloGraus);
    static Matriz rotacaoZ3D(double anguloGraus);

    // Multiplicação de matrizes
    Matriz multiplicar(const Matriz& outra) const;
    Matriz operator*(const Matriz& outra) const;

    // Método para criar matrizes com valores aleatórios
    static Matriz aleatoria(int lin, int col, int minValor = 0, int maxValor = 10);

    // Verificar se duas matrizes têm as mesmas dimensões
    bool mesmasDimensoes(const Matriz& outra) const;

    // Verificar se é uma matriz quadrada
    bool ehQuadrada() const;

    void redimensionar(int novasLinhas, int novasColunas);
};

#endif // MATRIZ_H
