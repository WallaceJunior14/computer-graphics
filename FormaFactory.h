#ifndef FORMAFACTORY_H
#define FORMAFACTORY_H

#include <QString>
#include <QColor>
#include <QMap>
#include <functional>
#include <memory>
#include "Ponto.h"
#include "Reta.h"
#include "Triangulo.h"

class FormaFactory {
public:
    using CriadorFormaSimples = std::function<ObjetoGrafico*(int x, int y, int tamanho, const QColor&)>;
    using CriadorFormaComplexa = std::function<ObjetoGrafico*(int x1, int y1, int x2, int y2, int tamanho, const QColor&)>;
    using CriadorFormaTriangulo = std::function<ObjetoGrafico*(int x1, int y1, int x2, int y2, int x3, int y3, int tamanho, const QColor&)>;

    static FormaFactory& instance() {
        static FormaFactory inst;
        return inst;
    }

    void registrarSimples(const QString& nome, CriadorFormaSimples criador) {
        formasSimples[nome] = criador;
    }

    void registrarComplexa(const QString& nome, CriadorFormaComplexa criador) {
        formasComplexas[nome] = criador;
    }

    void registrarTriangulo(const QString& nome, CriadorFormaTriangulo criador) {
        formasTriangulo[nome] = criador;
    }

    QStringList nomesFormas() const {
        QStringList nomes = formasSimples.keys();
        nomes.append(formasComplexas.keys());
        nomes.append(formasTriangulo.keys());
        return nomes;
    }

    // Para formas simples
    ObjetoGrafico* criar(const QString& nome, int x, int y, int tamanho, const QColor& cor) {
        if (formasSimples.contains(nome)) {
            return formasSimples[nome](x, y, tamanho, cor);
        }
        return nullptr;
    }

    // Para formas complexas
    ObjetoGrafico* criar(const QString& nome, int x1, int y1, int x2, int y2, int tamanho, const QColor& cor) {
        if (formasComplexas.contains(nome)) {
            return formasComplexas[nome](x1, y1, x2, y2, tamanho, cor);
        }
        return nullptr;
    }

    // Para formas triangulo
    ObjetoGrafico* criar(const QString& nome, int x1, int y1, int x2, int y2, int x3, int y3, int tamanho, const QColor& cor) {
        if (formasTriangulo.contains(nome)) {
            return formasTriangulo[nome](x1, y1, x2, y2, x3, y3, tamanho, cor);
        }
        return nullptr;
    }

private:
    QMap<QString, CriadorFormaSimples> formasSimples;
    QMap<QString, CriadorFormaComplexa> formasComplexas;
    QMap<QString, CriadorFormaTriangulo> formasTriangulo;
};

#endif // FORMAFACTORY_H
