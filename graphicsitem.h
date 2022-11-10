#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QLine>

class GraphicsItem: public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    GraphicsItem();

    // QGraphicsItem interface

public:
    QRectF  boundingRect() const;

    void    paintLine(QPainter *painter, QLine line);

signals:
    void    selected();

    void    contextMenu();

private:
    bool  mSelected = false;

    // QGraphicsItem interface

public:
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void  contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void  mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void  mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface

public:
    QPainterPath  shape() const;
};

#endif // GRAPHICSITEM_H
