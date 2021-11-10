#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "bar.h"
#include "cell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stepButton_clicked();
    void on_speedSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *cellsScene;
    QGraphicsScene *graphScene;


    // Cells view will have a height of 20 cells and 10 rows of cells (200 total).
    static const int row_cells_ = 10;
    static const int col_cells_ = 20;

    Bar * bars_[row_cells_][col_cells_];

    Cell * cells_[row_cells_][col_cells_];

    int neighborsX_[8] = {1,-1,0,0,1,1,-1,-1};
    int neighborsY_[8] = {0,0,1,-1,1,-1,1,-1};
};
#endif // MAINWINDOW_H
