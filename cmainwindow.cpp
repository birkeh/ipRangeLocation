#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include <QSettings>
#include <QCloseEvent>

#include <QDir>

#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>


cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow)
{
	initUI();

	checkTables();

	loadCityList();
	loadIPRangeList();
	displayIPRangeList();
}

cMainWindow::~cMainWindow()
{
	if(m_db.isOpen())
		m_db.close();

	delete ui;
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
	QSettings	settings;
	settings.setValue("main/width", QVariant::fromValue(size().width()));
	settings.setValue("main/height", QVariant::fromValue(size().height()));
	settings.setValue("main/x", QVariant::fromValue(x()));
	settings.setValue("main/y", QVariant::fromValue(y()));
	if(this->isMaximized())
		settings.setValue("main/maximized", QVariant::fromValue(true));
	else
		settings.setValue("main/maximized", QVariant::fromValue(false));

	event->accept();
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

	m_lpIPRangeModel			= new QStandardItemModel(0, 1);
	ui->m_lpIPRangeList->setModel(m_lpIPRangeModel);
	ui->m_lpIPRangeList->setItemDelegate(new cIPRangeItemDelegate());

	connect((cIPRangeItemDelegate*)ui->m_lpIPRangeList->itemDelegate(), SIGNAL(ipRangeChanged(cIPRange*,QStandardItem*)), this, SLOT(ipRangeChanged(cIPRange*,QStandardItem*)));
	connect((cIPRangeItemDelegate*)ui->m_lpIPRangeList->itemDelegate(), SIGNAL(cityChanged(cIPRange*,QStandardItem*)), this, SLOT(cityChanged(cIPRange*,QStandardItem*)));
}

void cMainWindow::checkTables()
{
	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName("localhost");
	m_db.setDatabaseName(QString("%1%2ipRangeLocation.sqlite").arg(QDir::homePath()).arg(QDir::separator()));
	if(!m_db.open())
		return;

	QSqlQuery	query(m_db);

	if(!m_db.tables().contains("ip_range_location"))
	{
		query.exec("CREATE TABLE ip_range_location ( "
				   "name TEXT, "
				   "cityID INTEGER, "
				   "subnet INTEGER, "
				   "prefix INTEGER, "
				   "subnet1 INTEGER, "
				   "subnet2 INTEGER, "
				   "subnet3 INTEGER, "
				   "mask INTEGER, "
				   "iplow INTEGER, "
				   "iphigh INTEGER)");
	}

	if(!m_db.tables().contains("continent"))
	{
		query.exec("CREATE TABLE continent ( "
				   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
				   "name STRING)");
	}

	if(!m_db.tables().contains("country"))
	{
		query.exec("CREATE TABLE country ( "
				   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
				   "name STRING, "
				   "continentID INTEGER, "
				   "CONSTRAINT country_continentID_FK FOREIGN KEY (continentID) REFERENCES continent(id))");
	}

	if(!m_db.tables().contains("region"))
	{
		query.exec("CREATE TABLE region ( "
				   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
				   "name STRING, "
				   "countryID INTEGER, "
				   "CONSTRAINT region_countryID_FK FOREIGN KEY (countryID) REFERENCES country(id))");
	}

	if(!m_db.tables().contains("city"))
	{
		query.exec("CREATE TABLE city ( "
				   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
				   "name STRING, "
				   "lat DOUBLE, "
				   "lon DOUBLE, "
				   "regionID INTEGER, "
				   "CONSTRAINT city_regionID_FK FOREIGN KEY (regionID) REFERENCES region(id))");
	}
}

void cMainWindow::loadCityList()
{
	m_cityList.clear();

	QSqlQuery	query;

	query.exec("SELECT		c.id id, "
			   "			c.name cityName, "
			   "			c.lat lat, "
			   "			c.lon lon, "
			   "			c.regionID, "
			   "			r.name regionName, "
			   "			r.countryID countryID, "
			   "			co.name countryName, "
			   "			co.continentID continentID, "
			   "			con.name continentName "
			   "FROM		city c "
			   "LEFT JOIN	region r ON (c.regionID = r.id) "
			   "LEFT JOIN	country co ON (r.countryID = co.id) "
			   "LEFT JOIN	continent con ON (co.continentID = con.id) "
			   "ORDER BY 	con.name, "
			   "			co.name, "
			   "			c.name;");
	while(query.next())
	{
		cContinent*	lpContinent	= m_continentList.add(query.value("continentID").toInt());
		lpContinent->setName(query.value("continentName").toString());

		cCountry*	lpCountry	= m_countryList.add(query.value("countryID").toInt());
		lpCountry->setName(query.value("countryName").toString());
		lpCountry->setContinent(lpContinent);

		cRegion*	lpRegion	= m_regionList.add(query.value("regionID").toInt());
		lpRegion->setName(query.value("regionName").toString());
		lpRegion->setCountry(lpCountry);

		cCity*	lpCity	= m_cityList.add(query.value("id").toInt());
		lpCity->setName(query.value("cityName").toString());
		lpCity->setRegion(lpRegion);
		lpCity->setLat(query.value("lat").toDouble());
		lpCity->setLon(query.value("lon").toDouble());
	}
}

