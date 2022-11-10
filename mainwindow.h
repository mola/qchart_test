#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <chartview.h>
#include <colordelegate.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <QBoxLayout>
#include <QCategoryAxis>
#include <QColorDialog>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTableView>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <series.h>
#include <spinboxthick.h>


namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void  configure();

    void  tableViewSeriesConfigure();

    void  createChartSeries();

    void  updateChartSeries(bool updateData);

    void  addToolBar();

    void  createStandardItem(QString Name);

private slots:
    void  itemChangedSeries(QStandardItem *item);

    void  updateChart();

    void  on_ExitButton_clicked();

    void  on_checkBox_toggled(bool checked);

    void  on_rngXstartPoint_valueChanged(int arg1);

    void  on_rangeXstopPoint_valueChanged(int arg1);

    void  on_rngYstartPoint_valueChanged(int arg1);

    void  on_rngYstopPoint_valueChanged(int arg1);

    void  timeRefresh();

    void  on_updateButton_clicked();

    void  on_AddSeries_clicked();

    void  on_UpdateDataChanged_clicked();

    void  on_AutoScale_clicked();

    void  on_rngXstartPointRight_valueChanged(int arg1);

    void  on_rngXstopPointRight_valueChanged(int arg1);

    void  on_VerticalThreshold_triggered(bool checked);

    void  on_HorizontalThreshold_triggered(bool checked);

    void  on_actionLine_triggered(bool checked);

    void  on_actionaddNode_triggered();

private:
    Ui::MainWindow *ui;
    QAction        *deleteAction;
// TableModelSeries *TableSeries;
    QStandardItemModel    *TableSeries = nullptr;
    QVBoxLayout           *layout;
    ChartView             *chartView;
    QtCharts::QLineSeries *series;
    Series                *currentSeries;
    QList<Series *>        SeriesList;
    QtCharts::QChart      *chart;
    QtCharts::QValueAxis  *axisX;
    QtCharts::QValueAxis  *axisYLeft;
    QtCharts::QValueAxis  *axisYRight;
    QPushButton           *target;
    QAction               *TimerAction;
    int                    TimerState = 0;
    QTimer                *timer;
    int                    timeOut             = 200;
    bool                   timerIsOn           = false;
    int                    rngXstartPoint      = 0;
    int                    rngXstopPoint       = 3600;
    int                    rngYstartPointLeft  = 0;
    int                    rngYstopPointLeft   = 100;
    int                    rngYstartPointRight = 0;
    int                    rngYstopPointRight  = 100;
    QToolBar              *toolBar;
    QColorDialog          *colorPalette;
    QTableView             SeriesTable;
    SpinBoxThick          *SpinBoxDelegate;
    colorDelegate         *colorDelegateBox;
};
#endif // MAINWINDOW_H
