#ifndef FRAMEDESENHO_H
#define FRAMEDESENHO_H

#include <QFrame>
#include <QColor>
#include "RepositorioObjetos.h"
#include "mainwindow.h"

// Frame Personalizado
class FrameDesenho : public QFrame {
    Q_OBJECT
public:
    explicit FrameDesenho(QWidget* parent = nullptr, MainWindow* mainWindow = nullptr); // Corrigido!

    // Cria ou Atualiza a forma e guarda no repositório
    void adicionarForma(const QString& tipo,
                        double x1, double y1,
                        double x2 = 0, double y2 = 0,
                        double x3 = 0, double y3 = 0,
                        double raio = 0,
                        QColor cor = Qt::black,
                        int indice = -1);

    // Setters
    void setRepositorio(RepositorioObjetos* repo);

    // Métodos para configurar window e viewport
    void setWindow(double wxmin, double wymin, double wxmax, double wymax);
    void setViewport(int vxmin, int vymin, int vxmax, int vymax);

    QPoint transformarCoordenada(double x, double y) const;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    RepositorioObjetos* repo;
    double wxmin, wymin, wxmax, wymax;
    int vxmin, vymin, vxmax, vymax;
    MainWindow* mainWindow; // Ponteiro para MainWindow
};

#endif // FRAMEDESENHO_H
