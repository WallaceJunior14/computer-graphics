#ifndef RETA_H
#define RETA_H

#include "ObjetoGrafico.h"
#include "Ponto.h"
#include <memory>

class Reta : public ObjetoGrafico {
public:
    Reta(const Ponto& ponto1, const Ponto& ponto2, const QColor& cor);

    // Sobreescrita das fuções dentro da classe ObjetoGrafico
    void desenhar(QPainter& painter, MainWindow* mainWindow) const override;
    QString toString() const override;

    // Manipulção 3D
    void aplicarTransformacao(const Matriz& transformacao);
    void normalizar();
    bool eh3D() const;

    // Getters
    Ponto getP1() const { return p1; }
    Ponto getP2() const { return p2; }

private:
    Ponto p1, p2;
};


#endif // RETA_H
