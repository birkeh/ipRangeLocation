#include "ccountry.h"


cCountry::cCountry(const qint32& id) :
	m_id(id),
	m_name(""),
	m_lpContinent(nullptr)
{
}

qint32 cCountry::id()
{
	return(m_id);
}

void cCountry::setName(const QString& name)
{
	m_name = name;
}

QString cCountry::name()
{
	return(m_name);
}

void cCountry::setContinent(cContinent* lpContinent)
{
	m_lpContinent = lpContinent;
}

cContinent* cCountry::continent()
{
	return(m_lpContinent);
}

cCountry* cCountryList::add(const qint32& id)
{
	cCountry*	lpNew	= find(id);

	if(lpNew)
		return(lpNew);

	lpNew	= new cCountry(id);
	append(lpNew);
	return(lpNew);
}

cCountry* cCountryList::find(const qint32& id)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == id)
			return(at(x));
	}

	return(nullptr);
}
