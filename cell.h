#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QGraphicsItem>


// QGraphicsItem is used to add senes, and QObject for signals.
class Cell : public QObject, public QGraphicsItem {

    // this makes it so that we can emit signals
    Q_OBJECT

public:
    Cell(const int x, const int y);  // constructor

    int get_x() const { return (x_); }  // inline member function
    int get_y() const { return (y_); }  // inline member function
    bool is_alive() const { return is_alive_; } // inline member function
    void set_is_alive(bool result) { this->is_alive_ = result ; } // inline member function
    void set_color(QColor color) { this->color_ = color; } // inline member function. sets the color of a cell to the parameter.

    /*
     * Sets the next turn to either alive or dead.
     * @param status alive=true, dead=false.
     */
    void set_next_turn_status(bool status){this->next_turn_status_ = status;}

    bool get_next_turn_status() const { return next_turn_status_; } // inline member function.

    int get_total_alive() const {return total_alive_; } // inline member function.

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; }



signals:
    void CellSelectedDies(Cell *c);
    void CellSelectedLives(Cell *c);

protected:
    // Overridden so that we can modify the color and parameters of the cell, when clicked.
    // Protected so that we can use inheritance, if desired.
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;



public slots:
    void CellColorChangeSlot(int color);
    void CellAlphaChangeSlot(float alpha);

private:

  // coordinates of cell
  int x_;
  int y_;

  static int total_alive_;

  bool next_turn_status_;
  bool is_alive_;


  QColor color_;

  // Width and height are the same.
  static const int width_ = 15;


};  // Class cell



#endif // CELL_H
