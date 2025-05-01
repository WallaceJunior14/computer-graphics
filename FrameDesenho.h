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
    explicit FrameDesenho(QWidget* parent = nullptr);

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

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    RepositorioObjetos* repo;
};

#endif // FRAMEDESENHO_H
