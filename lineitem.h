#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsLineItem>

class LineItem: public QGraphicsLineItem
{
public:
    LineItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = nullptr);

    LineItem(const QLineF &line, QGraphicsItem *parent = nullptr);

    ~LineItem();

    // QGraphicsItem interface

protected:
    void  contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void  mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool  mB = false;
};

#endif // LINEITEM_H
