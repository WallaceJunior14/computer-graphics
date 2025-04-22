#include "Quadrado.h"

Quadrado::Quadrado(const Ponto& ponto1, const Ponto& ponto2, const QColor& cor)
    : ObjetoGrafico(cor), p1(ponto1), p2(ponto2), cor(cor) {}

void Quadrado::desenhar(QPainter& painter) const {
    painter.setPen(getPen());
    painter.drawLine(p1.getX(), p1.getY(), p1.getX(), p2.getY()); // lado esquerdo
    painter.drawLine(p1.getX(), p2.getY(), p2.getX(), p2.getY()); // lado inferior
    painter.drawLine(p2.getX(), p2.getY(), p2.getX(), p1.getY()); // lado direito
    painter.drawLine(p2.getX(), p1.getY(), p1.getX(), p1.getY()); // lado superior
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
    // Calcula o centro do triângulo (média das coordenadas dos 3 pontos)
    int cx = (p1.getX() + p2.getX()) / 2;
    int cy = (p1.getY() + p2.getY()) / 2;
    Ponto centro(cx, cy, p1.getCor()); // A cor aqui é irrelevante, apenas para construir o objeto

    Ponto novoP1 = p1;
    Ponto novoP2 = p2;

    novoP1.aplicarTransformacao(transformacao, centro);
    novoP2.aplicarTransformacao(transformacao, centro);

    p1 = novoP1;
    p2 = novoP2;
}

void Quadrado::normalizar() {
    p1.normalizar();
    p2.normalizar();
}

bool Quadrado::eh3D() const {
    return p1.eh3D() || p2.eh3D();
}
