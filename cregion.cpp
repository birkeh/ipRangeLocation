#include "cregion.h"


cRegion::cRegion(const qint32& id) :
	m_id(id),
	m_name(""),
	m_lpCountry(nullptr)
{
}

qint32 cRegion::id()
{
	return(m_id);
}

void cRegion::setName(const QString& name)
{
	m_name = name;
}

QString cRegion::name()
{
	return(m_name);
}

void cRegion::setCountry(cCountry* lpCountry)
{
	m_lpCountry = lpCountry;
}

cCountry* cRegion::country()
{
	return(m_lpCountry);
}

cRegion* cRegionList::add(const qint32& id)
{
	cRegion*	lpNew	= find(id);

	if(lpNew)
		return(lpNew);

	lpNew	= new cRegion(id);
	append(lpNew);
	return(lpNew);
}

cRegion* cRegionList::find(const qint32& id)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == id)
			return(at(x));
	}

	return(nullptr);
}
