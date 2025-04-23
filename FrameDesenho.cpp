// FrameDesenho.cpp
#include "FrameDesenho.h"
#include "FormaFactory.h"
#include <QPainter>

FrameDesenho::FrameDesenho(QWidget* parent)
    : QFrame(parent), repo(nullptr) {
    setFrameShape(QFrame::Box);
    setLineWidth(10);
    setMinimumSize(400, 400);
}

void FrameDesenho::setRepositorio(RepositorioObjetos* repo) {
    this->repo = repo;
    update();
}

void FrameDesenho::paintEvent(QPaintEvent* event) {
    QFrame::paintEvent(event);
    if (!repo) return;

    QPainter p(this);
    for (const auto& obj : repo->obterTodos()) {
        obj->desenhar(p);
    }
}

void FrameDesenho::adicionarForma(const QString& tipo, double x1, double y1, double x2, double y2, double x3, double y3, double raio, QColor cor, int indice) {
    if (!repo || !cor.isValid()) return;

    ObjetoGrafico* objeto = nullptr;

    if (tipo == "Ponto") {
        objeto = FormaFactory::instance().criar(tipo, x1, y1, cor);
    } else if (tipo == "Reta" || tipo == "Quadrado") {
        objeto = FormaFactory::instance().criar(tipo, x1, y1, x2, y2, cor);
    } else if (tipo == "Triangulo") {
        objeto = FormaFactory::instance().criar(tipo, x1, y1, x2, y2, x3, y3, cor);
    } else if (tipo == "Circunferencia") {
        objeto = FormaFactory::instance().criar(tipo, x1, y1, raio, cor);
    }

    if (!objeto) return;

    if (indice >= 0 && indice < static_cast<int>(repo->obterTodos().size())) {
        repo->atualizar(indice, std::unique_ptr<ObjetoGrafico>(objeto));
    } else {
        repo->adicionar(std::unique_ptr<ObjetoGrafico>(objeto));
    }

    update();
}
