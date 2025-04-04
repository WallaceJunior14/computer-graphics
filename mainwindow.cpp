#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawArea = new DrawWidget(ui->drawFrame);  // drawFrame é o QFrame do .ui
    drawArea->setGeometry(ui->drawFrame->rect());  // Ocupa o espaço do frame
    drawArea->show();

    connect(ui->btnDesenhar, &QPushButton::clicked, this, [=]() {
        drawArea->mostrarFormas(ui->checkFormas->isChecked());
        drawArea->mostrarPontosRetas(ui->checkPontosRetas->isChecked());
    });

    connect(ui->btnCor, &QPushButton::clicked, this, [=]() {
        QColor novaCor = QColorDialog::getColor(Qt::red, this, "Escolher cor");
        if (novaCor.isValid()) {
            drawArea->setCor(novaCor);
        }
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
