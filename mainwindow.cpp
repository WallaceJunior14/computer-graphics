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

    // Conecta o repositório ao frame
    ui->frameDesenho->setRepositorio(&repositorio);

    // Log -> mostrar lista dos objetos no repositorio : desativado
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
    int raio = ui->spinRaio->value();

    ui->frameDesenho->adicionarForma(forma, x1, y1, x2, y2, x3, y3, raio, corSelecionada, indiceSelecionado);

    MainWindow::atualizarCBDisplayFile();
    MainWindow::resetarSelecao();
    update();
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
    ui->btnExcluirForma->hide();
    ui->lblRaio->hide();
    ui->spinRaio->hide();

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
    } else if (formaSelecionada == "Circunferencia") {
        ui->lblRaio->show();
        ui->spinRaio->show();
    }
}

void MainWindow::atualizarCBDisplayFile() {
    ui->cbDisplayFile->clear();
    for (const auto& forma : repositorio.obterTodos()) {
        ui->cbDisplayFile->addItem(forma->toString());
    }
}

void MainWindow::on_cbDisplayFile_currentIndexChanged(int index) {
    if (index < 0 || index >= static_cast<int>(repositorio.obterTodos().size())) {
        indiceSelecionado = -1;
        ui->btnDesenhar->setText("Adicionar");
        return;
    }

    const auto& forma = repositorio.obterTodos().at(index);
    indiceSelecionado = index;
    ui->btnDesenhar->setText("Editar");

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
    } else if (auto cir = dynamic_cast<const Circunferencia*>(forma.get())) {
        ui->comboFormas->setCurrentText("Circunferencia");
        ui->spinX1->setValue(cir->getP1().getX());
        ui->spinY1->setValue(cir->getP1().getY());
        ui->spinRaio->setValue(cir->getRaio());
    }

    corSelecionada = forma->getCor();

    ui->btnExcluirForma->show();
}

void MainWindow::resetarSelecao() {
    indiceSelecionado = -1;
    ui->cbDisplayFile->setCurrentIndex(-1);
    ui->btnExcluirForma->hide();
}

void MainWindow::on_btnExcluirForma_clicked() {
    if (indiceSelecionado != -1) {
        auto resposta = QMessageBox::question(this, "Confirmar exclusão",
                                              "Deseja realmente excluir a forma selecionada?",
                                              QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            repositorio.remover(indiceSelecionado);
            indiceSelecionado = -1;
            atualizarCBDisplayFile();
            ui->cbDisplayFile->setCurrentIndex(-1);
            ui->frameDesenho->update();
        }
    }
}


void MainWindow::on_btnTransformar_clicked()
{
    if (indiceSelecionado == -1) {
        QMessageBox::warning(this, "Aviso", "Nenhum objeto selecionado.");
        ui->spinTranslacaoX->setValue(0);
        ui->spinTranslacaoY->setValue(0);
        return;
    }

    double tx = ui->spinTranslacaoX->value();
    double ty = ui->spinTranslacaoY->value();

    if (tx == 0 || ty == 0) {
        QMessageBox::warning(this, "Erro", "Os fatores de translação não podem ser zero.");
        return;
    }

    Matriz translacao = Matriz::translacao2D(tx, ty);

    auto& forma = repositorio.obterTodos().at(indiceSelecionado);  // Recupera o objeto selecionado

    if (auto* ponto = dynamic_cast<Ponto*>(forma.get())) {
        ponto->aplicarTransformacao(translacao);
    } else if (auto* reta = dynamic_cast<Reta*>(forma.get())) {
        reta->aplicarTransformacao(translacao);
    } else if (auto* quadrado = dynamic_cast<Quadrado*>(forma.get())) {
        quadrado->aplicarTransformacao(translacao);
    } else if (auto* triangulo = dynamic_cast<Triangulo*>(forma.get())) {
        triangulo->aplicarTransformacao(translacao);
    }else if (auto* circunferencia = dynamic_cast<Circunferencia*>(forma.get())) {
        circunferencia->aplicarTransformacao(translacao);
    }

    atualizarComboBox();  // Chame um método para atualizar o ComboBox
    ui->frameDesenho->update();  // Atualiza a tela de desenho
    resetarSelecao();
}

// Função para atualizar o ComboBox com os novos dados
void MainWindow::atualizarComboBox() {
    ui->cbDisplayFile->clear();  // Limpa o ComboBox

    // Preenche o ComboBox novamente com os objetos atualizados
    for (const auto& forma : repositorio.obterTodos()) {
        ui->cbDisplayFile->addItem(forma->toString());  // Supondo que `toString()` retorne uma representação legível
    }

    // Opcional: Seleciona o item que estava anteriormente selecionado
    ui->cbDisplayFile->setCurrentIndex(indiceSelecionado);
}


