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

    // Conecta o repositório ao frame uma única vez
    ui->frameDesenho->setRepositorio(&repositorio);

    // Carrega as formas disponíveis
    QStringList formas = FormaFactory::instance().nomesFormas();
    ui->comboFormas->addItems(formas);

    // Ajusta campos de entrada com base na primeira forma
    QString forma = ui->comboFormas->itemText(0);
    atualizarCamposForma(forma);

    // ⚠️ Comente esta linha se você já ligou o botão no Qt Designer
    // connect(ui->btnDesenhar, &QPushButton::clicked, this, &MainWindow::on_btnDesenhar_clicked);
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

    int x1 = ui->spinX1->value();
    int y1 = ui->spinY1->value();
    int x2 = ui->spinX2->value();
    int y2 = ui->spinY2->value();
    int x3 = ui->spinX3->value();
    int y3 = ui->spinY3->value();
    int tamanho = ui->spinTamanho->value();

    ObjetoGrafico* objeto = nullptr;

    if (forma == "Ponto") {
        objeto = FormaFactory::instance().criar(forma, x1, y1, tamanho, corSelecionada);
    } else if (forma == "Reta" || forma == "Quadrado") {
        objeto = FormaFactory::instance().criar(forma, x1, y1, x2, y2, tamanho, corSelecionada);
    } else if (forma == "Triangulo") {
        objeto = FormaFactory::instance().criar(forma, x1, y1, x2, y2, x3, y3, tamanho, corSelecionada);
    }

    if (objeto) {
        repositorio.adicionar(std::unique_ptr<ObjetoGrafico>{objeto});
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

    ui->spinX2->hide();
    ui->spinY2->hide();
    ui->spinX3->hide();
    ui->spinY3->hide();

    ui->lblCoordenadaX2->hide();
    ui->lblCoordenadaY2->hide();
    ui->lblCoordenadaX3->hide();
    ui->lblCoordenadaY3->hide();

    if (formaSelecionada == "Reta" || formaSelecionada == "Quadrado") {
        ui->spinX2->show();
        ui->spinY2->show();
        ui->lblCoordenadaX2->show();
        ui->lblCoordenadaY2->show();
    } else if (formaSelecionada == "Triangulo") {
        ui->spinX2->show();
        ui->spinY2->show();
        ui->spinX3->show();
        ui->spinY3->show();
        ui->lblCoordenadaX2->show();
        ui->lblCoordenadaY2->show();
        ui->lblCoordenadaX3->show();
        ui->lblCoordenadaY3->show();
    }
}

void MainWindow::on_comboFormas_activated(int index) {
    atualizarCamposForma(ui->comboFormas->itemText(index));
}

void MainWindow::on_btnMostrar_clicked() {
    const auto& formas = repositorio.obterTodos();
    for (const auto& forma : formas) {
        qDebug() << forma->toString();
    }
}
