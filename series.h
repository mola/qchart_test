#ifndef SERIES_H
#define SERIES_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <QBoxLayout>
#include <QCategoryAxis>
#include <QColorDialog>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
class Series
{
public:
   Series();
   void generateAndAddData();
   void updateList();
   void initialList();
   void createSeriesLine();
   QtCharts::QLineSeries *getSeries();
   void updateSeriesLine(bool updateData);
   void updateColor(QColor col);
   void updateThickness(int thick);
   int findMin();
   int findMax();

   int getThickness() const;
   const QColor &getColor() const;

private:
   QList<QPointF>        Datas;
   QtCharts::QLineSeries *series;
   int                   Thickness = 1;
   QColor                Color     = Qt::black;
};

#endif // SERIES_H
