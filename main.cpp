#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "FormaFactory.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Registrar formas
    FormaFactory::instance().registrar("Ponto", [](int x, int y, int tamanho, const QColor& cor) {
        return new Ponto(x, y, tamanho, cor);
    });

    /*
    FormaFactory::instance().registrar("Reta", [](int x, int y, const QColor& cor) {
        return new Reta(x, y, x + 50, y + 50, cor);  // exemplo de reta
    });

    */

    MainWindow w;
    w.show();

    return app.exec();
}
