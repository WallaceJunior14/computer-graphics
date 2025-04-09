#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Triangulo : public ObjetoGrafico {
public:
    Triangulo(const Ponto& ponto1, const Ponto& ponto2, const Ponto& ponto3, int tamanho, const QColor& cor);

    void desenhar(QPainter& painter) const override;

    ~Triangulo() override = default;

    QString toString() const override;

    // Setters e Getters
    Ponto getP1() const { return p1; }
    Ponto getP2() const { return p2; }
    Ponto getP3() const { return p3; }
    int getTamanho() const override;

private:
    const Ponto p1;
    const Ponto p2;
    const Ponto p3;
    const int tamanho;
    const QColor cor;
};

#endif // TRIANGULO_H
