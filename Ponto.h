#ifndef PONTO_H
#define PONTO_H

#include "ObjetoGrafico.h"

class Ponto : public ObjetoGrafico {
public:
    Ponto(int x, int y, int tamanho, QColor cor);

    // Sobreescrita das fuções dentro da classe ObjetoGrafico
    void desenhar(QPainter& painter) const override;
    QString toString() const override;

    // Getters e Setters
    int getX() const { return x; }
    int getY() const { return y; }
    int getTamanho() const override;

private:
    int x, y;
};

#endif // PONTO_H
