#include "mainwindow.h"
#include "ui_mainwindow.h"


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


   // series                             = //defualt
   this->chart = new QtCharts::QChart();
   axisX       = new QtCharts::QCategoryAxis();
   axisY       = new QtCharts::QCategoryAxis();
   this->timer = new QTimer(this);

   QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateChart()));
}


void MainWindow::tableViewSeriesConfigure()
{
   TableSeries     = new TableModelSeries;
   SpinBoxDelegate = new SpinBoxThick(this);

   ui->SeriesTable->setModel(TableSeries);
   ui->SeriesTable->setSortingEnabled(false);

   ui->SeriesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
   ui->SeriesTable->resizeColumnsToContents();
   ui->SeriesTable->setItemDelegateForColumn(2, SpinBoxDelegate);
   TableSeries->TableModelSeries::insertRow("Item", currentSeries->getColor());
   //ui->SeriesTable->horizontalHeader()->setSectionHidden(QHeaderView::ResizeToContents);
}


void MainWindow::updateChartSeries(bool updateData)
{
   axisX->setRange(this->rngXstartPoint, this->rngXstopPoint);
   axisY->setRange(this->rngYstartPoint, this->rngYstopPoint);

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
   //updateChartSeries();
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

   chartView = new QtCharts::QChartView(chart);
   chart->addAxis(axisX, Qt::AlignBottom);
   chart->addAxis(axisY, Qt::AlignLeft);

   SeriesList[0]->getSeries()->attachAxis(axisX);
   SeriesList[0]->getSeries()->attachAxis(axisY);

   chartView->setRenderHint(QPainter::Antialiasing);
//![4]


//![5]
   layout = new QVBoxLayout;
   //QVBoxLayout* toolBarLayout=new QVBoxLayout;
   layout->setMenuBar(this->toolBar);
   ui->widget->setLayout(layout);

   ui->widget->layout()->addWidget(chartView);
}


void MainWindow::updateChart()
{
   updateChartSeries(true);
}


void MainWindow::on_ExitButton_clicked()
{
   exit(0);
}


void MainWindow::on_thickness_valueChanged(int arg1)
{
   currentSeries->updateThickness(arg1);
   updateChartSeries(false);
}


void MainWindow::updateColor()
{
   QColor col = this->colorPalette->currentColor();

   currentSeries->updateColor(col);

   if (col.isValid())
   {
      QString qss = QString("background-color: %1").arg(col.name());
      ui->colorChanged->setStyleSheet(qss);
   }
   updateChartSeries(false);
}


void MainWindow::on_checkBox_toggled(bool checked)
{
   if (checked)
   {
      std::cout << this->timeOut << "HH" << std::endl;
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
   this->rngYstartPoint = arg1;
}


void MainWindow::on_rngYstopPoint_valueChanged(int arg1)
{
   this->rngYstopPoint = arg1;
}


void MainWindow::on_colorChanged_clicked()
{
   colorPalette->open();

   target = qobject_cast<QPushButton *>(sender());

   QObject::connect(colorPalette, &QColorDialog::colorSelected, this, &MainWindow::updateColor);
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
   currentSeries->getSeries()->attachAxis(axisY);
   int     num  = SeriesList.size();
   QString Item = "Series " + QVariant(num).toString();

   ui->selectSeries->addItem(Item);
   TableSeries->TableModelSeries::insertRow(Item, currentSeries->getColor());
   ui->SeriesTable->resizeRowsToContents();
}


void MainWindow::on_selectSeries_currentTextChanged(const QString &arg1)
{
   QStringList list = arg1.split(' ');
   int         num  = list[list.size() - 1].toInt();

   currentSeries = SeriesList[num - 1];
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

   this->rngYstartPoint = Min;
   this->rngYstopPoint  = Max;
   updateChartSeries(false);
}
