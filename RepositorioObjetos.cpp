#include "RepositorioObjetos.h"

void RepositorioObjetos::adicionar(std::unique_ptr<ObjetoGrafico> obj) {
    objetos.push_back(std::move(obj));
}

void RepositorioObjetos::atualizar(int indice, std::unique_ptr<ObjetoGrafico> novo) {
    if (indice >= 0 && indice < static_cast<int>(objetos.size())) {
        objetos[indice] = std::move(novo);
    }
}

void RepositorioObjetos::remover(int indice) {
    if (indice >= 0 && indice < static_cast<int>(objetos.size())) {
        objetos.erase(objetos.begin() + indice);
    }
}

void RepositorioObjetos::limpar() {
    objetos.clear();
}

const std::vector<std::unique_ptr<ObjetoGrafico>>& RepositorioObjetos::obterTodos() const {
    return objetos;
}
