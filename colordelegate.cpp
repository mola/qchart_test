#include "colordelegate.h"

colorDelegate::colorDelegate(QObject *parent)
   : QStyledItemDelegate{parent}
{
}


QWidget *colorDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem & /* option */,
                                     const QModelIndex & /* index */) const
{
   QColorDialog *editor = new QColorDialog(parent);

   editor->setCurrentColor(Qt::black);
   return(editor);
}


void colorDelegate::setEditorData(QWidget           *editor,
                                  const QModelIndex &index) const
{
   QVariant value = index.model()->data(index, Qt::EditRole);
   // QColor   color = static_cast<QColor>(value);
//      QColorDialog *spinBox = static_cast<QColorDialog *>(editor);

//      spinBox->setValue(value);
}


//! [2]


//! [3]
void colorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
   QColorDialog *spinBox = static_cast<QColorDialog *>(editor);
   QColor       value    = Qt::black;

   value = spinBox->selectedColor();

   model->setData(index, value, Qt::BackgroundColorRole);
}


//! [3]


//! [4]
void colorDelegate::updateEditorGeometry(QWidget                    *editor,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex & /* index */) const
{
   editor->setGeometry(option.rect);
}
//! [4]
