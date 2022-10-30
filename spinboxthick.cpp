#include "spinboxthick.h"

#include <QSpinBox>

//! [0]
SpinBoxThick::SpinBoxThick(QObject *parent)
   : QStyledItemDelegate(parent)
{
}


//! [0]


//! [1]
QWidget *SpinBoxThick::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem & /* option */,
                                    const QModelIndex & /* index */) const
{
   QSpinBox *editor = new QSpinBox(parent);

   editor->setFrame(false);
   editor->setMinimum(0);
   editor->setMaximum(100);

   return(editor);
}


//! [1]


//! [2]
void SpinBoxThick::setEditorData(QWidget           *editor,
                                 const QModelIndex &index) const
{
   int value = index.model()->data(index, Qt::EditRole).toInt();

   std::cout << value;
   QSpinBox *spinBox = static_cast<QSpinBox *>(editor);

   spinBox->setValue(value);
}


//! [2]


//! [3]
void SpinBoxThick::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
   QSpinBox *spinBox = static_cast<QSpinBox *>(editor);

   spinBox->interpretText();


   model->setData(index, spinBox->value(), Qt::EditRole);
}


//! [3]


//! [4]
void SpinBoxThick::updateEditorGeometry(QWidget                    *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex & /* index */) const
{
   editor->setGeometry(option.rect);
}
//! [4]
