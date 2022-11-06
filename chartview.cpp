#include "chartview.h"

ChartView::ChartView(QtCharts::QChart *chart)
   : QtCharts::QChartView(chart)
{
}


void ChartView::insertLineVer(QMouseEvent *mouseEvent)
{
   auto s        = this->scene();
   auto posMouse = mouseEvent->pos().x();

   s->addLine(posMouse, 0, posMouse, 800);
}


void ChartView::insertLineHri(QMouseEvent *mouseEvent)
{
   auto s        = this->scene();
   auto posMouse = mouseEvent->pos().y();

   s->addLine(0, posMouse, 1000, posMouse);
}


void ChartView::setMode(Mode m)
{
   this->mode = m;
}


void ChartView::mousePressEvent(QMouseEvent *mouseEvent)
{
   if (mouseEvent->button() != Qt::LeftButton)
   {
      return;
   }

   switch (mode)
   {
   case InsertThresholdVer:
      insertLineVer(mouseEvent);
      break;

   case InsertThresholdHri:
      insertLineHri(mouseEvent);

   default:
      break;
   }
   //QGraphicsScene::mousePressEvent(mouseEvent);
}
