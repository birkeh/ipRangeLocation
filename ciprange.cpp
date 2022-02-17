#include "ciprange.h"

#include <QFile>
#include <QDomDocument>
#include <algorithm>


bool rangeSort(cIPRange* lpRange1, cIPRange* lpRange2)
{
	return(lpRange1->firstIPAddressBin() < lpRange2->firstIPAddressBin());
}

cIPRange::cIPRange() :
	m_szOldName(""),
	m_iLocation(-1),
	m_bOK(true)
{
	setIPRange("0.0.0.0/24");
}

cIPRange::cIPRange(const QString& szIPRange) :
	m_iLocation(-1),
	m_bOK(true)
{
	setIPRange(szIPRange);
}

bool cIPRange::isValid(const QString& szIPRange)
{
	if(!szIPRange.contains("/"))
		return(false);

	QString	szIPAddress;
	QString	szPrefix;

	szIPAddress	= szIPRange.left(szIPRange.indexOf("/"));
	szPrefix	= szIPRange.mid(szIPAddress.length()+1);

	if(!cIPAddress::isValid(szIPAddress))
		return(false);

	if(szPrefix.toInt() < 1 || szPrefix.toInt() > 32)
		return(false);

	return(true);
}

bool cIPRange::setIPRange(const QString& szIPRange)
{
	if(!szIPRange.contains("/"))
		return(false);

	QString	szIPAddress;
	QString	szPrefix;

	szIPAddress	= szIPRange.left(szIPRange.indexOf("/"));
	szPrefix	= szIPRange.mid(szIPAddress.length()+1);

	if(!cIPAddress::isValid(szIPAddress))
		return(false);

	if(szPrefix.toInt() < 1 || szPrefix.toInt() > 32)
		return(false);

	m_iPrefix	= szPrefix.toInt();
	m_IPAddress.setIPAddress(cIPAddress::ip2bin(szIPAddress) & ~((1 << (32 - m_iPrefix))-1));

	m_szName	= szIPRange;
	if(m_szOldName.isEmpty())
		m_szOldName	= m_szName;

	return(true);
}

QString cIPRange::firstIPAddress()
{
	return(cIPAddress::bin2ip(firstIPAddressBin()));
}

QString cIPRange::lastIPAddress()
{
	return(cIPAddress::bin2ip(lastIPAddressBin()));
}

qint64 cIPRange::firstIPAddressBin()
{
	return((m_IPAddress.IPAddressBin() & netmaskBin())+1);
}

qint64 cIPRange::lastIPAddressBin()
{
	return((m_IPAddress.IPAddressBin() | ~netmaskBin())-1);
}

QString cIPRange::broadcastIPAddress()
{
	return(cIPAddress::bin2ip(m_IPAddress.IPAddressBin() | ~netmaskBin()));
}

qint64 cIPRange::broadcastIPAddressBIN()
{
	return(m_IPAddress.IPAddressBin() | ~netmaskBin());
}

quint64 cIPRange::netmaskBin()
{
	return(~((1 << (32 - m_iPrefix))-1));
}

QString cIPRange::netmask()
{
	return(cIPAddress::bin2ip(netmaskBin()));
}

cIPAddress cIPRange::IPAddress()
{
	return(m_IPAddress);
}

qint16 cIPRange::prefix()
{
	return(m_iPrefix);
}

QString cIPRange::range()
{
	return(QString("%1/%2").arg(m_IPAddress.IPAddress()).arg(m_iPrefix));
}

qint64 cIPRange::subnetBIN()
{
	return(m_IPAddress.IPAddressBin());
}

qint64 cIPRange::subnet1BIN()
{
	return(subnetBIN() & 0xFFFF0000);
}

qint64 cIPRange::subnet2BIN()
{
	return(subnetBIN() & 0xFF000000);
}

qint64 cIPRange::subnet3BIN()
{
	return(subnetBIN() & 0xFFF00000);
}

void cIPRange::setOK(const bool& bOK)
{
	m_bOK	= bOK;
}

bool cIPRange::ok()
{
	return(m_bOK);
}

QString cIPRange::name()
{
	return(m_szName);
}

QString cIPRange::oldName()
{
	return(m_szOldName);
}

void cIPRange::setLocation(const qint32 iLocation)
{
	m_iLocation	= iLocation;
}

qint32 cIPRange::location()
{
	return(m_iLocation);
}

bool cIPRange::ipInRange(const QString& szIPAddress)
{
	return(ipInRange(cIPAddress::ip2bin(szIPAddress)));
}

bool cIPRange::ipInRange(const qint64& iIPAddress)
{
	if(iIPAddress >= firstIPAddressBin() && iIPAddress <= lastIPAddressBin())
		return(true);
	return(false);
}

void cIPRange::setName(QString& szName)
{
	m_szName	= szName;
}

void cIPRangeList::clean()
{
	clear();
}

cIPRange* cIPRangeList::add(const QString& szIPRange)
{
	if(!cIPRange::isValid(szIPRange))
		return(0);

	cIPRange*	lpNew	= new cIPRange(szIPRange);

	for(int x = 0;x < count();x++)
	{
		if(lpNew->firstIPAddressBin() == at(x)->firstIPAddressBin() &&
				lpNew->lastIPAddressBin() == at(x)->lastIPAddressBin())
		{
			delete lpNew;
			return(at(x));
		}
	}
	append(lpNew);

	return(lpNew);
}

void cIPRangeList::sort()
{
	std::sort(begin(), end(), rangeSort);
}

void cIPRangeList::verify()
{
	if(!count())
		return;

	if(count() == 1)
		at(0)->setOK(true);

	for(int x = 0;x < count();x++)
		at(x)->setOK(true);

	for(int x = 0;x < count()-1;x++)
	{
		cIPRange*	r1	= at(x);
		cIPRange*	r2	= at(x+1);

		if(r1->lastIPAddressBin() >= r2->firstIPAddressBin())
		{
			r1->setOK(false);
			r2->setOK(false);
		}
	}
}

cIPRange* cIPRangeList::findRange(const QString& szIPAddress)
{
	return(findRange(cIPAddress::ip2bin(szIPAddress)));
}

cIPRange* cIPRangeList::findRange(const qint64& iIPAddress)
{
	if(iIPAddress < at(0)->firstIPAddressBin())
		return(0);

	if(at(0)->ipInRange(iIPAddress))
		return(at(0));
	if(at(count()-1)->ipInRange(iIPAddress))
		return(at(count()-1));

	qint32	iStep	= (count()-1)/2;

	for(int x = 0;x < count();x += iStep)
	{
		cIPRange*	lpIPRange	= at(x);
		if(iIPAddress < lpIPRange->firstIPAddressBin())
		{
			if(iStep == 1)
				return(0);
			x -= iStep;
			iStep /= 2;
			continue;
		}
		else if(iIPAddress > lpIPRange->lastIPAddressBin())
			continue;
		else
			return(lpIPRange);
	}

	return(0);
}

qint32 cIPRangeList::position(cIPRange* lpIPRange)
{
	return(indexOf(lpIPRange));
}
