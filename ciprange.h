#ifndef CIPRANGE_H
#define CIPRANGE_H


#include "cipaddress.h"

#include <QMetaType>
#include <QString>
#include <QList>


class cIPRangeList;

/*!
 \brief The cIPRange class provides IP range handling routines.

The IP range is calculated from text. The class provides routines to validate IP addresses, provides information of the range and includes helper functions for database export.

 \class cIPRange ciprange.h "ciprange.h"
*/
class cIPRange
{
public:
	/*!
	 \brief Creates an empty cIPRange and initializes with default values.

	 The range may be set by setIPRange.

	 \fn cIPRange
	*/
	cIPRange();
	/*!
	 \brief Creates a cIPRange with the given <i>szIPRange</i>.

	 The required values are calculated from text.

	 \fn cIPRange
	 \param szIPRange
	*/
	cIPRange(const QString& szIPRange);

	/*!
	 \brief Verifies the given IP range.

	 This is a static function.

	 \fn isValid
	 \param szIPRange IP range to be verified.
	 \return TRUE on success, FALSE otherwise.
	*/
	static bool		isValid(const QString& szIPRange);

	/*!
	 \brief Sets the IP range. The required values are calculated from text;

	 \fn setIPRange
	 \param szIPRange IP range for calculation.
	 \return TRUE on success, FALSE otherwise.
	*/
	bool			setIPRange(const QString& szIPRange);
	/*!
	 \brief Returns the first valid IP address of the IP range.

	 \fn firstIPAddress
	 \return First valid IP address in textual format (x.x.x.x).
	*/
	QString			firstIPAddress();
	/*!
	 \brief Returns the last valid IP address of the IP range.

	 \fn lastIPAddress
	 \return Last valid IP address in textual format (x.x.x.x).
	*/
	QString			lastIPAddress();
	/*!
	 \brief Returns the first valid IP address of the IP range.

	 \fn firstIPAddressBin
	 \return First valid IP address in binary format (64bit).
	*/
	qint64			firstIPAddressBin();
	/*!
	 \brief Returns the last valid IP address of the IP range.

	 \fn lastIPAddressBin
	 \return Last valid IP address in binary format (64bit).
	*/
	qint64			lastIPAddressBin();
	/*!
	 \brief Returns the corresponding broadcast IP address.

	 \fn broadcastIPAddress
	 \return Broadcast IP address in textual format (x.x.x.x)
	*/
	QString			broadcastIPAddress();
	/*!
	 \brief Returns the corresponding broadcast IP address.

	 \fn broadcastIPAddressBIN
	 \return Broadcast IP address in binary format (64bit)
	*/
	qint64			broadcastIPAddressBIN();
	/*!
	 \brief Returns the corresponding netmask.

	 \fn netmask
	 \return Netmask in textual format (x.x.x.x)
	*/
	QString			netmask();
	/*!
	 \brief Returns the corresponding netmask.

	 \fn netmaskBin
	 \return Netmask in binary format (64bit).
	*/
	quint64			netmaskBin();
	/*!
	 \brief Returns the IP range in textual format (x.x.x.x/x)

	 \fn range
	 \return IP range in textual format (x.x.x.x/x)
	*/
	QString			range();

	/*!
	 \brief Sets the verification flag to TRUE or FALSE. This flag is used to display if this range has already been verified.

	 \fn setOK
	 \param bOK
	*/
	void			setOK(const bool &bOK);
	/*!
	 \brief Returns the verification flag.

	 \fn ok
	 \return TRUE or FALSE
	*/
	bool			ok();

	/*!
	 \brief Sets the name of the IP range.

	 \fn setName
	 \param szName Name of the IP range.
	*/
	void			setName(QString& szName);

	/*!
	 \brief Returns the base IP address of this IP range.

	 \fn IPAddress
	 \return Base IP address
	*/
	cIPAddress		IPAddress();
	/*!
	 \brief Returns the prefix of this IP range.

	 \fn prefix
	 \return Prefix of this IP range.
	*/
	qint16			prefix();

	/*!
	 \brief Returns the name of this IP range.

	 \fn name
	 \return Name of this IP range.
	*/
	QString			name();
	/*!
	 \brief Returns the old name of this IP range.

	 \fn oldName
	 \return Old name of this IP range.
	*/
	QString			oldName();

	/*!
	 \brief Sets the location of this IP range.

	 \fn setLocation
	 \param ID of the location of this IP range.
	*/
	void			setLocation(const qint32 iLocation);
	/*!
	 \brief Returns the location of this IP range.

	 \fn location
	 \return ID of the location of this IP range.
	*/
	qint32			location();