void cMainWindow::loadIPRangeList()
{
	m_ipRangeList.clear();

	QSqlQuery	query(m_db);

	query.exec("SELECT name, cityID FROM ip_range_location");
	while(query.next())
	{
		cIPRange*	lpIPRange	= m_ipRangeList.add(query.value("name").toString());
		lpIPRange->setLocation(query.value("cityID").toInt());
	}

	m_ipRangeList.sort();
	m_ipRangeList.verify();
}

void cMainWindow::displayIPRangeList()
{
	m_lpIPRangeModel->clear();

	QStringList	header;
	header << "Name" << "Range" << "Base IP" << "Prefix" << "Subnet Mask" << "Broadcast IP" << "First IP" << "Last IP" << "Location";

	m_lpIPRangeModel->setHorizontalHeaderLabels(header);

	for(int x = 0;x < m_ipRangeList.count();x++)
	{
		QList<QStandardItem*>	lpItems;

		for(int z = 0;z < header.count();z++)
			lpItems.append(new QStandardItem);

		cIPRange*		lpRange		= m_ipRangeList.at(x);
//LOCATION		cLocation*		lpLocation	= m_locationList.find(lpRange->location());

		lpItems.at(0)->setText(lpRange->name());
		lpItems.at(1)->setText(lpRange->range());
		lpItems.at(2)->setText(lpRange->IPAddress().IPAddress());
		lpItems.at(3)->setText(QString("%1").arg(lpRange->prefix()));
		lpItems.at(4)->setText(lpRange->netmask());
		lpItems.at(5)->setText(lpRange->broadcastIPAddress());
		lpItems.at(6)->setText(lpRange->firstIPAddress());
		lpItems.at(7)->setText(lpRange->lastIPAddress());
//		if(lpLocation)
//		{
//			lpItems.at(8)->setText(lpLocation->name());

//			QString	szHint	= QString("Name: %1").arg(lpLocation->name());

//			if(!lpLocation->location().isEmpty())
//				szHint.append(QString("\nLocation: %1").arg(lpLocation->location()));

//			if(!lpLocation->alternateLocation().isEmpty())
//				szHint.append(QString("\nAlternate Location: %1").arg(lpLocation->alternateLocation()));

//			if(!lpLocation->address().isEmpty())
//				szHint.append(QString("\nAddress: %1").arg(lpLocation->address()));

//			if(!lpLocation->city().isEmpty())
//				szHint.append(QString("\nCity: %1").arg(lpLocation->city()));

//			if(lpLocation->postalCode() > 999)
//				szHint.append(QString("\nPostal Code: %1").arg(lpLocation->postalCode()));

//			if(!lpLocation->federalState().isEmpty())
//				szHint.append(QString("\nFederal State: %1").arg(lpLocation->federalState()));

//			if(!lpLocation->country().isEmpty())
//				szHint.append(QString("\nCountry: %1").arg(lpLocation->country()));

//			lpItems.at(8)->setToolTip(szHint);
//		}

		lpItems.at(0)->setData(QVariant::fromValue(lpRange), Qt::UserRole);
//		lpItems.at(8)->setData(QVariant::fromValue(&m_locationList), Qt::UserRole);

		if(!lpRange->ok())
			lpItems.at(0)->setBackground(Qt::red);

		m_lpIPRangeModel->appendRow(lpItems);
	}

	for(int z = 0;z < header.count();z++)
		ui->m_lpIPRangeList->resizeColumnToContents(z);
}

