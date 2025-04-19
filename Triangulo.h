#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Triangulo : public ObjetoGrafico {
public:
    Triangulo(const Ponto& ponto1, const Ponto& ponto2, const Ponto& ponto3, const QColor& cor);
    ~Triangulo() override = default;

    // Sobreescrita das fuções dentro da classe ObjetoGrafico
    void desenhar(QPainter& painter) const override;
    QString toString() const override;

    // Métodos de transformação
    void aplicarTransformacao(const Matriz& transformacao);
    void normalizar();
    bool eh3D() const;

    // Setters e Getters
    Ponto getP1() const { return p1; }
    Ponto getP2() const { return p2; }
    Ponto getP3() const { return p3; }

private:
    Ponto p1, p2, p3;
    QColor cor;
};

#endif // TRIANGULO_H
