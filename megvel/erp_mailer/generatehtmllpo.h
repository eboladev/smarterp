#ifndef GENERATEHTMLLPO_H
#define GENERATEHTMLLPO_H

#include <QObject>

class GenerateHtmlLpo : public QObject
{
	Q_OBJECT
public:
	explicit GenerateHtmlLpo(QObject *parent = 0);
	static QString getHtmlString(QString requisitionNo);
signals:

public slots:

};

#endif // GENERATEHTMLLPO_H
