#include "Quadrado.h"
#include "mainwindow.h"
#include <QDebug>

Quadrado::Quadrado(const Ponto& ponto1, const Ponto& ponto2, const Ponto& ponto3, const Ponto& ponto4, const QColor& cor)
    : ObjetoGrafico(cor), p1(ponto1), p2(ponto2), p3(ponto3), p4(ponto4), cor(cor) {}

void Quadrado::desenhar(QPainter& painter, MainWindow* mainWindow) const {
    painter.setPen(getPen());

    QPoint p1_ = mainWindow->transformarCoordenada(p1.getX(), p1.getY());
    QPoint p2_ = mainWindow->transformarCoordenada(p2.getX(), p2.getY());
    QPoint p3_ = mainWindow->transformarCoordenada(p3.getX(), p3.getY());
    QPoint p4_ = mainWindow->transformarCoordenada(p4.getX(), p4.getY());

    painter.drawLine(p1_, p2_);
    painter.drawLine(p2_, p3_);
    painter.drawLine(p3_, p4_);
    painter.drawLine(p4_, p1_);
}

QString Quadrado::toString() const {
    return QString("Quadrado: P1(%1, %2), P2(%3, %4), Cor: %6")
    .arg(p1.getX())
        .arg(p1.getY())
        .arg(p2.getX())
        .arg(p2.getY())
        .arg(cor.name());
}

void Quadrado::aplicarTransformacao(const Matriz& transformacao) {
    // Calcula o centro do quadrado (média das coordenadas dos 2 pontos)
    double cx = (p1.getX() + p2.getX()) / 2.0;
    double cy = (p1.getY() + p2.getY()) / 2.0;
    Ponto centro(cx, cy, p1.getCor()); // A cor aqui é irrelevante, apenas para construir o objeto

    Ponto novoP1 = p1;
    Ponto novoP2 = p2;
    Ponto novoP3 = p3;
    Ponto novoP4 = p4;

    novoP1.aplicarTransformacao(transformacao, centro);
    novoP2.aplicarTransformacao(transformacao, centro);
    novoP3.aplicarTransformacao(transformacao, centro);
    novoP4.aplicarTransformacao(transformacao, centro);

    p1 = novoP1;
    p2 = novoP2;
    p3 = novoP3;
    p4 = novoP4;
}

void Quadrado::normalizar() {
    p1.normalizar();
    p2.normalizar();
}

bool Quadrado::eh3D() const {
    return p1.eh3D() || p2.eh3D();
}
