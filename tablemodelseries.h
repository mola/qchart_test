#ifndef TABLEMODELSERIES_H
#define TABLEMODELSERIES_H

#include <datamodelseries.h>
#include <iostream>
#include <QAbstractTableModel>
#include <QObject>

enum class TABLE_COLUMN_TYPE
{
   _NAME = 0,
   _COLOR,
   _THICKNESS,
};
class TableModelSeries : public QAbstractTableModel
{
public:
   explicit TableModelSeries(QObject *parent = nullptr);

   // QAbstractItemModel interface
public:
   int rowCount(const QModelIndex &parent) const;
   int columnCount(const QModelIndex &parent) const;
   QVariant data(const QModelIndex &index, int role) const;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const;
   bool insertRow(QString name, QColor col);
   void getSeriesData(int index);
   bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
   QList<DataModelSeries *> DataSeriesList;

   // QAbstractItemModel interface
};

#endif // TABLEMODELSERIES_H
