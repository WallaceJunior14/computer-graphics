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
    connect(ui->comboFormas, &QComboBox::currentTextChanged,
            this, &MainWindow::atualizarCamposForma);
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
    int x1 = ui->spinX1->value();
    int y1 = ui->spinY1->value();
    int x2 = ui->spinX2->value();
    int y2 = ui->spinY2->value();
    int tamanho = ui->spinTamanho->value();

    // Criar objeto com base na forma selecionada
    ObjetoGrafico* objeto = nullptr;

    if (forma == "Ponto") {
        objeto = FormaFactory::instance().criar(forma, x1, y1, tamanho, corSelecionada);
    } else if (forma == "Reta"){
        objeto = FormaFactory::instance().criar(forma, x1, y1, x2, y2, tamanho, corSelecionada);
    }

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


void MainWindow::atualizarCamposForma(const QString& formaSelecionada) {
    qDebug() << formaSelecionada;

    // Esconder todos inicialmente
    ui->spinX1->hide();
    ui->spinY1->hide();
    ui->spinX1->hide();
    ui->spinY1->hide();
    ui->spinX2->hide();
    ui->spinY2->hide();

    if (formaSelecionada == "Ponto") {
        ui->spinX1->show();
        ui->spinY1->show();
    } else if (formaSelecionada == "Reta") {
        ui->spinX1->show();
        ui->spinY1->show();
        ui->spinX2->show();
        ui->spinY2->show();
    }
}


