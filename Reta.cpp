#include "Reta.h"

Reta::Reta(const Ponto& ponto1, const Ponto& ponto2, int tamanho, const QColor& cor)
    : p1(ponto1), p2(ponto2), tamanho(tamanho), cor(cor) {}

void Reta::desenhar(QPainter& painter) const {
    painter.setPen(QPen(cor, tamanho));
    painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

QString Reta::toString() const {
    return QString("Reta((%1, %2) -> (%3, %4), tamanho: %5, cor: %6)")
    .arg(p1.getX()).arg(p1.getY()).arg(p2.getX()).arg(p2.getY()).arg(tamanho).arg(cor.name());
}

int Reta::getTamanho() const {
    return tamanho;
}
