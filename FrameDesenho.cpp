#include "FrameDesenho.h"
#include <QPainter>

FrameDesenho::FrameDesenho(QWidget* parent)
    :QFrame(parent), repo(nullptr){
    setFrameShape(QFrame::Box);
    setLineWidth(10);
    setMinimumSize(400, 400);
}

void FrameDesenho::setRepositorio(RepositorioObjetos *repo){
    this->repo = repo;
    update();
}

void FrameDesenho::paintEvent(QPaintEvent* event){
    QFrame::paintEvent(event); // CORREÇÃO AQUI

    if (!repo) return;

    QPainter p(this);
    for (const auto& obj : repo->obterTodos()) {
        obj->desenhar(p);
    }
}

