#include "chartview.h"


#include <QGraphicsItem>
ChartView::ChartView(QtCharts::QChart *chart, QWidget *parent)
   : QtCharts::QChartView(chart, parent)
{
   this->setMouseTracking(true);
   mousePressed = false;


   m_nPTargetPixmap = QPixmap(20, 20);
}


void ChartView::deletItem()
{
   auto selectedItems = scene()->selectedItems();

   // auto itemes        = scene()->items();

   //QDebug(selectedItems.size());
   qDebug() << selectedItems.size();
   //qDebug() << itemes.size();

   for (QGraphicsItem *item : qAsConst(selectedItems))
   {
      scene()->removeItem(item);
      delete item;
   }
}


void ChartView::insertLineVer(QMouseEvent *mouseEvent)
{
   auto s        = this->scene();
   auto posMouse = mouseEvent->pos().x();


   s->addItem(new LineItem(posMouse, 0, posMouse, 800));
}


void ChartView::insertLineHri(QMouseEvent *mouseEvent)
{
   auto s        = this->scene();
   auto posMouse = mouseEvent->pos().y();


   s->addItem(new LineItem(0, posMouse, 1000, posMouse));
}


void ChartView::setMode(Mode m)
{
   this->mode = m;
}


void ChartView::mousePressEvent(QMouseEvent *mouseEvent)
{
   auto s = this->scene();

   if (mouseEvent->button() != Qt::LeftButton)
   {
      deletItem();
      return;
   }
   QPen pen = QPen(Qt::green, 10);

   switch (mode)
   {
   case InsertThresholdVer:
      insertLineVer(mouseEvent);
      break;

   case InsertThresholdHri:
      insertLineHri(mouseEvent);
      break;

   case InsertLine:
      mLine.setP1(mouseEvent->pos());
      mLine.setP2(mouseEvent->pos());
      line = new LineItem(mLine);
      line->setPen(pen);
      s->addItem(line);

      break;


   default:
      break;
   }
   //Mouse is pressed for the first time
   mousePressed = true;

   //set the initial line points, both are same
//   if (selectedTool == 1)
//   {
//      mRect.setTopLeft(mouseEvent->pos());
//      mRect.setBottomRight(mouseEvent->pos());
//   }


//QGraphicsScene::mousePressEvent(mouseEvent);
} // ChartView::mousePressEvent


void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
   //When mouse is released update for the one last time

   mousePressed = false;
   update();
}


void ChartView::mouseMoveEvent(QMouseEvent *event)
{
   //As mouse is moving set the second point again and again
   // and update continuously
   if (!mousePressed)
   {
      return;
   }

   switch (mode)
   {
   case InsertLine:

      if (line != nullptr)
      {
         mLine.setP2(event->pos());
         line->setLine(mLine);
      }
      break;

   default:
      break;
   }
//      if (selectedTool == 1)
//      {
//         mRect.setBottomRight(event->pos());
//      }


   //it calls the paintEven() function continuously
   update();
}
