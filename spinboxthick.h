#ifndef SPINBOXTHICK_H
#define SPINBOXTHICK_H

#include <iostream>
#include <QStyledItemDelegate>

class SpinBoxThick : public QStyledItemDelegate
{
public:
   SpinBoxThick(QObject *parent = nullptr);

   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

   void setEditorData(QWidget *editor, const QModelIndex &index) const override;
   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif // SPINBOXTHICK_H
