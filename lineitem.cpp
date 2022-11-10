#include "lineitem.h"
#include "qdebug.h"

#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPen>
#include <QGraphicsScene>
#include <iostream>

LineItem::LineItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent):
    QGraphicsLineItem(x1, y1, x2, y2, parent)
{
// setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

LineItem::LineItem(const QLineF &line, QGraphicsItem *parent):
    QGraphicsLineItem(line, parent)
{
}

LineItem::~LineItem()
{
}

void  LineItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    setSelected(true);

    auto     menu = QMenu();
    QAction *act  = menu.addAction("Delete");

    QObject::connect(act, &QAction::triggered, [this]()
    {
        scene()->removeItem(this);
    });
    menu.exec(event->screenPos());
}

void  LineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mB = !mB;
        setSelected(mB);

        if (mB)
        {
            setPen(QPen(Qt::blue, 6));
        }
        else
        {
            setPen(QPen(Qt::green, 4));
        }
    }

    qDebug() << boundingRect();
}
