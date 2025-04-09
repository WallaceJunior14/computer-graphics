#ifndef RETA_H
#define RETA_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Reta : public ObjetoGrafico {
public:
    Reta(const Ponto& ponto1, const Ponto& ponto2, int tamanho, const QColor& cor);

    void desenhar(QPainter& painter) const override;

    QString toString() const override;

    // setters e getters
    Ponto getP1() const { return p1; }
    Ponto getP2() const { return p2; }
    int getTamanho() const override;

private:
    Ponto p1, p2;
    int tamanho;
    QColor cor;
};


#endif // RETA_H
