#ifndef CIRCUNFERENCIA_H
#define CIRCUNFERENCIA_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Circunferencia : public ObjetoGrafico {
public:
    Circunferencia(const Ponto& ponto1, int raio, const QColor& cor);
    ~Circunferencia() override = default;

    // Sobrescrita das funções da classe ObjetoGrafico
    void desenhar(QPainter& painter) const override;
    QString toString() const override;

    // Getters
    Ponto getP1() const { return p1; }
    int getRaio() const { return raio; }

    // Métodos de transformação
    void aplicarTransformacao(const Matriz& transformacao);
    void normalizar();
    bool eh3D() const;

private:
    Ponto p1;
    int raio;
    QColor cor;
};

#endif // CIRCUNFERENCIA_H
