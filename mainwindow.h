#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>

#include "RepositorioObjetos.h"
#include "Ponto.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnDesenhar_clicked();

    void on_btnCor_clicked();

    void atualizarCamposForma(const QString& formaSelecionada);

    void on_btnMostrar_clicked();

    void on_cbDisplayFile_currentIndexChanged(int index);

    void on_btnExcluirForma_clicked();

    void on_btnEditarForma_clicked();

private:
    Ui::MainWindow *ui;
    QColor corSelecionada;
    int indiceSelecionado;
    RepositorioObjetos repositorio;
    void atualizarCBDisplayFile();
};

#endif // MAINWINDOW_H
