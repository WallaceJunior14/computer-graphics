#include "Reta.h"

Reta::Reta(const Ponto& ponto1, const Ponto& ponto2, int tamanho, const QColor& cor)
    : p1(ponto1), p2(ponto2), tamanho(tamanho), cor(cor) {}

void Reta::desenhar(QPainter& painter) const {
    painter.setPen(QPen(cor, tamanho));
    painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}
