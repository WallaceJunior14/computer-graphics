#include "Triangulo.h"

Triangulo::Triangulo(const Ponto& ponto1, const Ponto& ponto2, const Ponto& ponto3, int tamanho, const QColor& cor)
    : p1(ponto1), p2(ponto2), p3(ponto3), tamanho(tamanho), cor(cor) {}

void Triangulo::desenhar(QPainter& painter) const {
    painter.setPen(QPen(cor, tamanho));
    painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    painter.drawLine(p2.getX(), p2.getY(), p3.getX(), p3.getY());
    painter.drawLine(p3.getX(), p3.getY(), p1.getX(), p1.getY());
}

QString Triangulo::toString() const {
    return QString("Triangulo((%1, %2), (%3, %4), (%5, %6), tamanho: %7, cor: %8)")
    .arg(p1.getX()).arg(p1.getY()).arg(p2.getX()).arg(p2.getY()).arg(p3.getX()).arg(p3.getY()).arg(tamanho).arg(cor.name());
}
