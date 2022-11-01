#include "series.h"

int Series::m_id = 0;

Series::Series(QObject *parent)
   : QObject(parent)
{
   initialList();
   series = new QtCharts::QLineSeries();
   m_id   = m_id++;
}


int Series::getId()
{
   return(m_id);
}


void Series::updateList()
{
   for (int i = 0; i < this->Datas.size(); i++)
   {
      int second = (rand() % 100) + 1;
      Datas[i] = QPoint(i, second);
   }
}


void Series::generateAndAddData()
{
   for (int i = 0; i < 3600; i++)
   {
      int first  = i;
      int second = (rand() % 100) + 1;
      Datas[i] = QPoint(first, second);
      series->append(first, second);
   }
}


void Series::initialList()
{
   for (int i = 0; i < 3600; i++)
   {
      Datas.push_back(QPoint(i, 0));
   }
}


QtCharts::QLineSeries *Series::getSeries()
{
   return(series);
}


void Series::updateColor(QColor col)
{
   this->Color = col;
}


void Series::updateThickness(int thick)
{
   this->Thickness = thick;
}


int Series::findMin()
{
   int min = MAX_INPUT;

   for (int i = 0; i < Datas.size(); i++)
   {
      int t = Datas[i].ry();

      if (Datas[i].y() < min)
      {
         min = Datas[i].y();
      }
   }

   return(min);
}


int Series::findMax()
{
   int max = -1;

   for (int i = 0; i < Datas.size(); i++)
   {
      if (Datas[i].y() > max)
      {
         max = Datas[i].y();
      }
   }

   return(max);
}


int Series::getThickness() const
{
   return(Thickness);
}


const QColor &Series::getColor() const
{
   return(Color);
}


void Series::updateSeriesLine(bool updateData)
{
   if (updateData)
   {
      updateList();
      series->replace(Datas);
   }
   QPen pen;

   pen.setWidth(this->Thickness);
   series->setPen(pen);
   series->setColor(this->Color);
}


void Series::createSeriesLine()
{
   generateAndAddData();
   QPen pen;

   pen.setWidth(this->Thickness);
   series->setPen(pen);
   series->setColor(this->Color);
}
