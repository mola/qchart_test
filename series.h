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


class Series : public QObject
{
   Q_OBJECT

public:
   Series(QObject *parent = nullptr);

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

   int getId();

private:
   static int            m_id;
   QList<QPointF>        Datas;
   QtCharts::QLineSeries *series;
   int                   Thickness = 1;
   QColor                Color     = Qt::black;
};

// Q_DECLARE_METATYPE(Series)

#endif // SERIES_H
