#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsSceneMouseEvent>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   configure();

   createChartSeries();
   colorPalette = new QColorDialog();
}

MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::configure()
{
   SeriesList.push_back(new Series());
   currentSeries = SeriesList[0];
   tableViewSeriesConfigure();
   deleteAction = new QAction(tr("&Delete"), this);
   deleteAction->setShortcut(QKeySequence::Delete);
   deleteAction->setStatusTip(tr("Delete item from diagram"));
   // series                             = //defualt
   this->chart = new QtCharts::QChart();
   axisX       = new QtCharts::QValueAxis();
   axisYLeft   = new QtCharts::QValueAxis();
   axisYRight  = new QtCharts::QValueAxis();
   this->timer = new QTimer(this);

   QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateChart()));
}


void MainWindow::createStandardItem(QString Name)
{
   auto item0 = new QStandardItem(Name);
   auto item1 = new QStandardItem();
   auto item2 = new QStandardItem();

   item0->setToolTip(Name);

   //auto                   item1 = new QStandardItem("color");
   QList<QStandardItem *> items;
   QVariant               variant;
   QColor                 color = variant.value<QColor>();

   item1->setData(color, Qt::BackgroundColorRole);
   item2->setData(QVariant::fromValue(2), Qt::DisplayRole);
   item0->setData(QVariant::fromValue(currentSeries), 1000);
   items << item0 << item1 << item2;
   TableSeries->insertRow(currentSeries->getId(), items);
}


void MainWindow::itemChangedSeries(QStandardItem *item)
{
   if (item->column() == 2)
   {
      auto item0 = TableSeries->item(item->row(), 0);
      // auto          item_1      = TableSeries->takeItem(item->row(), 0);
      auto s     = item0->data(1000).value<Series *>();
      auto thick = item->data(Qt::DisplayRole).value<int>();
      s->updateThickness(thick);
      s->updateSeriesLine(false);
   }

   if (item->column() == 1)
   {
      auto item0 = TableSeries->item(item->row(), 0);
      auto s     = item0->data(1000).value<Series *>();
      auto color = item->data(Qt::BackgroundColorRole).value<QColor>();
      s->updateColor(color);
      s->updateSeriesLine(false);
   }
}


void MainWindow::tableViewSeriesConfigure()
{
// TableSeries = new TableModelSeries();
   TableSeries      = new QStandardItemModel;
   SpinBoxDelegate  = new SpinBoxThick(this);
   colorDelegateBox = new colorDelegate(this);
   connect(TableSeries, &QStandardItemModel::itemChanged, this, &MainWindow::itemChangedSeries);
   TableSeries->setHorizontalHeaderLabels({ "Name", "Color", "Thikness" });
   ui->SeriesTable->setModel(TableSeries);
   ui->SeriesTable->setSortingEnabled(false);
   ui->SeriesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
   ui->SeriesTable->resizeColumnsToContents();
   ui->SeriesTable->setItemDelegateForColumn(1, colorDelegateBox);
   ui->SeriesTable->setItemDelegateForColumn(2, SpinBoxDelegate);
   createStandardItem("Series 1");
}


void MainWindow::updateChartSeries(bool updateData)
{
   axisX->setRange(this->rngXstartPoint, this->rngXstopPoint);
   axisYLeft->setRange(this->rngYstartPointLeft, this->rngYstopPointLeft);
   axisYRight->setRange(this->rngYstartPointRight, this->rngYstopPointRight);

   for (int i = 0; i < SeriesList.size(); i++)
   {
      SeriesList[i]->updateSeriesLine(updateData);
   }

   if (ui->checkBox->isChecked())
   {
      this->timer->start(this->timeOut);
   }
}


void MainWindow::timeRefresh()
{
   TimerState++;
   TimerState = TimerState % 3;

   if (this->TimerState == 0)
   {
      TimerAction->setText("1");
      timeOut = 100;
   }
   else if (this->TimerState == 1)
   {
      TimerAction->setText("5");
      timeOut = 500;
   }
   else if (this->TimerState == 2)
   {
      TimerAction->setText("10");
      timeOut = 1000;
   }
   // updateChartSeries();
}


void MainWindow::addToolBar()
{
   this->toolBar = new QToolBar();
   toolBar->setContentsMargins(0, 0, 0, 0);
   toolBar->setOrientation(Qt::Horizontal);

   TimerAction = new QAction(toolBar);
   TimerAction->setText("1");

   QObject::connect(TimerAction, &QAction::triggered, this, &MainWindow::timeRefresh);
   this->toolBar->addAction(TimerAction);
}


