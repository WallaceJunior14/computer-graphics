#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#include <QPainter>
#include <QString>
#include <QColor>

class ObjetoGrafico {
protected:
    QColor cor;
    int tamanho;
    int raio;

public:
    ObjetoGrafico();
    virtual ~ObjetoGrafico() = default;

    virtual void desenhar(QPainter& painter) const = 0;
    virtual QString toString() const = 0;

    virtual QColor getCor() const { return cor; }
    virtual void setCor(const QColor& novaCor) { cor = novaCor; }

    virtual int getTamanho() const { return tamanho; }
    virtual void setTamanho(int novoTamanho) { tamanho = novoTamanho; }

    virtual int getRaio() const { return raio; }
    virtual void setRaio(int novoRaio) { tamanho = novoRaio; }
};

#endif // OBJETOGRAFICO_H
