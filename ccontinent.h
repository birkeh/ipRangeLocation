#ifndef CCONTINENT_H
#define CCONTINENT_H


#include <QMetaType>
#include <QString>
#include <QList>


class cContinent
{
public:
	cContinent(const qint32& id);

	qint32			id();

	void			setName(const QString& name);
	QString			name();

private:
	qint32			m_id;
	QString			m_name;
};

Q_DECLARE_METATYPE(cContinent*)

class cContinentList : public QList<cContinent*>
{
public:
	cContinent*		add(const qint32& id);
	cContinent*		find(const qint32& id);
};

//Q_DECALRE_METATYPE(cContinentList*)

#endif // CCONTINENT_H
