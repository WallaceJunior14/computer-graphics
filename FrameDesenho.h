#ifndef FRAMEDESENHO_H
#define FRAMEDESENHO_H

#include <QFrame>
#include <QColor>
#include "RepositorioObjetos.h"

// Frame Personalizado
class FrameDesenho : public QFrame {
    Q_OBJECT
public:
    explicit FrameDesenho(QWidget* parent = nullptr);

    // Cria ou Atualiza a forma e guarda no repositório.
    void adicionarForma(const QString& tipo,
                        int x1, int y1,
                        int x2 = 0, int y2 = 0,
                        int x3 = 0, int y3 = 0,
                        int raio = 0,
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
