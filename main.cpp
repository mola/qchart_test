#include "mainwindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>


QT_CHARTS_USE_NAMESPACE
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow   w;

   //Data         myData;

   w.show();
   return(a.exec());
} // main
