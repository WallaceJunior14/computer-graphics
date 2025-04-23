#include "Triangulo.h"

Triangulo::Triangulo(const Ponto& ponto1, const Ponto& ponto2, const Ponto& ponto3, const QColor& cor)
    : ObjetoGrafico(cor), p1(ponto1), p2(ponto2), p3(ponto3), cor(cor) {}

void Triangulo::desenhar(QPainter& painter) const {
    painter.setPen(getPen());
    painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    painter.drawLine(p2.getX(), p2.getY(), p3.getX(), p3.getY());
    painter.drawLine(p3.getX(), p3.getY(), p1.getX(), p1.getY());
}

QString Triangulo::toString() const {
    return QString("Triangulo((%1, %2), (%3, %4), (%5, %6), cor: %8)")
        .arg(p1.getX())
        .arg(p1.getY())
        .arg(p2.getX())
        .arg(p2.getY())
        .arg(p3.getX())
        .arg(p3.getY())
        .arg(cor.name());
}

void Triangulo::aplicarTransformacao(const Matriz& transformacao) {
    // Calcula o centro do triângulo (média das coordenadas dos 3 pontos)
    double cx = (p1.getX() + p2.getX() + p3.getX()) / 3.0;
    double cy = (p1.getY() + p2.getY() + p3.getY()) / 3.0;
    Ponto centro(cx, cy, p1.getCor()); // A cor aqui é irrelevante, apenas para construir o objeto

    Ponto novoP1 = p1;
    Ponto novoP2 = p2;
    Ponto novoP3 = p3;

    novoP1.aplicarTransformacao(transformacao, centro);
    novoP2.aplicarTransformacao(transformacao, centro);
    novoP3.aplicarTransformacao(transformacao, centro);

    p1 = novoP1;
    p2 = novoP2;
    p3 = novoP3;
}

void Triangulo::normalizar() {
    p1.normalizar();
    p2.normalizar();
    p3.normalizar();
}

bool Triangulo::eh3D() const {
    return p1.eh3D() || p2.eh3D() || p3.eh3D();
}
