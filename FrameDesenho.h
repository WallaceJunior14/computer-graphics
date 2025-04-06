#ifndef FRAMEDESENHO_H
#define FRAMEDESENHO_H

#include <QFrame>
#include "RepositorioObjetos.h"

class FrameDesenho: public QFrame
{
    Q_OBJECT
public:
    explicit FrameDesenho(QWidget* parent = nullptr);
    void setRepositorio(RepositorioObjetos* repo);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    RepositorioObjetos* repo;

};

#endif // FRAMEDESENHO_H
