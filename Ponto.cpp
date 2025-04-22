#include "Ponto.h"
#include <QDebug>
#include <cmath>

// Construtor para ponto 3D
Ponto::Ponto(int x, int y, int z, QColor cor)
    : ObjetoGrafico(cor), Matriz(3, 1, 1) {
    (*this)[0][0] = x;
    (*this)[1][0] = y;
    (*this)[2][0] = 1;  // coordenada homogênea
}

// Construtor para ponto 2D (z=0)
Ponto::Ponto(int x, int y, QColor cor)
    : Ponto(x, y, 0, cor) {
    // Chama o construtor 3D com z=0
}

void Ponto::desenhar(QPainter& painter) const {
    painter.setPen(getPen());
    // Simplesmente desenha no plano 2D (ignorando a coordenada Z)
    // Em uma aplicação real, você provavelmente iria projetar o ponto 3D para 2D antes de desenhar
    painter.drawPoint(getX(), getY());
}

QString Ponto::toString() const {
    if (eh3D()) {
        return QString("Ponto3D(%1, %2, %3)").arg(getX()).arg(getY()).arg(getZ());
    } else {
        return QString("Ponto(%1, %2)").arg(getX()).arg(getY());
    }
}

int Ponto::getX() const {
    return (*this)[0][0];
}

int Ponto::getY() const {
    return (*this)[1][0];
}

int Ponto::getZ() const {
    // Se for uma matriz 3x1 (ponto 2D), retorna 0
    if (getLinhas() == 3) {
        return 0;
    }
    return (*this)[2][0];
}

void Ponto::setX(int x) {
    (*this)[0][0] = x;
}

void Ponto::setY(int y) {
    (*this)[1][0] = y;
}

void Ponto::setZ(int z) {
    // Se for uma matriz 4x1 (ponto 3D)
    if (getLinhas() == 4) {
        (*this)[2][0] = z;
    } else {
        // Se for uma matriz 3x1 (ponto 2D), converte para 4x1
        Matriz temp(4, 1, 0);
        temp[0][0] = getX();
        temp[1][0] = getY();
        temp[2][0] = z;
        temp[3][0] = 1;

        // Copia os valores de volta para o ponto
        // Redimensiona a matriz base da classe para 4x1
        this->redimensionar(4, 1);

        // Copia os valores de temp para *this
        for (int i = 0; i < 4; i++) {
            (*this)[i][0] = temp[i][0];
        }
    }
}

void Ponto::aplicarTransformacao(const Matriz& transformacao) {
    int n = this->getLinhas();

    if (transformacao.getColunas() != n || transformacao.getLinhas() != n) {
        throw std::invalid_argument("A transformação precisa ser uma matriz NxN compatível com o ponto.");
    }

    Matriz resultado = transformacao * (*this);  // Multiplica a matriz de transformação pelo ponto

    for (int i = 0; i < n; ++i) {
        (*this)[i][0] = resultado[i][0];
    }
}


void Ponto::normalizar() {
    // Obtém o índice do componente homogêneo (última linha)
    int homIndex = getLinhas() - 1;

    // Se o componente homogêneo não for 0 ou 1, normaliza as coordenadas
    if ((*this)[homIndex][0] != 0 && (*this)[homIndex][0] != 1) {
        for (int i = 0; i < homIndex; i++) {
            (*this)[i][0] /= (*this)[homIndex][0];
        }
        (*this)[homIndex][0] = 1;
    }
}

double Ponto::distancia(const Ponto& outro) const {
    double somaQuadrados = 0.0;

    // Calcula a distância euclidiana considerando as dimensões disponíveis
    int dimMin = std::min(getLinhas() - 1, outro.getLinhas() - 1);

    for (int i = 0; i < dimMin; i++) {
        double diff = (*this)[i][0] - outro[i][0];
        somaQuadrados += diff * diff;
    }

    return std::sqrt(somaQuadrados);
}

bool Ponto::eh3D() const {
    // Verifica se é um ponto 3D (matriz 4x1) ou 2D (matriz 3x1)
    return (getLinhas() == 4);
}

Ponto& Ponto::operator=(const Matriz& m) {
    if (this != &m) {
        QColor corAtual = getCor();  // Salva a cor atual

        this->redimensionar(m.getLinhas(), m.getColunas());
        for (int i = 0; i < m.getLinhas(); i++) {
            for (int j = 0; j < m.getColunas(); j++) {
                (*this)[i][j] = m[i][j];
            }
        }

        this->setCor(corAtual);  // Restaura a cor
    }
    return *this;
}
