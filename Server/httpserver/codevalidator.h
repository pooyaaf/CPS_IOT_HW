#ifndef CODEVALIDATOR_H
#define CODEVALIDATOR_H

#include <QObject>
#include <QString>
#include <QSet>

class codevalidator : public QObject
{
    Q_OBJECT
public:
    codevalidator();
    bool isValid(const QString& code);

signals:

private:
    QSet<QString> validCodes;
};

#endif // CODEVALIDATOR_H
