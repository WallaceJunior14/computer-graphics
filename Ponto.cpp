#include "Ponto.h"

Ponto::Ponto(int x, int y, int tamanho, QColor cor)
    : x(x), y(y), tamanho(tamanho), cor(cor) {}

void Ponto::desenhar(QPainter& p) const {
    QBrush brush(cor);
    p.setBrush(brush);
    p.setPen(Qt::NoPen); // sem borda
    p.drawEllipse(QPoint(x, y), tamanho, tamanho); // raio X, raio Y
}
