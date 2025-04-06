// ObjetoGrafico.h
#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#include <QPainter>

class ObjetoGrafico {
public:
    ObjetoGrafico();
    virtual void desenhar(QPainter& painter) const = 0; // <- tem que ter const
    virtual ~ObjetoGrafico() = default;
};

#endif // OBJETOGRAFICO_H
