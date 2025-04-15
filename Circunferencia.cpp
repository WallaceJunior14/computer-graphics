#include "Circunferencia.h"
#define _USE_MATH_DEFINES
#include <cmath>

Circunferencia::Circunferencia(const Ponto& ponto1, int raio, int tamanho, const QColor& cor)
    : p1(ponto1), raio(raio), tamanho(tamanho), cor(cor) {}

void Circunferencia::desenhar(QPainter& painter) const {
    painter.setPen(QPen(cor, tamanho));

    int numPoints = 10000;
    for (int i = 0; i < numPoints; ++i) {
        int x1 = p1.getX() + int(raio * cos(i * 2 * M_PI / numPoints));
        int y1 = p1.getY() + int(raio * sin(i * 2 * M_PI / numPoints));
        painter.drawLine(x1, y1, x1, y1);
    }
}

QString Circunferencia::toString() const {
    return QString("Circunferencia: P1(%1, %2), Raio %3, Tamanho: %4, Cor: %5")
        .arg(p1.getX())
        .arg(p1.getY())
        .arg(raio)
        .arg(tamanho)
        .arg(cor.name());
}

int Circunferencia::getTamanho() const {
    return tamanho;
}




