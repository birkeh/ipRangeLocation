#include "cipaddress.h"

#include <QStringList>


bool rangeSort(cIPAddress* lpIPAddress1, cIPAddress* lpIPAddress2)
{
	return(lpIPAddress1->IPAddressBin() < lpIPAddress2->IPAddressBin());
}

cIPAddress::cIPAddress() :
	m_szAddress(""),
	m_lpIPRange(0)
{
	setIPAddress("0.0.0.0");
}

cIPAddress::cIPAddress(const QString& szIPAddress, const QString& szAddress) :
	m_szAddress(szAddress),
	m_lpIPRange(0)
{
	setIPAddress(szIPAddress);
}

bool cIPAddress::setIPAddress(const QString& szIPAddress)
{
	if(!isValid(szIPAddress))
		return(false);

	m_iIPAddress	= ip2bin(szIPAddress);

	return(true);
}

bool cIPAddress::setIPAddress(const qint64& iIPAddress)
{
	m_iIPAddress	= iIPAddress;
}

bool cIPAddress::isValid(const QString& szIPAddress)
{
	QStringList	szList	= szIPAddress.split(".");

	if(szList.count() != 4)
		return(false);

	qint64	ip;

	for(int x = 0;x < 4;x++)
	{
		ip	= szList[0].toLong();
		if(ip < 0 || ip > 255)
			return(false);
	}

	return(true);
}

QString cIPAddress::IPAddress()
{
	return(bin2ip(m_iIPAddress));
}

qint64 cIPAddress::IPAddressBin()
{
	return(m_iIPAddress);
}

void cIPAddress::setAddress(const QString& szAddress)
{
	m_szAddress	= szAddress;
}

QString cIPAddress::address()
{
	return(m_szAddress);
}

void cIPAddress::setIPRange(cIPRange* lpIPRange)
{
	m_lpIPRange	= lpIPRange;
}

cIPRange* cIPAddress::ipRange()
{
	return(m_lpIPRange);
}

qint64 cIPAddress::ip2bin(const QString& szIPAddress)
{
	qint64	ip	= 0;
	qint64	ipHelper;

	QStringList	szList	= szIPAddress.split(".");

	for(int x = 0;x < 4;x++)
	{
		ipHelper	= szList[x].toLong();
		ip	+= ipHelper << (8*(3-x));
	}

	return(ip);
}

QString cIPAddress::bin2ip(const qint64& iIPAddress)
{
	QString	szIP	= QString("%1.%2.%3.%4").arg((iIPAddress >> 24) & 0xFF).arg((iIPAddress >> 16) & 0xFF).arg((iIPAddress >> 8) & 0xFF).arg(iIPAddress& 0xFF);
	return(szIP);
}

cIPAddress* cIPAddressList::add(const QString& szIPAddress, const QString& szAddress)
{
	cIPAddress*	lpNew;
/*
	for(int x = 0;x < count();x++)
	{
		if(at(x)->IPAddress() == szIPAddress)
			return(at(x));
	}
*/
	lpNew	= new cIPAddress(szIPAddress, szAddress);
	append(lpNew);
	return(lpNew);
}

void cIPAddressList::sort()
{
	std::sort(begin(), end(), rangeSort);
}
