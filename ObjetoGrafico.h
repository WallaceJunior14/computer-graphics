#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#include <QPainter>
#include <QString>
#include <QColor>
class MainWindow;

// Classe abstrata para as formas (ponto, reta...).
class ObjetoGrafico {
protected:
    QColor cor;
    double tamanho;
    double raio;
    bool transformadoModelo = false;    // Para rotação, escala, translação
    bool transformadoViewport = false;  // Para window → viewport

public:
    ObjetoGrafico(){};
    ObjetoGrafico(const QColor& cor) : cor(cor), tamanho(1), raio(1) {}
    virtual ~ObjetoGrafico() = default;

    // Função para desenhar no frame.
    virtual void desenhar(QPainter& painter) const = 0;

    // Função para pegar todas as informações do objeto;.
    virtual QString toString() const = 0;

    // Para transformações de modelagem
    void marcarTransformadoModelo() { transformadoModelo = true; }
    void resetarTransformadoModelo() { transformadoModelo = false; }
    bool foiTransformadoModelo() const { return transformadoModelo; }

    // Para transformações de viewport
    void marcarTransformadoViewport() { transformadoViewport = true; }
    void resetarTransformadoViewport() { transformadoViewport = false; }
    bool foiTransformadoViewport() const { return transformadoViewport; }

    // Getters e Setters
    virtual QColor getCor() const { return cor; }
    virtual void setCor(const QColor& novaCor) { cor = novaCor; }

    virtual double getTamanho() const { return tamanho; }
    virtual void setTamanho(double novoTamanho) { tamanho = novoTamanho; }

    virtual double getRaio() const { return raio; }
    virtual void setRaio(double novoRaio) { tamanho = novoRaio; }

    virtual QPen getPen() const {
        QPen pen(cor);
        pen.setWidth(tamanho);
        return pen;
    }
};

#endif // OBJETOGRAFICO_H
