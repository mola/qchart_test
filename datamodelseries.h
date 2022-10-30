#ifndef DATAMODELSERIES_H
#define DATAMODELSERIES_H

#include <QColor>
#include <QString>
class DataModelSeries
{
public:
   DataModelSeries(QString name, QColor col);
   const QString &getName() const;
   void setName(const QString &newName);
   const QColor &getColor() const;
   void setColor(const QColor &newColor);
   int getThickness() const;
   void setThickness(int newThickness);

private:
   QString Name;
   QColor  Color;
   int     Thickness;
};

#endif // DATAMODELSERIES_H