	/*!
	 \brief Verifies if the given IP address is within this IP range.

	 \fn ipInRange
	 \param szIPAddress IP address to be verified in textual format (x.x.x.x).
	 \return TRUE on success, FALSE otherwise.
	*/
	bool			ipInRange(const QString& szIPAddress);
	/*!
	 \brief Verifies if the given IP address is within this IP range.

	 \fn ipInRange
	 \param iIPAddress IP address to be verified in binary format (64bit).
	 \return TRUE on success, FALSE otherwise.
	*/
	bool			ipInRange(const qint64& iIPAddress);

	/*!
	 \brief Helper function for database export.

	 \fn subnetBIN
	 \return Precalculated subnet value in binary format (64bit).
	*/
	qint64			subnetBIN();
	/*!
	 \brief Helper function for database export.

	 \fn subnet1BIN
	 \return Precalculated subnet value in binary format (64bit).
	*/
	qint64			subnet1BIN();
	/*!
	 \brief Helper function for database export.

	 \fn subnet2BIN
	 \return Precalculated subnet value in binary format (64bit).
	*/
	qint64			subnet2BIN();
	/*!
	 \brief Helper function for database export.

	 \fn subnet3BIN
	 \return Precalculated subnet value in binary format (64bit).
	*/
	qint64			subnet3BIN();
private:
	cIPAddress		m_IPAddress;	/*!< This property holds the base IP address.<br><b>Access functions:</b><br><table><tr><td>cIPAddress*</td><td><b>IPAddress()</b></td></tr><tr><td>void</td><td><b>setIPRange</b>(const QString& szIPrange)</td></tr></table> */
	qint16			m_iPrefix;		/*!< This property holds the prefix of the IP range.<br><b>Access functions:</b><br><table><tr><td>qint16</td><td><b>prefix()</b></td></tr><tr><td>void</td><td><b>setIPRange</b>(const QString& szIPrange)</td></tr></table> */
	QString			m_szName;		/*!< This property holds the name of the IP range.<br><b>Access functions:</b><br><table><tr><td>QString</td><td><b>name()</b></td></tr><tr><td>void</td><td><b>setName</b>(const QString& szName)</td></tr></table> */
	QString			m_szOldName;	/*!< This property holds the old name of the IP range.<br><b>Access functions:</b><br><table><tr><td>QString</td><td><b>oldName()</b></td></tr><tr><td>void</td><td><b>setOldName</b>(const QString& szOldName)</td></tr></table> */
	qint32			m_iLocation;	/*!< This property holds the location of the IP range.<br><b>Access functions:</b><br><table><tr><td>qint32</td><td><b>location()</b></td></tr><tr><td>void</td><td><b>setLocation</b>(qint32 iLocation)</td></tr></table> */
	bool			m_bOK;			/*!< This property holds the verification state of the IP range.<br><b>Access functions:</b><br><table><tr><td>bool</td><td><b>ok()</b></td></tr><tr><td>void</td><td><b>setOk</b>(bool bOK)</td></tr></table> */
};

Q_DECLARE_METATYPE(cIPRange*)

/*!
 \brief The cIPRangeList class provides a list of IP ranges.

 \class cIPRangeList ciprange.h "ciprange.h"
*/
class cIPRangeList : public QList<cIPRange*>
{
public:
	/*!
	 \brief Adds a new entry to the IP range list.

	 If the IP range already exists, the existing IP range is returned, otherwise, the newly created IP range is returned.

	 \fn add
	 \param szIPRange IP range to be added.
	 \return Pointer to the newly or already existing IP range.
	*/
	cIPRange*		add(const QString& szIPRange);
	/*!
	 \brief Empties the IP range list.

	 \fn clean
	*/
	void			clean();
	/*!
	 \brief Sort the IP range list.

	 \fn sort
	*/
	void			sort();
	/*!
	 \brief Verifies all entries of the IP address list and set the "OK"-flag to TRUE or FALSE.

	 \fn verify
	*/
	void			verify();

	/*!
	 \brief Search for the given IP address within the list and returns the corresponding IP range.

	 \fn findRange
	 \param szIPAddress IP address to search for in textual format (x.x.x.x).
	 \return Returns the corresponding IP range or NULL if nothing is found.
	*/
	cIPRange*		findRange(const QString& szIPAddress);
	/*!
	 \brief Search for the given IP address within the list and returns the corresponding IP range.

	 \fn findRange
	 \param iIPAddress IP address to search for in binary format (64bit).
	 \return Returns the corresponding IP range or NULL if nothing is found.
	*/
	cIPRange*		findRange(const qint64& iIPAddress);

	/*!
	 \brief Returns the position of the given IP range within the list.

	 \fn position
	 \param lpIPRange IP range to be found.
	 \return Index of the position within the list.
	*/
	qint32			position(cIPRange* lpIPRange);
};

#endif // CIPRANGE_H
