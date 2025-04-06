#include "RepositorioObjetos.h"

void RepositorioObjetos::adicionar(std::unique_ptr<ObjetoGrafico> obj) {
    objetos.push_back(std::move(obj));
}

const std::vector<std::unique_ptr<ObjetoGrafico>>& RepositorioObjetos::obterTodos() const {
    return objetos;
}

void RepositorioObjetos::limpar() {
    objetos.clear();
}
