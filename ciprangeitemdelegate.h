#ifndef CIPRANGEITEMDELEGATE_H
#define CIPRANGEITEMDELEGATE_H


#include "ciprange.h"

#include <QStyledItemDelegate>
#include <QStandardItem>


/*!
 \brief The cIPRangeItemDelegate class provides routines to display IP range items depending on the state.

 \class cIPRangeItemDelegate ciprangeitemdelegate.h "ciprangeitemdelegate.h"
*/
class cIPRangeItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	/*!
	 \brief Creates a cIPRangeItemDelegate with the given <i>parent</i>.

	 \fn cIPRangeItemDelegate
	 \param parent Parent of this class.
	*/
	cIPRangeItemDelegate(QObject* parent = 0);
	/*!
	 \brief Destroys this object.

	 \fn ~cIPRangeItemDelegate
	*/
	~cIPRangeItemDelegate();

	/*!
	 \brief Reimplemented from QStyledItemDelegate.

	 Returns the widget used to edit the item specified by <i>index</i> for editing. The <i>parent</i> widget and <i>style option</i> are used to control how the editor widget appears.

	 \fn createEditor
	 \param parent Parent of the editor item.
	 \param option Options of the editor item.
	 \param index QModelIndex of the item within the list.
	 \return Edit widget.
	*/
	virtual QWidget*	createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	/*!
	 \brief Reimplemented from QStyledItemDelegate.

	 Sets the data to be displayed and edited by the <i>editor</i> from the data model item specified by the model <i>index</i>.

	\fn setEditorData
	 \param editor Pointer to the editor.
	 \param index QModelIndex of the item within the list.
	*/
	virtual void		setEditorData(QWidget *editor, const QModelIndex &index) const;
	/*!
	 \brief Reimplemented from QStyledItemDelegate.

	 Gets data from the <i>editor</i> widget and stores it in the specified <i>model</i> at the item <i>index</i>.

	 \fn setModelData
	 \param editor Pointer to the editor.
	 \param model Model of the item.
	 \param index QModelIndex of the item within the list.
	*/
	virtual void		setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:
	/*!
	 \brief This function is called when the IP range has been changed.

	 \fn ipRangeChanged
	 \param lpIPRange Pointer to the new IP range.
	 \param lpItem Pointer to the item within the list that has been changed.
	*/
	void				ipRangeChanged(cIPRange* lpIPRange, QStandardItem* lpItem) const;
	/*!
	 \brief This function is called when the location has been changed.

	 \fn locationChanged
	 \param lpIPRange Pointer to the IP range that has been changed.
	 \param lpItem Pointer to the item within the list that has been changed.
	*/
	void				locationChanged(cIPRange* lpIPRange, QStandardItem* lpItem) const;
};

#endif // CIPRANGEITEMDELEGATE_H
