#include "Reta.h"

Reta::Reta(const Ponto& ponto1, const Ponto& ponto2, const QColor& cor)
    :ObjetoGrafico(cor), p1(ponto1), p2(ponto2) {}

void Reta::desenhar(QPainter& painter) const {
    painter.setPen(getPen());
    painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

QString Reta::toString() const {
    return QString("Reta((%1, %2) -> (%3, %4), cor: %6)")
    .arg(p1.getX()).arg(p1.getY()).arg(p2.getX()).arg(p2.getY()).arg(cor.name());
}

void Reta::aplicarTransformacao(const Matriz& transformacao) {
    Ponto novoP1 = p1;
    Ponto novoP2 = p2;

    novoP1.aplicarTransformacao(transformacao);
    novoP2.aplicarTransformacao(transformacao);

    p1 = novoP1;
    p2 = novoP2;
}

void Reta::normalizar() {
    p1.normalizar();
    p2.normalizar();
}

bool Reta::eh3D() const {
    return p1.eh3D() || p2.eh3D();
}
