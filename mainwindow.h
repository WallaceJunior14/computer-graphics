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

    // Parâmetros da Window (em unidades do mundo - cm)
    double wxmin = -5.0;
    double wymin = -5.0;
    double wxmax = 15.0;
    double wymax = 15.0;

    // Parâmetros da Viewport (em pixels do FrameDesenho)
    int vxmin = 0;
    int vymin = 0;
    int vxmax = 400; // tamanho padrão inicial do FrameDesenho
    int vymax = 400;

    QPoint transformarCoordenada(double x, double y) const;

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
    void on_windowParametrosAlterados();
    void on_viewportParametrosAlterados();
    void on_spinWxMin_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
