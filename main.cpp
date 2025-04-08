#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "FormaFactory.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Registrar formas
    FormaFactory::instance().registrarSimples("Ponto", [](int x, int y, int tamanho, const QColor& cor) {
        return new Ponto(x, y, tamanho, cor);
    });

    FormaFactory::instance().registrarComplexa("Reta", [](int x1, int y1, int x2, int y2, int tamanho, const QColor& cor) {
        Ponto p1(x1, y1, tamanho, cor);
        Ponto p2(x2, y2, tamanho, cor);
        return new Reta(p1, p2, tamanho, cor);
    });


    MainWindow w;
    w.show();

    return app.exec();
}
