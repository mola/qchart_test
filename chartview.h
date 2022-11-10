#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <iostream>
#include <lineitem.h>
#include <QChartView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include <QtCharts>

enum Mode
{
   InsertRec,
   InsertCirle,
   InsertText,
   InsertLine,
   InsertThresholdVer,
   InsertThresholdHri,
   None
};
class ChartView : public QtCharts::QChartView
{
public:
   ChartView(QtCharts::QChart *chart, QWidget *parent = 0);

   void deletItem();


   // QWidget interface
   void insertLineVer(QMouseEvent *mouseEvent);
   void insertLineHri(QMouseEvent *mouseEvent);
   void setMode(Mode m);

protected:
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);

   // void paintEvent(QPaintEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

private:
   Mode          mode = None;
   QPoint        m_mousPos;
   bool          mousePressed;
   QPainter      *painter;
   QGraphicsItem *itemToDraw;
   QLine         mLine;
   LineItem      *line;
   QRect         mRect;
   QPixmap       m_nPTargetPixmap;


   // QWidget interface

   // QGraphicsView interface
};

#endif // CHARTVIEW_H
