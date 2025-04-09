#pragma once
#include <vector>
#include <memory>
#include "ObjetoGrafico.h"

class RepositorioObjetos {
public:
    void adicionar(std::unique_ptr<ObjetoGrafico> obj);

    void atualizar(int indice, std::unique_ptr<ObjetoGrafico> novo);

    void remover(int indice);

    void limpar();

    const std::vector<std::unique_ptr<ObjetoGrafico>>& obterTodos() const;


private:
    std::vector<std::unique_ptr<ObjetoGrafico>> objetos;
};
