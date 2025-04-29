#ifndef PONTO_H
#define PONTO_H

#include "ObjetoGrafico.h"
#include "Matriz.h"
#include <QColor>
#include <QPainter>

// Herança múltipla: Ponto herda de ObjetoGrafico e de Matriz
class Ponto : public ObjetoGrafico, public Matriz {
public:
    // Construtores
    Ponto(double x, double y, double z, QColor cor);
    Ponto(double x, double y, QColor cor); // Sobrecarga para compatibilidade 2D (z=0)

    // Sobreescrita das funções dentro da classe ObjetoGrafico
    void desenhar(QPainter& painter, MainWindow* mainWindow) const override;
    QString toString() const override;

    // Getters e Setters
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    // Métodos para transformações geométricas
    void aplicarTransformacao(const Matriz& transformacao, const Ponto& centro);

    // Método para normalizar coordenadas homogêneas
    void normalizar();

    // Método para calcular a distância até outro ponto
    double distancia(const Ponto& outro) const;

    // Método para verificar se é ponto 2D ou 3D
    bool eh3D() const;

    // Operador de atribuição
    Ponto& operator=(const Matriz& m);
};

#endif // PONTO_H
