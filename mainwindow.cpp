#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FrameDesenho.h"
#include "FormaFactory.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configura a conexão com o repositório uma vez
    ui->frameDesenho->setRepositorio(&repositorio);

    // Formas para seleção
    QStringList formas = FormaFactory::instance().nomesFormas();
    ui->comboFormas->addItems(formas);

    // Conectar manualmente (caso não tenha feito via Qt Designer -> Sinais/Slots)
    connect(ui->btnDesenhar, &QPushButton::clicked, this, &MainWindow::on_btnDesenhar_clicked);
    connect(ui->btnCor, &QPushButton::clicked, this, &MainWindow::on_btnCor_clicked);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnDesenhar_clicked() {
    QString forma = ui->comboFormas->currentText();

    if (!corSelecionada.isValid()) {
        QMessageBox::warning(this, "Aviso", "Escolha uma cor antes de desenhar.");
        return;
    }

    // Obtendo as coordenadas dos spinBoxes
    int x = ui->spinX->value();
    int y = ui->spinY->value();
    int tamanho = ui->spinTamanho->value();

    // Criar objeto com base na forma selecionada
    ObjetoGrafico* objeto = FormaFactory::instance().criar(forma, x, y, tamanho, corSelecionada);

    if (objeto) {
        repositorio.adicionar(std::unique_ptr<ObjetoGrafico>{objeto});
        ui->frameDesenho->setRepositorio(&repositorio);
        ui->frameDesenho->update();
    } else {
        QMessageBox::warning(this, "Erro", "Forma não reconhecida: " + forma);
    }
}


void MainWindow::on_btnCor_clicked() {
    QColor novaCor = QColorDialog::getColor(Qt::black, this, "Escolher Cor");

    if (novaCor.isValid()) {
        corSelecionada = novaCor;
        qDebug() << "Cor selecionada:" << corSelecionada.name();
    }
}
