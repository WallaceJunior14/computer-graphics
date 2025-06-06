#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FrameDesenho.h"
#include "FormaFactory.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    indiceSelecionado(-1)
{
    ui->setupUi(this);

    // Conecta o repositório ao frame
    ui->frameDesenho->setRepositorio(&repositorio);

    // Carrega as formas disponíveis
    ui->comboFormas->addItems(FormaFactory::instance().nomesFormas());

    // Ajusta os campos baseado na primeira forma
    atualizarCamposForma(ui->comboFormas->itemText(0));

    // Conecta os sinais dos combos e botões aos seus respectivos slots
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

    double x1 = ui->spinX1->value(), y1 = ui->spinY1->value();
    double x2 = ui->spinX2->value(), y2 = ui->spinY2->value();
    double x3 = ui->spinX3->value(), y3 = ui->spinY3->value();
    double raio = ui->spinRaio->value();

    ui->frameDesenho->adicionarForma(forma, x1, y1, x2, y2, x3, y3, raio, corSelecionada, indiceSelecionado);

    atualizarCBDisplayFile();
    resetarSelecao();
    ui->frameDesenho->update();
}

void MainWindow::on_btnCor_clicked() {
    QColor novaCor = QColorDialog::getColor(Qt::black, this, "Escolher Cor");

    if (novaCor.isValid()) {
        corSelecionada = novaCor;
        qDebug() << "Cor selecionada:" << corSelecionada.name();
    }
}

void MainWindow::atualizarCamposForma(const QString& formaSelecionada) {
    ui->btnExcluirForma->hide();
    ui->lblRaio->hide();
    ui->spinRaio->hide();

    static const QList<QWidget*> campos2 = { ui->spinX2, ui->spinY2, ui->lblCoordenadaX2, ui->lblCoordenadaY2 };
    static const QList<QWidget*> campos3 = { ui->spinX3, ui->spinY3, ui->lblCoordenadaX3, ui->lblCoordenadaY3 };

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
    } else if (auto quadrado = dynamic_cast<const Quadrado*>(forma.get())) {
        ui->comboFormas->setCurrentText("Quadrado");
        ui->spinX1->setValue(quadrado->getP1().getX());
        ui->spinY1->setValue(quadrado->getP1().getY());
        ui->spinX2->setValue(quadrado->getP2().getX());
        ui->spinY2->setValue(quadrado->getP2().getY());
    } else if (auto triangulo = dynamic_cast<const Triangulo*>(forma.get())) {
        ui->comboFormas->setCurrentText("Triangulo");
        ui->spinX1->setValue(triangulo->getP1().getX());
        ui->spinY1->setValue(triangulo->getP1().getY());
        ui->spinX2->setValue(triangulo->getP2().getX());
        ui->spinY2->setValue(triangulo->getP2().getY());
        ui->spinX3->setValue(triangulo->getP3().getX());
        ui->spinY3->setValue(triangulo->getP3().getY());
    } else if (auto circunferencia = dynamic_cast<const Circunferencia*>(forma.get())) {
        ui->comboFormas->setCurrentText("Circunferencia");
        ui->spinX1->setValue(circunferencia->getP1().getX());
        ui->spinY1->setValue(circunferencia->getP1().getY());
        ui->spinRaio->setValue(circunferencia->getRaio());
    }

    corSelecionada = forma->getCor();
    ui->btnExcluirForma->show();
}

void MainWindow::resetarSelecao() {
    indiceSelecionado = -1;
    ui->cbDisplayFile->setCurrentIndex(-1);
    ui->btnDesenhar->setText("Adicionar");
    ui->btnExcluirForma->hide();
}

void MainWindow::on_btnExcluirForma_clicked() {
    if (indiceSelecionado != -1) {
        auto resposta = QMessageBox::question(this, "Confirmar exclusão",
                                              "Deseja realmente excluir a forma selecionada?",
                                              QMessageBox::Yes | QMessageBox::No);
        if (resposta == QMessageBox::Yes) {
            repositorio.remover(indiceSelecionado);
            atualizarCBDisplayFile();
            resetarSelecao();
            ui->frameDesenho->update();
        }
    }
}

