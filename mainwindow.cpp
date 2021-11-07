#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    qDebug() << "play button clicked default slot!";
}

void MainWindow::on_pauseButton_clicked()
{
    qDebug() << "pause button clicked default slot!";
}

void MainWindow::on_stepButton_clicked()
{
    qDebug() << "step button clicked default slot!";
}
