#ifndef QUADRADO_H
#define QUADRADO_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Quadrado : public ObjetoGrafico {
public:
    Quadrado(const Ponto& ponto1, const Ponto& ponto2, int tamanho, const QColor& cor);

    void desenhar(QPainter& painter) const override;

    ~Quadrado() override = default;

    QString toString() const override;

private:
    const Ponto p1;
    const Ponto p2;
    const int tamanho;
    const QColor cor;
};

#endif // QUADRADO_H
