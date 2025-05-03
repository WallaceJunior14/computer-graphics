#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>

#include "Matriz.h"
#include "RepositorioObjetos.h"
#include "FrameDesenho.h"
#include "Ponto.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QColor corSelecionada;
    int indiceSelecionado;
    RepositorioObjetos repositorio;

    // Funções auxiliares
    void atualizarCBDisplayFile();
    void resetarSelecao();
    void atualizarCamposForma(const QString& formaSelecionada);
    void atualizarComboBox();
    void realizarTransformacao(Matriz transformacao);

private slots:
    void on_btnDesenhar_clicked();
    void on_btnCor_clicked();
    void on_cbDisplayFile_currentIndexChanged(int index);
    void on_btnExcluirForma_clicked();
    void on_btnTransformar_clicked();
    void on_btnChangeWindow_clicked();
    void on_spinWMinX_valueChanged(double arg1);
    void on_spinWMinY_valueChanged(double arg1);
    void on_spinWMaxX_valueChanged(double arg1);
    void on_spinWMaxY_valueChanged(double arg1);
    void on_spinVMinX_valueChanged(double arg1);
    void on_spinVMinY_valueChanged(double arg1);
    void on_spinVMaxX_valueChanged(double arg1);
    void on_spinVMaxY_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
