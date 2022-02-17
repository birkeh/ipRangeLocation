#include "ciprangeitemdelegate.h"
//LOCATION #include "clocation.h"

#include <QComboBox>
#include <QLineEdit>


cIPRangeItemDelegate::cIPRangeItemDelegate(QObject* parent) :
	QStyledItemDelegate(parent)
{
}

cIPRangeItemDelegate::~cIPRangeItemDelegate()
{
}

QWidget* cIPRangeItemDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	if(index.column() == 0)
		return(QStyledItemDelegate::createEditor(parent, option, index));

	if(index.column() != 8)
		return(0);

//LOCATION 	cLocationList*	lpLocationList	= qvariant_cast<cLocationList*>(index.data(Qt::UserRole));
	QComboBox*		lpComboBox		= new QComboBox(parent);

//LOCATION 	for(int x = 0;x < lpLocationList->count();x++)
//LOCATION 		lpComboBox->addItem(lpLocationList->at(x)->name(), lpLocationList->at(x)->locationID());

	return(lpComboBox);
}

void cIPRangeItemDelegate::setEditorData ( QWidget *editor, const QModelIndex &index ) const
{
	QComboBox*	lpComboBox	= qobject_cast<QComboBox*>(editor);

	if(lpComboBox)
	{
		QString	currentText	= index.data(Qt::EditRole).toString();
		int		cbIndex		= lpComboBox->findText(currentText);

		if(cbIndex >= 0)
			lpComboBox->setCurrentIndex(cbIndex);
	}
	else
	{
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void cIPRangeItemDelegate::setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	QComboBox*	lpComboBox	= qobject_cast<QComboBox*>(editor);
	QLineEdit*	lpLineEdit	= qobject_cast<QLineEdit*>(editor);

	if(lpComboBox)
	{
		model->setData(index, lpComboBox->currentText(), Qt::EditRole);
		QModelIndex	index1		= model->index(index.row(), 0);
		cIPRange*	lpIPRange	= qvariant_cast<cIPRange*>(index1.data(Qt::UserRole));

		if(lpIPRange->location() != lpComboBox->currentData().toInt())
		{
			QStandardItemModel*	lpModel		= (QStandardItemModel*)index.model();
			QStandardItem*		lpItem		= lpModel->itemFromIndex(index1);

			lpIPRange->setLocation(lpComboBox->currentData().toInt());
			locationChanged(lpIPRange, lpItem);
		}
	}
	else if(lpLineEdit)
	{
		QString				strText		= lpLineEdit->text();

		if(!cIPRange::isValid(strText))
			return;

		cIPRange*			lpIPRange	= qvariant_cast<cIPRange*>(index.data(Qt::UserRole));
		QStandardItemModel*	lpModel		= (QStandardItemModel*)index.model();
		QStandardItem*		lpItem		= lpModel->itemFromIndex(index);

		lpIPRange->setIPRange(strText);
		QStyledItemDelegate::setModelData(editor, model, index);
		emit ipRangeChanged(lpIPRange, lpItem);
	}
}
