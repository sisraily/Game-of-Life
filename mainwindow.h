#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "bar.h"
#include "cell.h"
#include "qtimer.h"


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

    void CellSelectedLivesSlot(Cell *c);
    void CellSelectedDiesSlot(Cell *c);

    void CalcNextValues();
    int CalcLivePop();
    void AddBar(int pop);

    void on_colorButton1_clicked();

    void on_colorButton2_clicked();

    void on_colorButton3_clicked();

signals:
    void CellColorChange(int color);
    void CellAlphaChange(float alpha);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *cellsScene;
    QGraphicsScene *graphScene;


    // Cells view will have a height of 20 cells and 10 rows of cells (200 total).
    // y coordinates
    static const int y_cells_ = 20;
    // x coordinates
    static const int x_cells_ = 40;
    static const int max_num_bars_ = 37;

    Cell * cells_[x_cells_][y_cells_];
    Bar * bars_[max_num_bars_];

    int neighborsX_[8] = {1,-1,0,0,1,1,-1,-1};
    int neighborsY_[8] = {0,0,1,-1,1,-1,1,-1};

    // Keeps track of how many turns we've had in a given simulation.
    int turn_count_ = 0;

    // Used to calculate percentage of population alive in a given turn
    int total_pop_ = y_cells_ * x_cells_;

    // keeps track number of bars in the bar graph area.
    int num_bars_ = 0;

    QTimer *timer = new QTimer(this);

    QColor cell_live_colors_ = QColor(217,130,181);
};
#endif // MAINWINDOW_H
