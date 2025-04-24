#include "mainwindow.h"
#include <QApplication>
#include "FormaFactory.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Registrar formas
    FormaFactory::instance().registrarSimples("Ponto", [](double x, double y, const QColor& cor) {
        return new Ponto(x, y, cor);
    });

    FormaFactory::instance().registrarComplexa("Reta", [](double x1, double y1, double x2, double y2, const QColor& cor) {
        Ponto p1(x1, y1, cor);
        Ponto p2(x2, y2, cor);
        return new Reta(p1, p2, cor);
    });

    FormaFactory::instance().registrarTriangulo("Triangulo", [](double x1, double y1, double x2, double y2, double x3, double y3, const QColor& cor) {
        Ponto p1(x1, y1, cor);
        Ponto p2(x2, y2, cor);
        Ponto p3(x3, y3, cor);
        return new Triangulo(p1, p2, p3, cor);
    });

    FormaFactory::instance().registrarComplexa("Quadrado", [](double x1, double y1, double x2, double y2, const QColor& cor) {
        Ponto p1(x1, y1, cor);
        Ponto p2(x2, y2, cor);
        Ponto p3(x1, y2, cor);
        Ponto p4(x2, y1, cor);
        return new Quadrado(p1, p2, p3, p4, cor);
    });

    FormaFactory::instance().registrarCircunferencia("Circunferencia", [](double x1, double y1, double raio, const QColor& cor) {
        Ponto p1(x1, y1, cor);
        return new Circunferencia(p1, raio, cor);
    });

    MainWindow w;
    w.show();

    return app.exec();
}
