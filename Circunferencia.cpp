#include "Circunferencia.h"
#include "mainwindow.h"
#define _USE_MATH_DEFINES
#include <cmath>

Circunferencia::Circunferencia(const Ponto& ponto1, double raio, const QColor& cor)
    : ObjetoGrafico(cor), p1(ponto1), raio(raio), cor(cor) {}

void Circunferencia::desenhar(QPainter& painter, MainWindow* mainWindow) const {
    painter.setPen(getPen());

    int numPoints = 1000; // 10000 é exagero, 1000 já é bem suave visualmente
    QPoint anterior = mainWindow->transformarCoordenada(
        p1.getX() + raio * cos(0),
        p1.getY() + raio * sin(0)
        );

    for (int i = 1; i <= numPoints; ++i) {
        double angulo = i * 2 * M_PI / numPoints;
        double x = p1.getX() + raio * cos(angulo);
        double y = p1.getY() + raio * sin(angulo);

        QPoint atual = mainWindow->transformarCoordenada(x, y);

        painter.drawLine(anterior, atual);
        anterior = atual;
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

