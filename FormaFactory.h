#ifndef FORMAFACTORY_H
#define FORMAFACTORY_H

#include <QString>
#include <QColor>
#include <QMap>
#include <functional>
#include <memory>
#include "Ponto.h"
// inclua outras formas aqui

class FormaFactory {
public:
    using CriadorForma = std::function<ObjetoGrafico*(int x, int y, int tamanho, const QColor&)>;

    static FormaFactory& instance() {
        static FormaFactory inst;
        return inst;
    }

    void registrar(const QString& nome, CriadorForma criador) {
        formas[nome] = criador;
    }

    QStringList nomesFormas() const {
        return formas.keys();
    }

    ObjetoGrafico* criar(const QString& nome, int x, int y, int tamanho, const QColor& cor) {
        if (formas.contains(nome)) {
            return formas[nome](x, y, tamanho, cor);
        }
        return nullptr;
    }

private:
    QMap<QString, CriadorForma> formas;
};

#endif // FORMAFACTORY_H
