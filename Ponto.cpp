#include "Ponto.h"
#include <QPainter>

Ponto::Ponto(int x, int y, int tamanho, QColor cor)
    : x(x), y(y), tamanho(tamanho), cor(cor) {}

void Ponto::desenhar(QPainter& painter) const {
    painter.setBrush(cor);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(x, y, tamanho, tamanho);
}
