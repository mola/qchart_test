#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <QColor>
#include <QColorDialog>
#include <QObject>
#include <QStyledItemDelegate>
#include <QWidget>

class colorDelegate : public QStyledItemDelegate
{
   Q_OBJECT
public:
   explicit colorDelegate(QObject *parent = nullptr);

   // QAbstractItemDelegate interface
public:
   void setEditorData(QWidget *editor, const QModelIndex &index) const;
   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COLORDELEGATE_H
