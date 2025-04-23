#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>

#include "Matriz.h"
#include "RepositorioObjetos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Botão para adicionar (desenhar) forma
    void on_btnDesenhar_clicked();

    // Botão para selecionar cor
    void on_btnCor_clicked();

    void on_cbDisplayFile_currentIndexChanged(int index);
    void on_btnExcluirForma_clicked();

    // Função para resetar a seleção da displayFile na tela.
    void resetarSelecao();

    // Função para atualizar os campos pela forma selecionada.
    void atualizarCamposForma(const QString& formaSelecionada);

    // Botão para as trasnformações geométricas
    void on_btnTransformar_clicked();

    // Função para atualizar combo box
    void atualizarComboBox();

    // Função para realizar as transformações geométricas
    void realizarTransformacao(Matriz transformacao);

private:
    Ui::MainWindow *ui;
    QColor corSelecionada;
    int indiceSelecionado;
    RepositorioObjetos repositorio;
    void atualizarCBDisplayFile();
};

#endif // MAINWINDOW_H
