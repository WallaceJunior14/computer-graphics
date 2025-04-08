// ObjetoGrafico.h
#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#include <QPainter>
#include <QString>

class ObjetoGrafico {
public:
    ObjetoGrafico();

    virtual void desenhar(QPainter& painter) const = 0;

    virtual ~ObjetoGrafico() = default;

    virtual QString toString() const = 0;
};

#endif // OBJETOGRAFICO_H
