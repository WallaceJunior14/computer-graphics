#pragma once
#include <vector>
#include <memory>
#include "ObjetoGrafico.h"

// Classe para guardar as formas geradas na tela (seria o DisplayFile).
class RepositorioObjetos {
public:
    // Adiciona a forma na lista.
    void adicionar(std::unique_ptr<ObjetoGrafico> obj);

    // Atualiza a forma na lista.
    void atualizar(int indice, std::unique_ptr<ObjetoGrafico> novo);

    // Remove a forma na lista.
    void remover(int indice);

    // Limpa a lista.
    void limpar();

    // Função para pegar todos os objetos da lista.
    const std::vector<std::unique_ptr<ObjetoGrafico>>& obterTodos() const;


private:
    std::vector<std::unique_ptr<ObjetoGrafico>> objetos;
};