void MainWindow::createChartSeries()
{
   chart->legend()->hide();

   for (int i = 0; i < SeriesList.size(); i++)
   {
      SeriesList[i]->createSeriesLine();
      chart->addSeries(SeriesList[i]->getSeries());
   }

   chart->createDefaultAxes();
   addToolBar();

   // chartView = new QtCharts::QChartView(chart);
   chartView = new ChartView(chart, this);
   connect(deleteAction, &QAction::triggered, chartView, &ChartView::deletItem);

   chart->setAxisX(axisX);
   chart->setAxisY(axisYLeft);
   chart->addAxis(axisYRight, Qt::AlignRight);


   auto s = chartView->scene();


   QGraphicsSceneMouseEvent mouse;


   SeriesList[0]->getSeries()->attachAxis(axisX);
   SeriesList[0]->getSeries()->attachAxis(axisYLeft);

   chartView->setRenderHint(QPainter::Antialiasing);
//! [4]

//! [5]
   layout = new QVBoxLayout;
   // QVBoxLayout* toolBarLayout=new QVBoxLayout;
   layout->setMenuBar(this->toolBar);
   ui->widget->setLayout(layout);

   ui->widget->layout()->addWidget(chartView);
} // MainWindow::createChartSeries


void MainWindow::updateChart()
{
   updateChartSeries(true);
}


void MainWindow::on_ExitButton_clicked()
{
   exit(0);
}


void MainWindow::on_checkBox_toggled(bool checked)
{
   if (checked)
   {
      // std::cout << this->timeOut << "HH" << std::endl;
      this->timer->start(this->timeOut);
   }
   else
   {
      this->timer->stop();
   }
}


void MainWindow::on_rngXstartPoint_valueChanged(int arg1)
{
   this->rngXstartPoint = arg1;
}


void MainWindow::on_rangeXstopPoint_valueChanged(int arg1)
{
   this->rngXstopPoint = arg1;
}


void MainWindow::on_rngYstartPoint_valueChanged(int arg1)
{
   this->rngYstartPointLeft = arg1;
}


void MainWindow::on_rngYstopPoint_valueChanged(int arg1)
{
   this->rngYstopPointLeft = arg1;
}


void MainWindow::on_updateButton_clicked()
{
   updateChartSeries(false);
}


void MainWindow::on_AddSeries_clicked()
{
   SeriesList.push_back(new Series());
   currentSeries = SeriesList[SeriesList.size() - 1];
   currentSeries->createSeriesLine();
   chart->addSeries(currentSeries->getSeries());
   currentSeries->getSeries()->attachAxis(axisX);

   if (currentSeries->getId() % 2)
   {
      currentSeries->getSeries()->attachAxis(axisYLeft);
   }
   else
   {
      // axisYRight->setRange(0, 100);
      axisYRight->setLinePenColor(Qt::blue);
      //axisYRight->setGridLinePen((currentSeries->getSeries()->pen()));
      currentSeries->getSeries()->attachAxis(axisYRight);
   }
   int     num  = SeriesList.size();
   QString Item = "Series " + QVariant(num).toString();


   createStandardItem(Item);
// TableSeries->TableModelSeries::insertRow(Item, currentSeries->getColor());
   ui->SeriesTable->resizeRowsToContents();
}


void MainWindow::on_UpdateDataChanged_clicked()
{
   updateChartSeries(true);
}


void MainWindow::on_AutoScale_clicked()
{
   int Min = MAX_INPUT;
   int Max = -1;

   for (int i = 0; i < SeriesList.size(); i++)
   {
      int tempMin = SeriesList[i]->findMin();
      int tempMax = SeriesList[i]->findMax();
      Min = std::min(Min, tempMin);
      Max = std::max(Max, tempMax);
   }

   this->rngYstartPointLeft = Min;
   this->rngYstopPointRight = Max;
   updateChartSeries(false);
}


void MainWindow::on_rngXstartPointRight_valueChanged(int arg1)
{
   this->rngYstartPointRight = arg1;
}


void MainWindow::on_rngXstopPointRight_valueChanged(int arg1)
{
   this->rngYstopPointRight = arg1;
}


void MainWindow::on_VerticalThreshold_triggered(bool checked)
{
   if (checked)
   {
      chartView->setMode(InsertThresholdVer);
   }
   else
   {
      chartView->setMode(None);
   }
}


void MainWindow::on_HorizontalThreshold_triggered(bool checked)
{
   if (checked)
   {
      chartView->setMode(InsertThresholdHri);
   }
   else
   {
      chartView->setMode(None);
   }
}


void MainWindow::on_actionLine_triggered(bool checked)
{
   if (checked)
   {
      chartView->setMode(InsertLine);
   }
   else
   {
      chartView->setMode(None);
   }
}
