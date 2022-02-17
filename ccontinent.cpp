#include "ccontinent.h"


cContinent::cContinent(const qint32& id) :
	m_id(id),
	m_name("")
{
}

qint32 cContinent::id()
{
	return(m_id);
}

void cContinent::setName(const QString& name)
{
	m_name = name;
}

QString cContinent::name()
{
	return(m_name);
}

cContinent* cContinentList::add(const qint32& id)
{
	cContinent*	lpNew	= find(id);

	if(lpNew)
		return(lpNew);

	lpNew	= new cContinent(id);
	append(lpNew);
	return(lpNew);
}

cContinent* cContinentList::find(const qint32& id)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == id)
			return(at(x));
	}

	return(nullptr);
}
