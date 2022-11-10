#include "graphicsitem.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

GraphicsItem::GraphicsItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF  GraphicsItem::boundingRect() const
{
    qreal  adjust = 2;

    return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

void  GraphicsItem::paintLine(QPainter *painter, QLine line)
{
}

void  GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient  gradient(-3, -3, 10);

    if (option->state & QStyle::State_Sunken)
    {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
    }
    else
    {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }

    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

void  GraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    emit  contextMenu();
}

void  GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void  GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QPainterPath  GraphicsItem::shape() const
{
    QPainterPath  path;

    path.addEllipse(-10, -10, 20, 20);

    return path;
}
