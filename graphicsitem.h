#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QLine>

class GraphicsItem : public QGraphicsItem
{
public:
   GraphicsItem();

   // QGraphicsItem interface
public:
   QRectF boundingRect() const;
   void paintLine(QPainter *painter, QLine line);

private:
};

#endif // GRAPHICSITEM_H
