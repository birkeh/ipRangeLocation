#ifndef CIPADDRESS_H
#define CIPADDRESS_H


#include <QString>

#include <QMetaType>
#include <QString>
#include <QList>

class cIPRange;

/*!
 \brief The cIPAddress class provides IP address handling routines.

The IP address may be provided either as a string or as a 64bit-value.
For each IP address, a location name (address) may be set.

 \class cIPAddress cipaddress.h "cipaddress.h"
*/
class cIPAddress
{
public:
	/*!
	 \brief Creates a cIPAddress and initializes with default values.

	 The IP address may be set by setIPAddress.

	 \fn cIPAddress
	*/
	cIPAddress();
	/*!
	 \brief Creates a cIPAddress with the given <i>szIPAddress</i> and <i>szAddress</i>.

	 The IP address may also be set by setIPAddress.

	 \fn cIPAddress
	 \param szIPAddress IP address in text format (x.x.x.x)
	 \param szAddress Optional location name associated with the IP address
	*/
	cIPAddress(const QString& szIPAddress, const QString& szAddress = QString(""));
	/*!
	 \brief Sets the IP address.

	 \fn setIPAddress
	 \param szIPAddress IP address in text format (x.x.x.x)
	 \return TRUE on success, FALSE otherwise
	*/
	bool			setIPAddress(const QString& szIPAddress);
	/*!
	 \brief Sets the IP address.

	 \fn setIPAddress
	 \param iIPAddress IP address in binary format (64bit)
	 \return TRUE on success, FALSE otherwise
	*/
	bool			setIPAddress(const qint64& iIPAddress);
	/*!
	 \brief Returns the IP address in text format (x.x.x.x)

	 \fn IPAddress
	 \return IP address in text format.
	*/
	QString			IPAddress();
	/*!
	 \brief Returns the IP address in binary format (64bit)

	 \fn IPAddressBin
	 \return IP address in binary format.
	*/
	qint64			IPAddressBin();
	/*!
	 \brief Sets the location name corresponding to the IP address.

	 \fn setAddress
	 \param szAddress Name of the location.
	*/
	void			setAddress(const QString& szAddress);
	/*!
	 \brief Returns the name of the location (if set)

	 \fn address
	 \return Name of the location.
	*/
	QString			address();
	/*!
	 \brief Sets the IP range according to the IP address.

	 \fn setIPRange
	 \param lpIPRange Pointer to a cIPRange class
	*/
	void			setIPRange(cIPRange* lpIPRange);
	/*!
	 \brief Returns the pointer to the IP range (if set)

	 \fn ipRange
	 \return Pointer to a cIPRange object.
	*/
	cIPRange*		ipRange();

	/*!
	 \brief Validates the IP address.

	 The verification includes the check if the IP address is within the IP range (if set).
	 This is a static function.

	 \fn isValid
	 \param szIPAddress IP address to be checked in text format.
	 \return TRUE on success, False otherwise
	*/
	static bool		isValid(const QString& szIPAddress);

	/*!
	 \brief Converts a textual IP address into a 64bit-value

	 This is a static function.

	 \fn ip2bin
	 \param szIPAddress IP address in text format (x.x.x.x)
	 \return IP address in binary format (64bit)
	*/
	static qint64	ip2bin(const QString& szIPAddress);
	/*!
	 \brief Convers a binary IP address into text format (x.x.x.x)

	 This is a static function.

	 \fn bin2ip
	 \param iIPAddress IP address in binary format (64bit)
	 \return IP address in textual format.
	*/
	static QString	bin2ip(const qint64& iIPAddress);
private:
	qint64			m_iIPAddress;	/*!< This property holds the IP address in binary format (64bit).<br><b>Access functions:</b><br><table><tr><td>qint64</td><td><b>IPAddressBin</b>()</td></tr><tr><td>QString</td><td><b>IPAddress</b>()</td></tr><tr><td>void</td><td><b>setIPAddress</b>(const QString& szIPAddress)</td></tr><tr><td>void</td><td><b>setIPAddress</b>(const qint64& iIPAddress)</td></tr></table> */
	QString			m_szAddress;	/*!< This property holds the location of the IP address.<br>The default value is empty. <br><b>Access functions:</b><br><table><tr><td>QString</td><td><b>address</b>()</td></tr><tr><td>void</td><td><b>setAddress</b>(const QString& szAddress)</td></tr></table> */
	cIPRange*		m_lpIPRange;	/*!< This property holds the IP range of the IP address.<br>The default value is NULL. <br><b>Access functions:</b><br><table><tr><td>cIPRange</td><td><b>ipRange</b>()</td></tr><tr><td>void</td><td><b>setIPRange</b>(cIPRange* lpIPRange)</td></tr></table> */
};

Q_DECLARE_METATYPE(cIPAddress*)

/*!
 \brief The cIPAddressList class provides a list of IP addresses.

 \class cIPAddressList cipaddress.h "cipaddress.h"
*/
class cIPAddressList : public QList<cIPAddress*>
{
public:
	/*!
	 \brief Adds a new IP address entry to the list.

	 If the IP address already exists, the existing IP address is returned, otherwise, the newly created IP address is returned.

	 \fn add
	 \param szIPAddress IP address to be added.
	 \param szAddress Location name of the IP address (if available)
	 \return Pointer to the newly created or already existing cIPAddress
	*/
	cIPAddress*		add(const QString& szIPAddress, const QString& szAddress = QString(""));
	/*!
	 \brief Sorts the list of IP addresses.

	 \fn sort
	*/
	void			sort();
};

#endif // CIPADDRESS_H
