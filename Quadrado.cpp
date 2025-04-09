#include "Quadrado.h"

Quadrado::Quadrado(const Ponto& ponto1, const Ponto& ponto2, int tamanho, const QColor& cor)
    : p1(ponto1), p2(ponto2), tamanho(tamanho), cor(cor) {}

void Quadrado::desenhar(QPainter& painter) const {
    painter.setPen(QPen(cor, tamanho));
    painter.drawLine(p1.getX(), p1.getY(), p1.getX(), p2.getY()); // lado esquerdo
    painter.drawLine(p1.getX(), p2.getY(), p2.getX(), p2.getY()); // lado inferior
    painter.drawLine(p2.getX(), p2.getY(), p2.getX(), p1.getY()); // lado direito
    painter.drawLine(p2.getX(), p1.getY(), p1.getX(), p1.getY()); // lado superior
}

QString Quadrado::toString() const {
    return QString("Quadrado: P1(%1, %2), P2(%3, %4), Tamanho: %5, Cor: %6")
    .arg(p1.getX())
        .arg(p1.getY())
        .arg(p2.getX())
        .arg(p2.getY())
        .arg(tamanho)
        .arg(cor.name());
}

int Quadrado::getTamanho() const {
    return tamanho;
}
