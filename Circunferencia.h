#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Circunferencia : public ObjetoGrafico
{
public:
    Circunferencia(const Ponto& ponto1, const int raio, int tamanho, const QColor& cor);

    ~Circunferencia() override = default;

    // Sobreescrita das fuções dentro da classe ObjetoGrafico
    void desenhar(QPainter& painter) const override;
    QString toString() const override;

    // setters e getters
    Ponto getP1() const { return p1; }
    int getRaio() const {return raio;}
    int getTamanho() const override;

private:
    const Ponto p1;
    const int raio;
    const int tamanho;
    const QColor cor;
};

#endif // CIRCUNFERENCIA_H
