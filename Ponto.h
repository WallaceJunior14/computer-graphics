#ifndef PONTO_H
#define PONTO_H

#include "ObjetoGrafico.h"
#include <QColor>

class Ponto : public ObjetoGrafico {
public:
    Ponto(int x, int y, int tamanho, QColor cor);

    void desenhar(QPainter& painter) const override;

    // Getters públicos (se for necessário acessar em Reta, por exemplo)
    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
    int tamanho = 5; // valor padrão
    QColor cor;
};

#endif // PONTO_H
