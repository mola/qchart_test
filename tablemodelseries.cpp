#include "tablemodelseries.h"

TableModelSeries::TableModelSeries(QObject *parent)
   : QAbstractTableModel{parent}
{
}


int TableModelSeries::rowCount(const QModelIndex &parent) const
{
   if (parent.isValid())
   {
      return(0);
   }
   return(DataSeriesList.count());
}


int TableModelSeries::columnCount(const QModelIndex &parent) const
{
   if (parent.isValid())
   {
      return(0);
   }
   return(3);
}


QVariant TableModelSeries::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
   {
      return(QVariant());
   }

   if (role == Qt::TextAlignmentRole)
   {
      Qt::Alignment alignment = Qt::AlignHCenter | Qt::AlignVCenter;

      return(QVariant(alignment));
   }

   if (role == Qt::DisplayRole || role == Qt::EditRole)
   {
      const auto &Series = DataSeriesList[index.row()];

      switch (index.column())
      {
      case (int)TABLE_COLUMN_TYPE::_NAME:
         return(Series->getName());

      case (int)TABLE_COLUMN_TYPE::_COLOR:
         return(Series->getColor());

      case (int)TABLE_COLUMN_TYPE::_THICKNESS:
         return(Series->getThickness());

      default:
         return(QVariant());
      }   // switch
   }
   return(QVariant());
}


QVariant TableModelSeries::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
   {
      return(QVariant());
   }

   switch (section)
   {
   case (int)TABLE_COLUMN_TYPE::_NAME:
      return("Name");

   case (int)TABLE_COLUMN_TYPE::_COLOR:
      return("Color");

   case (int)TABLE_COLUMN_TYPE::_THICKNESS:
      return("Thickness");

   default:
      return(QVariant());
   }
}


bool TableModelSeries::insertRow(QString name, QColor col)
{
   beginInsertRows({}, DataSeriesList.count(), DataSeriesList.count());
   DataModelSeries *data = new DataModelSeries(name, col);

   DataSeriesList.push_front(data);
   endInsertRows();
   return(true);
}


bool TableModelSeries::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (const auto col = index.column(); col == (int)TABLE_COLUMN_TYPE::_THICKNESS)
   {
      std::cout << "JJ";

      if (const auto row = index.row(); role == Qt::EditRole)
      {
         std::cout << "BB";
         this->DataSeriesList[row]->setThickness(value.toInt());
         return(true);
      }
   }
   return(false);
   //->DataSeriesList[index.row()]->setThickness(value.toInt());
}