void MainWindow::on_btnTransformar_clicked() {
    if (indiceSelecionado == -1) {
        QMessageBox::warning(this, "Aviso", "Nenhum objeto selecionado.");
        return;
    }

    if (!ui->checkBoxEscala->isChecked() &&
        !ui->checkBoxRotacao->isChecked() &&
        !ui->checkBoxTranslacao->isChecked()) {
        QMessageBox::warning(this, "Aviso", "Nenhuma transformação selecionada.");
        return;
    }

    Matriz transformacao = Matriz::identidade(3);

    if (ui->checkBoxEscala->isChecked()) {
        double ex = ui->spinEscalaX->value();
        double ey = ui->spinEscalaY->value();
        if (ex == 0 || ey == 0) {
            QMessageBox::warning(this, "Erro", "Por favor, não insira 0 para a escala.");
            return;
        }
        Matriz escala = Matriz::escala2D(ex, ey);
        transformacao = escala * transformacao;
    }

    if (ui->checkBoxRotacao->isChecked()) {
        double ang = ui->spinRotacao->value();
        if (ang == 0) {
            QMessageBox::warning(this, "Erro", "Por favor, insira algum valor na rotação.");
            return;
        }
        Matriz rotacao = Matriz::rotacao2D(ang);
        transformacao = rotacao * transformacao;
    }

    if (ui->checkBoxTranslacao->isChecked()) {
        double tx = ui->spinTranslacaoX->value();
        double ty = ui->spinTranslacaoY->value();
        if (tx == 0 && ty == 0) {
            QMessageBox::warning(this, "Erro", "Por favor, insira valores para a translação.");
            return;
        }
        Matriz translacao = Matriz::translacao2D(tx, ty);
        transformacao = translacao * transformacao;
    }

    realizarTransformacao(transformacao);
    atualizarCBDisplayFile();

    if(indiceSelecionado == 0){
        auto& vetor = repositorio.obterTodos().at(0);
        auto* quadrado = dynamic_cast<Quadrado*>(vetor.get());

        /*double minX = std::min({quadrado->getP1().getX(),
                                quadrado->getP2().getX(),
                                quadrado->getP3().getX(),
                                quadrado->getP4().getX()});

        double maxX = std::max({quadrado->getP1().getX(),
                    quadrado->getP2().getX(),
                    quadrado->getP3().getX(),
                    quadrado->getP4().getX()});

        double minY = std::min({quadrado->getP1().getY(),
                                quadrado->getP2().getY(),
                                quadrado->getP3().getY(),
                                quadrado->getP4().getY()});

        double maxY = std::max({quadrado->getP1().getY(),
                                quadrado->getP2().getY(),
                                quadrado->getP3().getY(),
                                quadrado->getP4().getY()});*/

        ui->frameDesenho->setWindowSCN(quadrado->getP1().getX(),
                                       quadrado->getP2().getY(),
                                       quadrado->getP2().getX(),
                                       quadrado->getP1().getY());
    }

    ui->frameDesenho->update();
    resetarSelecao();
}

void MainWindow::atualizarComboBox() {
    atualizarCBDisplayFile();
}

void MainWindow::realizarTransformacao(Matriz transformacao) {
    auto& forma = repositorio.obterTodos().at(indiceSelecionado);

    if (auto* ponto = dynamic_cast<Ponto*>(forma.get())) {
        ponto->aplicarTransformacao(transformacao, *ponto);
        ponto->marcarTransformadoModelo();
        ponto->resetarTransformadoViewport();
    } else if (auto* reta = dynamic_cast<Reta*>(forma.get())) {
        reta->aplicarTransformacao(transformacao);
        reta->marcarTransformadoModelo();
        reta->resetarTransformadoViewport();
    } else if (auto* quadrado = dynamic_cast<Quadrado*>(forma.get())) {
        quadrado->aplicarTransformacao(transformacao);
        quadrado->marcarTransformadoModelo();
        quadrado->resetarTransformadoViewport();
    } else if (auto* triangulo = dynamic_cast<Triangulo*>(forma.get())) {
        triangulo->aplicarTransformacao(transformacao);
        triangulo->marcarTransformadoModelo();
        triangulo->resetarTransformadoViewport();
    } else if (auto* circunferencia = dynamic_cast<Circunferencia*>(forma.get())) {
        circunferencia->aplicarTransformacao(transformacao);
        circunferencia->marcarTransformadoModelo();
        circunferencia->resetarTransformadoViewport();
    }
}
