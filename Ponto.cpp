#include "Ponto.h"
#include <QPainter>

Ponto::Ponto(int x, int y, int tamanho, QColor cor)
    : x(x), y(y) {
    this->tamanho = tamanho;
    this->cor = cor;
}

void Ponto::desenhar(QPainter& painter) const {
    painter.setBrush(cor);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(x, y, tamanho, tamanho);
}

QString Ponto::toString() const {
    return QString("Ponto em (%1, %2), Tamanho: %3, Cor: %4")
    .arg(x).arg(y).arg(tamanho).arg(cor.name());
}
