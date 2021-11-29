#ifndef BAR_H
#define BAR_H

#include <QColor>
#include <QGraphicsItem>


// QGraphicsItem is used to add senes, and QObject for signals.
class Bar : public QObject, public QGraphicsItem {

    // this makes it so that we can emit signals
    Q_OBJECT

public:
    Bar(const int x, const int y, const int height);  // constructor

    int get_x() const { return x_; }  // inline member function
    int get_y() const { return y_; }  // inline member function

    void set_x(int x){this->x_ = x;}
    void set_y(int y){this->y_ = y;}

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; }


private:

  // coordinates of cell
  int x_;
  int y_;

  QColor color_;

  // Width of bar always stays the same.
  static const int width_ = 20;
  int height_ = 0;

};  // Class Bar



#endif // BAR_H
