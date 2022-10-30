#include "datamodelseries.h"

DataModelSeries::DataModelSeries(QString name, QColor col)
{
   Name  = name;
   Color = col;
}


const QString &DataModelSeries::getName() const
{
   return(Name);
}


void DataModelSeries::setName(const QString &newName)
{
   Name = newName;
}


const QColor &DataModelSeries::getColor() const
{
   return(Color);
}


void DataModelSeries::setColor(const QColor &newColor)
{
   Color = newColor;
}


int DataModelSeries::getThickness() const
{
   return(Thickness);
}


void DataModelSeries::setThickness(int newThickness)
{
   Thickness = newThickness;
}
