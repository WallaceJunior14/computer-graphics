#include "FrameDesenho.h"
#include "FormaFactory.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

FrameDesenho::FrameDesenho(QWidget* parent)
    : QFrame(parent), repo(nullptr),
    windowSCN(0.0, 0.0, 1.0, 1.0), // Inicializa com a janela SCN padrão [0, 1] x [0, 1]
    viewportSCN(0.0, 0.0, 1.0, 1.0) // Inicializa com a viewport SCN padrão [0, 1] x [0, 1]
{
    setFrameShape(QFrame::Box);
    setLineWidth(10);
    setMinimumSize(400, 400);
}

void FrameDesenho::setRepositorio(RepositorioObjetos* repo) {
    this->repo = repo;
    update();
}

void FrameDesenho::setWindowSCN(double minX, double minY, double maxX, double maxY) {
    windowSCN = QRectF(minX, minY, maxX - minX, maxY - minY);
    update();
}

void FrameDesenho::setViewportSCN(double minX, double minY, double maxX, double maxY) {
    viewportSCN = QRectF(minX, minY, maxX - minX, maxY - minY);
    update();
}

QPointF FrameDesenho::transformarParaViewport(const QPointF& pontoSCN) const {
    double xViewport = (pontoSCN.x() - windowSCN.left()) / windowSCN.width() * viewportSCN.width() + viewportSCN.left();
    double yViewport = (1.0 - (pontoSCN.y() - windowSCN.top()) / windowSCN.height()) * viewportSCN.height() + viewportSCN.top();

    // Multiplica pelas dimensões do FrameDesenho para obter coordenadas de pixel
    double xPixel = xViewport * width();
    double yPixel = yViewport * height();

    return QPointF(xPixel, yPixel);
}

void FrameDesenho::paintEvent(QPaintEvent* event) {
    QFrame::paintEvent(event);
    if (!repo) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing); // Opcional: para desenhos mais suaves

    for (const auto& obj : repo->obterTodos()) {
        if (obj) {
            QPainterPath path; // Usaremos QPainterPath para construir as formas transformadas

            if (auto ponto = dynamic_cast<Ponto*>(obj.get())) {
                QPointF pontoSCN(ponto->getX(), ponto->getY());
                QPointF pontoViewport = transformarParaViewport(pontoSCN);
                p.setPen(obj->getPen());
                p.drawPoint(pontoViewport);
            } else if (auto reta = dynamic_cast<Reta*>(obj.get())) {
                QPointF p1SCN(reta->getP1().getX(), reta->getP1().getY());
                QPointF p2SCN(reta->getP2().getX(), reta->getP2().getY());
                QPointF p1Viewport = transformarParaViewport(p1SCN);
                QPointF p2Viewport = transformarParaViewport(p2SCN);
                p.setPen(obj->getPen());
                p.drawLine(p1Viewport, p2Viewport);
            } else if (auto quadrado = dynamic_cast<Quadrado*>(obj.get())) {
                QPointF p1SCN(quadrado->getP1().getX(), quadrado->getP1().getY());
                QPointF p2SCN(quadrado->getP2().getX(), quadrado->getP2().getY());
                QPointF p3SCN(quadrado->getP3().getX(), quadrado->getP3().getY());
                QPointF p4SCN(quadrado->getP4().getX(), quadrado->getP4().getY());
                QPointF p1Viewport = transformarParaViewport(p1SCN);
                QPointF p2Viewport = transformarParaViewport(p2SCN);
                QPointF p3Viewport = transformarParaViewport(p3SCN);
                QPointF p4Viewport = transformarParaViewport(p4SCN);
                p.setPen(obj->getPen());
                path.moveTo(p1Viewport);
                path.lineTo(p3Viewport); // Mantendo a ordem original do seu código
                path.lineTo(p2Viewport);
                path.lineTo(p4Viewport);
                path.lineTo(p1Viewport);
                p.drawPath(path);
            } else if (auto triangulo = dynamic_cast<Triangulo*>(obj.get())) {
                QPointF p1SCN(triangulo->getP1().getX(), triangulo->getP1().getY());
                QPointF p2SCN(triangulo->getP2().getX(), triangulo->getP2().getY());
                QPointF p3SCN(triangulo->getP3().getX(), triangulo->getP3().getY());
                QPointF p1Viewport = transformarParaViewport(p1SCN);
                QPointF p2Viewport = transformarParaViewport(p2SCN);
                QPointF p3Viewport = transformarParaViewport(p3SCN);
                p.setPen(obj->getPen());
                path.moveTo(p1Viewport);
                path.lineTo(p2Viewport);
                path.lineTo(p3Viewport);
                path.lineTo(p1Viewport);
                p.drawPath(path);
            } else if (auto circunferencia = dynamic_cast<Circunferencia*>(obj.get())) {
                QPointF centroSCN(circunferencia->getP1().getX(), circunferencia->getP1().getY());
                QPointF centroViewport = transformarParaViewport(centroSCN);
                // Precisamos transformar o raio também, proporcionalmente à menor dimensão da Window/Viewport
                double raioSCN = circunferencia->getRaio();
                double escalaX = viewportSCN.width() / windowSCN.width();
                double escalaY = viewportSCN.height() / windowSCN.height();
                double raioViewport = raioSCN * qMin(escalaX, escalaY) * width(); // Multiplica pela largura para ter em pixels

                p.setPen(obj->getPen());
                p.drawEllipse(centroViewport, raioViewport, raioViewport);
            }
        }
    }
}

void FrameDesenho::adicionarForma(const QString& tipo, double x1, double y1, double x2, double y2, double x3, double y3, double raio, QColor cor, int indice) {
    if (!repo || !cor.isValid()) return;

    ObjetoGrafico* objeto = nullptr;

    if (tipo == "Ponto") {
        objeto = FormaFactory::instance().criarSimples(tipo, x1, y1, cor);
    } else if (tipo == "Reta" || tipo == "Quadrado") {
        objeto = FormaFactory::instance().criarComplexa(tipo, x1, y1, x2, y2, cor);
    } else if (tipo == "Triangulo") {
        objeto = FormaFactory::instance().criarTriangulo(tipo, x1, y1, x2, y2, x3, y3, cor);
    } else if (tipo == "Circunferencia") {
        objeto = FormaFactory::instance().criarCircunferencia(tipo, x1, y1, raio, cor);
    }

    if (!objeto) return;

    if (indice >= 0 && indice < static_cast<int>(repo->obterTodos().size())) {
        repo->atualizar(indice, std::unique_ptr<ObjetoGrafico>(objeto));
    } else {
        repo->adicionar(std::unique_ptr<ObjetoGrafico>(objeto));
    }

    update();
}
