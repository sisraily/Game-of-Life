#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QTime>
#include "cell.h"
#include "bar.h"
#include <QString>


// Setting up bar.

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
    cellsScene = new QGraphicsScene;
    cellsView->setScene(cellsScene);

    // populate grid of cells.
    // store this in a datastructure?
    // cell number.
    int count_x = 0;
    int count_y = 0;

    for (int j = 0; j<150; j = j+15){
        for (int i = 0; i<300; i = i+15){
            if (count_x == 20){
                count_x = 0;
            }
            else {
                count_x += 1;
            }
            Cell * c = new Cell(i, j);
            this->cells_[count_x][count_y] = c;
            cellsScene->addItem(c);
        }
        count_y+=1;
        qDebug() << count_x;
    }

    /*** Causing program not to work at certain times ***/
    int alive_tracker = 0;
    for (int i = 0; i < row_cells_; i++){
        for (int j = 0; j < col_cells_; j++){
            if(this->cells_[i][j]->is_alive()){
                alive_tracker +=1;
                //qDebug() << "X: " << cells_[i][j]->get_x() << ", Y: " << cells_[i][j]->get_y();
            }
        }
    }

    // set pct alive label
    std::string s = "Population: " + std::to_string(alive_tracker);
    QString qs(s.c_str());
    ui->populationLabel->setText(qs);
    qDebug() << "alive tracker: " << alive_tracker;
    /*** end crash casue ***/

    // Populate grid
    QGraphicsView * graphView = ui->stepGraph;
    graphScene = new QGraphicsScene;
    // sets the coordinate system so bottom left hand corner is (0,0)
    graphScene->setSceneRect(0,0,600,101);

    graphView->setScene(graphScene);

    // bar testing.
    Bar *b = new Bar(0,0,20);
    graphScene->addItem(b);
    //Cell * c2 = new Cell(15, 0);
    // add it to the scene
    //scene->addItem(c);
    //scene->addItem(c2);

    /**************** Next values calculated here *******************/
    for (int i = 0; i < row_cells_; i++){
        for (int j = 0; j < col_cells_; j++){
            int x_coord = cells_[i][j]->get_x()/15;
            int y_coord = cells_[i][j]->get_y()/15;
            int neighbor_live_count = 0;
            for(int i=0;i<8;i++)
            {
              // We only need to know max if three neihbors are alive.
              if (neighbor_live_count > 3){
                  break;
              }

              int neighbor_x = x_coord + neighborsX_[i];
              qDebug() << "x coord " << x_coord;
              // edge cases here, if below zero or more than last col
              if (neighbor_x < 0){
                  neighbor_x = col_cells_ -1;
              } else if (neighbor_x == col_cells_){
                  neighbor_x = 0;
              }

              int neighbor_y=y_coord+neighborsY_[i];
              // edge cases here, if below zero or more than last row
              if (neighbor_y < 0){
                  neighbor_y = row_cells_ -1;
              } else if (neighbor_y == row_cells_){
                  neighbor_y = 0;
              }
              qDebug() << "X: " << neighbor_x << ", Y: " << neighbor_y;

//              if (cells_[neighbor_x][neighbor_y]->is_alive()){
//                  neighbor_live_count+=1;
//              }
//                  if(nx<n && nx>=0 && ny>=0 && ny<m)
//                  {
//                      do what you want to do
//                  }

            }
        }
    }

    /**************** END -- Next values calculated here *******************/


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

