#pragma once
#include <vector>
#include <memory>
#include "ObjetoGrafico.h"

class RepositorioObjetos {
public:
    void adicionar(std::unique_ptr<ObjetoGrafico> obj);
    const std::vector<std::unique_ptr<ObjetoGrafico>>& obterTodos() const;
    void limpar();

private:
    std::vector<std::unique_ptr<ObjetoGrafico>> objetos;
};
