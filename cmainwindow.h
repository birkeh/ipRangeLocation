#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "ciprange.h"
#include "ciprangeitemdelegate.h"

#include "ccity.h"

#include <QMainWindow>
#include <QStandardItemModel>

#include <QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class cMainWindow; }
QT_END_NAMESPACE

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	cMainWindow(QWidget *parent = nullptr);
	~cMainWindow();

private:
	Ui::cMainWindow*			ui;
	QStandardItemModel*			m_lpIPRangeModel;

	QSqlDatabase				m_db;

	cIPRangeList				m_ipRangeList;
	cCityList					m_cityList;
	cRegionList					m_regionList;
	cCountryList				m_countryList;
	cContinentList				m_continentList;

	void						initUI();
	void						checkTables();
	void						loadIPRangeList();
	void						loadCityList();
	void						displayIPRangeList();

	void						saveRange(cIPRange* lpIPRange);

protected:
	void						closeEvent(QCloseEvent* event);

private slots:
	void						ipRangeChanged(cIPRange* lpIPRange, QStandardItem* lpItem);
	void						cityChanged(cIPRange* lpIPRange, QStandardItem* lpItem);
};
#endif // CMAINWINDOW_H
