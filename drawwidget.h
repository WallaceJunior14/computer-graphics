#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

class DrawWidget : public QWidget {
    Q_OBJECT

public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void mostrarFormas(bool mostrar);
    void mostrarPontosRetas(bool mostrar);
    void setCor(const QColor &cor);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    bool desenharFormas;
    bool desenharPontosRetas;
    QPoint posCirculo;
    bool arrastando = false;
    QColor corFormas;
};

#endif // DRAWWIDGET_H
