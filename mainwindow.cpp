#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QTime>
#include "cell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Seed for random number generation. Used for choosing wether cells are alive or dead.
    srand(static_cast<unsigned>(QTime::currentTime().msec()));

    // Sets the properties for the speed slider.
    // emits value changed signal when the user is holding down the slider. Used for updating the speed label, as the speed bar
    // is moved.
    ui->speedSlider->setTracking(true);

    // slider range from slow to fast.
    ui->speedSlider->setRange(0,100);

    // slider incrementation step value
    ui->speedSlider->setSingleStep(1);

    // sets default slider value
    ui->speedSlider->setValue(25);


    // QGraphicsView settings
    QGraphicsView * cellsView = ui->cellsView;
    scene = new QGraphicsScene;
    cellsView->setScene(scene);

    // populate grid of cells.
    for (int i = 0; i<300; i = i+15){
        for (int j = 0; j<150; j = j+15){
            Cell * c = new Cell(i, j);
            scene->addItem(c);
        }
    }


    //Cell * c2 = new Cell(15, 0);
    // add it to the scene
    //scene->addItem(c);
    //scene->addItem(c2);

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


void MainWindow::on_speedSlider_sliderMoved(int position)
{
    std::string s = "Speed: " + std::to_string(position);
    QString qs(s.c_str());
    ui->speedLabel->setText(qs);
}