void cMainWindow::ipRangeChanged(cIPRange *lpIPRange, QStandardItem *lpItem)
{
	QList<QStandardItem*>	lpItems;
	QModelIndex				index	= lpItem->index();
	QStandardItemModel*		lpModel	= (QStandardItemModel*)index.model();

	for(int x = 0;x < 9;x++)
		lpItems.append(lpModel->itemFromIndex(lpModel->index(index.row(), x)));

	lpItems.at(0)->setText(lpIPRange->name());
	lpItems.at(1)->setText(lpIPRange->range());
	lpItems.at(2)->setText(lpIPRange->IPAddress().IPAddress());
	lpItems.at(3)->setText(QString("%1").arg(lpIPRange->prefix()));
	lpItems.at(4)->setText(lpIPRange->netmask());
	lpItems.at(5)->setText(lpIPRange->broadcastIPAddress());
	lpItems.at(6)->setText(lpIPRange->firstIPAddress());
	lpItems.at(7)->setText(lpIPRange->lastIPAddress());

	m_ipRangeList.sort();
	m_ipRangeList.verify();

	qint32					iPos	= m_ipRangeList.position(lpIPRange);
	qint32					iOldPos	= index.row();

	if(iPos >= 0)
	{
		QList<QStandardItem*>	itemList	= m_lpIPRangeModel->takeRow(index.row());
		m_lpIPRangeModel->insertRow(iPos, itemList);
		ui->m_lpIPRangeList->setCurrentIndex(lpModel->index(iPos, 0));
	}

	QBrush	brush	= m_lpIPRangeModel->item(0, 1)->background();

	qint32	iMin;
	qint32	iMax;

	iMin	= (iPos > 0) ? iPos-1 : 0;
	iMax	= (iPos < (m_lpIPRangeModel->rowCount()-1)) ? iPos + 2 : m_lpIPRangeModel->rowCount();
	for(int x = iMin;x < iMax;x++)
	{
		QStandardItem*	lpItem	= m_lpIPRangeModel->item(x, 0);
		cIPRange*		lpRange	= qvariant_cast<cIPRange*>(lpItem->data(Qt::UserRole));
		if(lpRange && lpRange->ok())
			lpItem->setBackground(brush);
		else
			lpItem->setBackground(Qt::red);
	}

	iMin	= (iOldPos > 0) ? iOldPos-1 : 0;
	iMax	= (iOldPos < (m_lpIPRangeModel->rowCount()-1)) ? iOldPos + 2 : m_lpIPRangeModel->rowCount();
	for(int x = iMin;x < iMax;x++)
	{
		QStandardItem*	lpItem	= m_lpIPRangeModel->item(x, 0);
		cIPRange*		lpRange	= qvariant_cast<cIPRange*>(lpItem->data(Qt::UserRole));
		if(lpRange && lpRange->ok())
			lpItem->setBackground(brush);
		else
			lpItem->setBackground(Qt::red);
	}

//	saveRange(lpIPRange);
//	filterError();
}

void cMainWindow::cityChanged(cIPRange* lpIPRange, QStandardItem* /*lpItem*/)
{
//	saveRange(lpIPRange);
}

void cMainWindow::saveRange(cIPRange* lpIPRange)
{
//	QString		strSQL;
//	QSqlQuery	query(m_db);

//	QString		szName		= lpIPRange->name();
//	qint32		iLocation	= lpIPRange->location();
//	qint32		iRange		= cIPAddress::ip2bin(lpIPRange->range());
//	qint32		iPrefix		= lpIPRange->prefix();
//	qint64		iSubnet1	= lpIPRange->subnet1BIN();
//	qint64		iSubnet2	= lpIPRange->subnet2BIN();
//	qint64		iSubnet3	= lpIPRange->subnet3BIN();
//	quint64		iNetmask	= lpIPRange->netmaskBin();
//	qint64		iFirstIP	= lpIPRange->firstIPAddressBin();
//	qint64		iLastIP		= lpIPRange->lastIPAddressBin();
//	QString		szOldName	= lpIPRange->oldName();

//	strSQL	= QString("UPDATE ip_range_location SET name='%1', location_id=%2, subnet=%3, prefix=%4, subnet1=%5, subnet2=%6, subnet3=%7, mask=%8, iplow=%9, iphigh=%10 WHERE name='%11';")
//			.arg(szName)
//			.arg(iLocation)
//			.arg(iRange)
//			.arg(iPrefix)
//			.arg(iSubnet1)
//			.arg(iSubnet2)
//			.arg(iSubnet3)
//			.arg(iNetmask)
//			.arg(iFirstIP)
//			.arg(iLastIP)
//			.arg(szOldName);

//	query.exec(strSQL);
}
