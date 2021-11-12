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
#include <QTimer>


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

    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::on_stepButton_clicked));


    // QGraphicsView settings
    QGraphicsView * cellsView = ui->cellsView;
    cellsScene = new QGraphicsScene;
    cellsScene->setSceneRect(0,0,750,301);
    cellsView->setScene(cellsScene);

    // populate initial grid of cells.
   for (int i = 0; i<x_cells_; i++){
        for (int j = 0; j<y_cells_; j++){
            Cell * c = new Cell(i, j);
            this->cells_[i][j] = c;
            cellsScene->addItem(c);
            // connect custom signal to custom slot.
            connect(c, &Cell::CellSelectedDies, this, &MainWindow::CellSelectedDiesSlot);
            connect(c, &Cell::CellSelectedLives, this, &MainWindow::CellSelectedLivesSlot);
        }
    }


    int live_pop = CalcLivePop();

    // Populate grid
    QGraphicsView * graphView = ui->stepGraph;
    graphScene = new QGraphicsScene;
    // sets the coordinate system so bottom left hand corner is (0,0)
    graphScene->setSceneRect(0,0,740,101);

    graphView->setScene(graphScene);

    // bar testing.

    this->AddBar(live_pop);
    this->CalcNextValues();

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_playButton_clicked()
{
//    qDebug() << "play button clicked default slot!";
    timer->start(1000);
}


void MainWindow::on_pauseButton_clicked()
{
//    qDebug() << "pause button clicked default slot!";
    timer->stop();
}


void MainWindow::on_stepButton_clicked()
{
//    qDebug() << "step button clicked default slot!";
    /**************** Start turn ******************************************/
    for (int i = 0; i < x_cells_; i++){
        for (int j = 0; j < y_cells_; j++){

             cells_[i][j]->set_is_alive(cells_[i][j]->get_next_turn_status());
             if (cells_[i][j]->is_alive()){
                 int r = 217;
                 int g = 130;
                 int b = 181;
                 QColor c(r, g, b);
                 cells_[i][j]->set_color(c);
             }
             else{
                 int r = 255;
                 int g = 255;
                 int b = 255;
                 QColor c(r, g, b);
                 cells_[i][j]->set_color(c);
             }
             cells_[i][j]->update();
        }
    }

    /**************** end turn ********************************************/
    this->CalcNextValues();
    turn_count_ += 1;
    std::string s = "Turn: " + std::to_string(turn_count_);
    QString qs(s.c_str());
    ui->turnLabel->setText(qs);

    int live_pop = this->CalcLivePop();
    AddBar(live_pop);

}


void MainWindow::on_speedSlider_sliderMoved(int position)
{
    std::string s = "Speed: " + std::to_string(position);
    QString qs(s.c_str());
    ui->speedLabel->setText(qs);
}

void MainWindow::CellSelectedLivesSlot(Cell *c){
    c->set_is_alive(true);
    QColor color(217,130,181);
    c->set_color(color);

    CalcLivePop();
    CalcNextValues();
}


void MainWindow::CellSelectedDiesSlot(Cell *c){
    c->set_is_alive(false);
    QColor color(255,255,255);
    c->set_color(color);

    CalcLivePop();
    CalcNextValues();
}

void MainWindow::CalcNextValues(){
    /**************** Next values calculated here *******************/
    for (int i = 0; i < x_cells_; i++){
        for (int j = 0; j < y_cells_; j++){
            // edge cells
//            if (i == 0 || j == 0 || i == x_cells_-1 || j == y_cells_-1){
//                continue;
//            }
//            else {
                int x_coord = cells_[i][j]->get_x()/15;
                int y_coord = cells_[i][j]->get_y()/15;
                int neighbor_live_count = 0;
//                qDebug() << "Cell: " << x_coord << ", " << y_coord;
//                qDebug() << "Neighbors: ";
                for(int i=0;i<8;i++)
                {
                  // We only need to know max if three neihbors are alive.


                  int neighbor_x = x_coord + neighborsX_[i];
                  int neighbor_y = y_coord + neighborsY_[i];

                  // edge cases here, if below zero or more than last col
                  if (neighbor_x < 0){
                      neighbor_x = x_cells_ -1;
                  // if neighbors x value is the width, then we switch it to zero.
                  } else if (neighbor_x == x_cells_){
                      neighbor_x = 0;
                  }

                  // y coordinate edge cases. if below zero or more than last row
                  if (neighbor_y < 0){
                      neighbor_y = y_cells_ -1;
                  } else if (neighbor_y == y_cells_){
                      neighbor_y = 0;
                  }

//                  qDebug() << "X: " << neighbor_x << ", Y: " << neighbor_y;
//                  qDebug() << "Alive? " << cells_[neighbor_x][neighbor_y]->is_alive();
                  if (cells_[neighbor_x][neighbor_y]->is_alive()){
                      neighbor_live_count+=1;
                  }

                }
                // rule 4: overpoulation. Cell automatically dies when more than 3 neighbors are live.
                if (neighbor_live_count > 3){
                    cells_[i][j]->set_next_turn_status(false);
                }
                // Underpoulation. Cells with less than 2 neighbors dies.
                else if ((cells_[i][j]->is_alive()) && neighbor_live_count < 2){
                    cells_[i][j]->set_next_turn_status(false);
                }
                else if ((cells_[i][j]->is_alive()) && ((neighbor_live_count == 2 ) || (neighbor_live_count ==3 ))){
                    continue;
                }
                // Reproduction.
                else if (!(cells_[i][j]->is_alive()) && neighbor_live_count == 3){
                    cells_[i][j]->set_next_turn_status(true);
                }
//            }
        }
    }

    /**************** END -- Next values calculated here *******************/
}

int MainWindow::CalcLivePop(){
    int alive_tracker = 0;
    for (int i = 0; i<x_cells_; i++){
        for (int j = 0; j<y_cells_;j++){
            if(this->cells_[i][j]->is_alive()){
                alive_tracker +=1;
                //qDebug() << "X: " << cells_[i][j]->get_x() << ", Y: " << cells_[i][j]->get_y();
            }
        }
    }
    float pct_alive = float(alive_tracker)/total_pop_;

    // set pct alive label
    std::string s = "Population: " + std::to_string(alive_tracker) + " (" + std::to_string(pct_alive) + ")";
    QString qs(s.c_str());
    ui->populationLabel->setText(qs);
//    qDebug() << "alive tracker: " << alive_tracker/total_pop_;

    // Feature 2 cases here. adjust color of cell based on pct of live vs dead cells.


    return alive_tracker;
}

void MainWindow::AddBar(int pop){
    int bar_pct = int((float(pop)/float(total_pop_))*100);


    // Fill up our scene width with bars, until we'vew reached the max number of bars.
    if(num_bars_ < max_num_bars_){
        int bar_x_loc = int(num_bars_ * 20);
        Bar *b = new Bar(bar_x_loc,int(100-bar_pct),100);

        bars_[num_bars_] = b;
        graphScene->addItem(bars_[num_bars_]);
        graphScene->update();
        num_bars_ += 1;
    }
    // If we've reached the max capacity of bars, set the previous bar to the next bars' height and
    // and adjust the last bar to the new height.
    else {

        for (int i = 1; i < num_bars_; i++){
            bars_[i-1]->set_y(int(bars_[i]->get_y()));
        }
        bars_[num_bars_-1]->set_y(int(100-bar_pct));
        graphScene->update();



    }
}
