#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QGraphicsScene>
#include <QObject>
#include <QtCharts>
enum Mode
{
   InsertRec,
   InsertCirle,
   InsertText,
   InsertThresholdVer,
   InsertThresholdHri,
   None
};
class ChartView : public QtCharts::QChartView
{
   Q_OBJECT
public:
   ChartView(QtCharts::QChart *chart);


   // QWidget interface
   void insertLineVer(QMouseEvent *mouseEvent);
   void insertLineHri(QMouseEvent *mouseEvent);
   void setMode(Mode m);

protected:
   void mousePressEvent(QMouseEvent *event);

//   void mouseReleaseEvent(QMouseEvent *event);
//   void mouseMoveEvent(QMouseEvent *event);
private:
   Mode mode = None;
};

#endif // CHARTVIEW_H
