#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FrameDesenho.h"
#include "FormaFactory.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    indiceSelecionado(-1)
{

    ui->setupUi(this);

    // Conecta o repositório ao frame uma única vez
    ui->frameDesenho->setRepositorio(&repositorio);

    // Log -> mostrar lista de repositorio : desativado
    ui->btnMostrar->hide();

    // Carrega as formas disponíveis
    ui->comboFormas->addItems(FormaFactory::instance().nomesFormas());

    // Ajusta campos de entrada com base na primeira forma
    atualizarCamposForma(ui->comboFormas->itemText(0));

    connect(ui->comboFormas, &QComboBox::currentTextChanged,
            this, &MainWindow::atualizarCamposForma);
    connect(ui->cbDisplayFile, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_cbDisplayFile_currentIndexChanged);
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

    int x1 = ui->spinX1->value(), y1 = ui->spinY1->value();
    int x2 = ui->spinX2->value(), y2 = ui->spinY2->value();
    int x3 = ui->spinX3->value(), y3 = ui->spinY3->value();
    int tamanho = ui->spinTamanho->value();

    ObjetoGrafico* objeto = nullptr;

    if (forma == "Ponto") {
        objeto = FormaFactory::instance().criar(forma, x1, y1, tamanho, corSelecionada);
    } else if (forma == "Reta" || forma == "Quadrado") {
        objeto = FormaFactory::instance().criar(forma, x1, y1, x2, y2, tamanho, corSelecionada);
    } else if (forma == "Triangulo") {
        objeto = FormaFactory::instance().criar(forma, x1, y1, x2, y2, x3, y3, tamanho, corSelecionada);
    }

    if (!objeto) {
        QMessageBox::warning(this, "Erro", "Forma não reconhecida: " + forma);
        return;
    }

    if (indiceSelecionado >= 0 && indiceSelecionado < static_cast<int>(repositorio.obterTodos().size())) {
        repositorio.atualizar(indiceSelecionado, std::unique_ptr<ObjetoGrafico>(objeto));
        indiceSelecionado = -1;
    } else {
        repositorio.adicionar(std::unique_ptr<ObjetoGrafico>(objeto));
    }

    atualizarCBDisplayFile();
    ui->cbDisplayFile->setCurrentIndex(-1);
    ui->frameDesenho->update();
}

void MainWindow::on_btnCor_clicked() {
    QColor novaCor = QColorDialog::getColor(Qt::black, this, "Escolher Cor");

    if (novaCor.isValid()) {
        corSelecionada = novaCor;
        qDebug() << "Cor selecionada:" << corSelecionada.name();
    }
}

void MainWindow::on_btnMostrar_clicked() {
    for (const auto& forma : repositorio.obterTodos()) {
        qDebug() << forma->toString();
    }
}

void MainWindow::atualizarCamposForma(const QString& formaSelecionada) {
    static const QList<QWidget*> campos2 = {
        ui->spinX2, ui->spinY2, ui->lblCoordenadaX2, ui->lblCoordenadaY2
    };
    static const QList<QWidget*> campos3 = {
        ui->spinX3, ui->spinY3, ui->lblCoordenadaX3, ui->lblCoordenadaY3
    };

    for (QWidget* campo : campos2 + campos3) campo->hide();

    if (formaSelecionada == "Reta" || formaSelecionada == "Quadrado") {
        for (QWidget* campo : campos2) campo->show();
    } else if (formaSelecionada == "Triangulo") {
        for (QWidget* campo : campos2 + campos3) campo->show();
    }
}

void MainWindow::atualizarCBDisplayFile() {
    ui->cbDisplayFile->clear();
    for (const auto& forma : repositorio.obterTodos()) {
        ui->cbDisplayFile->addItem(forma->toString());
    }
}

void MainWindow::on_cbDisplayFile_currentIndexChanged(int index)
{
    if (index < 0 || index >= static_cast<int>(repositorio.obterTodos().size())) {
        indiceSelecionado = -1;
        return;
    }

    const auto& forma = repositorio.obterTodos().at(index);
    indiceSelecionado = index;

    // Aqui você pode usar RTTI para verificar o tipo
    if (auto ponto = dynamic_cast<const Ponto*>(forma.get())) {
        ui->comboFormas->setCurrentText("Ponto");
        ui->spinX1->setValue(ponto->getX());
        ui->spinY1->setValue(ponto->getY());
    } else if (auto reta = dynamic_cast<const Reta*>(forma.get())) {
        ui->comboFormas->setCurrentText("Reta");
        ui->spinX1->setValue(reta->getP1().getX());
        ui->spinY1->setValue(reta->getP1().getY());
        ui->spinX2->setValue(reta->getP2().getX());
        ui->spinY2->setValue(reta->getP2().getY());
    } else if (auto quad = dynamic_cast<const Quadrado*>(forma.get())) {
        ui->comboFormas->setCurrentText("Quadrado");
        ui->spinX1->setValue(quad->getP1().getX());
        ui->spinY1->setValue(quad->getP1().getY());
        ui->spinX2->setValue(quad->getP2().getX());
        ui->spinY2->setValue(quad->getP2().getY());
    } else if (auto tri = dynamic_cast<const Triangulo*>(forma.get())) {
        ui->comboFormas->setCurrentText("Triangulo");
        ui->spinX1->setValue(tri->getP1().getX());
        ui->spinY1->setValue(tri->getP1().getY());
        ui->spinX2->setValue(tri->getP2().getX());
        ui->spinY2->setValue(tri->getP2().getY());
        ui->spinX3->setValue(tri->getP3().getX());
        ui->spinY3->setValue(tri->getP3().getY());
    }

    ui->spinTamanho->setValue(forma->getTamanho());
    corSelecionada = forma->getCor();

    indiceSelecionado = index;
}

