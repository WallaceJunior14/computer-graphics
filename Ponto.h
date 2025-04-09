#ifndef PONTO_H
#define PONTO_H

#include "ObjetoGrafico.h"

class Ponto : public ObjetoGrafico {
public:
    Ponto(int x, int y, int tamanho, QColor cor);

    void desenhar(QPainter& painter) const override;
    QString toString() const override;

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
};

#endif // PONTO_H
