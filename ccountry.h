#ifndef CCOUNTRY_H
#define CCOUNTRY_H


#include "ccontinent.h"

#include <QMetaType>
#include <QString>
#include <QList>


class cCountry
{
public:
	cCountry(const qint32& id);

	qint32			id();

	void			setName(const QString& name);
	QString			name();

	void			setContinent(cContinent* lpContintent);
	cContinent*		continent();

private:
	qint32			m_id;
	QString			m_name;
	cContinent*		m_lpContinent;
};

Q_DECLARE_METATYPE(cCountry*)

class cCountryList : public QList<cCountry*>
{
public:
	cCountry*		add(const qint32& id);
	cCountry*		find(const qint32& id);
};

//Q_DECALRE_METATYPE(cCountryList*)

#endif // CCOUNTRY_H
