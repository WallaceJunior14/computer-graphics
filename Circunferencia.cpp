#include "Circunferencia.h"
#include "mainwindow.h"
#define _USE_MATH_DEFINES
#include <cmath>

Circunferencia::Circunferencia(const Ponto& ponto1, double raio, const QColor& cor)
    : ObjetoGrafico(cor), p1(ponto1), raio(raio), cor(cor) {}

void Circunferencia::desenhar(QPainter& painter) const {
    painter.setPen(getPen());

    int numPoints = 1000;

    for (int i = 0; i < numPoints; ++i) {
        double x1 = p1.getX() + double(raio * cos(i * 2 * M_PI / numPoints));
        double y1 = p1.getY() + double(raio * sin(i * 2 * M_PI / numPoints));
        painter.drawLine(x1, y1, x1, y1);
    }
}

QString Circunferencia::toString() const {
    return QString("Circunferencia: P1(%1, %2), Raio %3, Cor: %5")
        .arg(p1.getX())
        .arg(p1.getY())
        .arg(raio)
        .arg(cor.name());
}

void Circunferencia::aplicarTransformacao(const Matriz& transformacao) {
    // Cria um ponto auxiliar na borda da circunferência (lado direito do centro)
    Ponto pontoRaio(p1.getX() + raio, p1.getY(), p1.getCor());

    // Aplica a transformação ao centro e ao ponto na borda
    Ponto novoCentro = p1;
    novoCentro.aplicarTransformacao(transformacao, p1);
    pontoRaio.aplicarTransformacao(transformacao, p1); // Usa o mesmo centro original

    // Atualiza o centro
    p1 = novoCentro;

    // Recalcula o raio com base na nova distância do centro ao ponto da borda
    raio = static_cast<int>(novoCentro.distancia(pontoRaio));
}

void Circunferencia::normalizar() {
    p1.normalizar();
}

bool Circunferencia::eh3D() const {
    return p1.eh3D();
}

