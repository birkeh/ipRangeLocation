#include "ccity.h"


cCity::cCity(const qint32& id) :
	m_id(id),
	m_name(""),
	m_lat(0.0),
	m_lon(0.0),
	m_lpRegion(nullptr)
{
}

qint32 cCity::id()
{
	return(m_id);
}

void cCity::setName(const QString& name)
{
	m_name = name;
}

QString cCity::name()
{
	return(m_name);
}

void cCity::setLat(const double& lat)
{
	m_lat = lat;
}

double cCity::lat()
{
	return(m_lat);
}

void cCity::setLon(const double& lon)
{
	m_lon = lon;
}

double cCity::lon()
{
	return(m_lon);
}

void cCity::setRegion(cRegion* lpRegion)
{
	m_lpRegion = lpRegion;
}

cRegion* cCity::region()
{
	return(m_lpRegion);
}

cCity* cCityList::add(const qint32& id)
{
	cCity*	lpNew	= find(id);

	if(lpNew)
		return(lpNew);

	lpNew	= new cCity(id);
	append(lpNew);
	return(lpNew);
}

cCity* cCityList::find(const qint32& id)
{
	for(int x = 0;x < count();x++)
	{
		if(at(x)->id() == id)
			return(at(x));
	}

	return(nullptr);
}
