#ifndef CLOCATIONLIST_H
#define CLOCATIONLIST_H


#include "cregion.h"

#include <QMetaType>
#include <QString>
#include <QList>


class cCity
{
public:
	cCity(const qint32& id);

	qint32			id();

	void			setName(const QString& name);
	QString			name();

	void			setLat(const double& lat);
	double			lat();

	void			setLon(const double& lon);
	double			lon();

	void			setRegion(cRegion* lpRegion);
	cRegion*		region();

private:
	qint32			m_id;
	QString			m_name;
	double			m_lat;
	double			m_lon;
	cRegion*		m_lpRegion;
};

Q_DECLARE_METATYPE(cCity*)

class cCityList : public QList<cCity*>
{
public:
	cCity*			add(const qint32& id);
	cCity*			find(const qint32& id);
};

//Q_DECALRE_METATYPE(cCityList*)

#endif // CLOCATIONLIST_H
