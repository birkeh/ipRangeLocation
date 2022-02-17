#ifndef CREGION_H
#define CREGION_H


#include "ccountry.h"

#include <QMetaType>
#include <QString>
#include <QList>


class cRegion
{
public:
	cRegion(const qint32& id);

	qint32			id();

	void			setName(const QString& name);
	QString			name();

	void			setCountry(cCountry* lpCountry);
	cCountry*		country();

private:
	qint32			m_id;
	QString			m_name;
	cCountry*		m_lpCountry;
};

Q_DECLARE_METATYPE(cRegion*)

class cRegionList : public QList<cRegion*>
{
public:
	cRegion*		add(const qint32& id);
	cRegion*		find(const qint32& id);
};

//Q_DECALRE_METATYPE(cRegionList*)

#endif // CREGION_H
