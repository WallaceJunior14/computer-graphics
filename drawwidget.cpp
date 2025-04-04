#include "drawwidget.h"
#include <QPainter>
#include <QPolygon>
#include <QMouseEvent>

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget(parent), desenharFormas(false), desenharPontosRetas(false)
{
    corFormas = Qt::red;
    posCirculo = QPoint(20, 20); // posição inicial
}


void DrawWidget::mostrarFormas(bool mostrar) {
    desenharFormas = mostrar;
    update();
}

void DrawWidget::mostrarPontosRetas(bool mostrar) {
    desenharPontosRetas = mostrar;
    update();
}

void DrawWidget::setCor(const QColor &cor) {
    corFormas = cor;
    update();
}

void DrawWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(corFormas);
    painter.drawEllipse(posCirculo.x(), posCirculo.y(), 60, 60);

    if (desenharFormas) {
        // Círculo
        painter.setBrush(corFormas);
        painter.drawEllipse(20, 20, 60, 60);

        // Quadrado
        painter.setBrush(corFormas.darker(110));
        painter.drawRect(100, 20, 60, 60);

        // Triângulo
        painter.setBrush(corFormas.lighter(120));
        QPolygon triangle;
        triangle << QPoint(200, 80) << QPoint(230, 20) << QPoint(260, 80);
        painter.drawPolygon(triangle);
    }

    if (desenharPontosRetas) {
        // Pontos
        painter.setPen(QPen(Qt::black, 8));
        painter.drawPoint(50, 120);
        painter.drawPoint(100, 120);
        painter.drawPoint(150, 120);
        painter.drawPoint(200, 120);
        painter.drawPoint(250, 120);
        painter.drawPoint(300, 120);
        painter.drawPoint(350, 120);
        painter.drawPoint(400, 120);

        // Retas
        painter.setPen(QPen(Qt::darkMagenta, 2));
        painter.drawLine(50, 160, 150, 160);
        painter.drawLine(50, 160, 100, 200);
        painter.drawLine(100, 100, 120, 200);
        painter.drawLine(200, 50, 180, 120);
        painter.drawLine(100, 100, 120, 200);
    }
}

void DrawWidget::mousePressEvent(QMouseEvent *event) {
    QRect circuloRect(posCirculo, QSize(60, 60));
    if (circuloRect.contains(event->pos())) {
        arrastando = true;
    }
}

void DrawWidget::mouseMoveEvent(QMouseEvent *event) {
    if (arrastando) {
        posCirculo = event->pos() - QPoint(30, 30); // centraliza o clique
        update();
    }
}




