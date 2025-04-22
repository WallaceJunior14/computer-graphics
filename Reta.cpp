#include "Reta.h"
#include <QDebug>

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
    // Calcula o centro da reta (média dos dois pontos)
    int cx = (p1.getX() + p2.getX()) / 2;
    int cy = (p1.getY() + p2.getY()) / 2;
    Ponto centro(cx, cy, p1.getCor());  // cor só por compatibilidade

    // Aplica a transformação em cada ponto em torno do centro
    p1.aplicarTransformacao(transformacao, centro);
    p2.aplicarTransformacao(transformacao, centro);
}

void Reta::normalizar() {
    p1.normalizar();
    p2.normalizar();
}

bool Reta::eh3D() const {
    return p1.eh3D() || p2.eh3D();
}
