#ifndef QUADRADO_H
#define QUADRADO_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Quadrado : public ObjetoGrafico {
public:
    // Construtor
    Quadrado(const Ponto& ponto1, const Ponto& ponto2, const Ponto& ponto3, const Ponto& ponto4, const QColor& cor);
    ~Quadrado() override = default;

    // Função para desenhar
    void desenhar(QPainter& painter) const override;


    // Transformações e verificação
    void aplicarTransformacao(const Matriz& transformacao);
    void normalizar();
    bool eh3D() const;

    QString toString() const override;

    // Getters
    Ponto getP1() const { return p1; }
    Ponto getP2() const { return p2; }
    Ponto getP3() const { return p3; }
    Ponto getP4() const { return p4; }
    QString getNome() const {return nome;}

    QString nome;

private:
    Ponto p1, p2, p3, p4;
    QColor cor;
};

#endif // QUADRADO_H
