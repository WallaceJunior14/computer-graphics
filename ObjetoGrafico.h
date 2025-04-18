#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#include <QPainter>
#include <QString>
#include <QColor>

// Classe abstrata para as formas (ponto, reta...).
class ObjetoGrafico {
protected:
    QColor cor;
    int tamanho;
    int raio;

public:
    ObjetoGrafico(){};
    ObjetoGrafico(const QColor& cor) : cor(cor), tamanho(1), raio(1) {}
    virtual ~ObjetoGrafico() = default;

    // Função para desenhar no frame.
    virtual void desenhar(QPainter& painter) const = 0;

    // Função para pegar todas as informações do objeto;.
    virtual QString toString() const = 0;

    // Getters e Setters
    virtual QColor getCor() const { return cor; }
    virtual void setCor(const QColor& novaCor) { cor = novaCor; }

    virtual int getTamanho() const { return tamanho; }
    virtual void setTamanho(int novoTamanho) { tamanho = novoTamanho; }

    virtual int getRaio() const { return raio; }
    virtual void setRaio(int novoRaio) { tamanho = novoRaio; }

    virtual QPen getPen() const {
        QPen pen(cor);
        pen.setWidth(tamanho);
        return pen;
    }
};

#endif // OBJETOGRAFICO_H
