#ifndef EWS_H
#define EWS_H

#include <QString>

class Ews
{
public:
    Ews(const QString& server, const QString& domain, const QString& login, const QString& password);
    ~Ews();
};

#endif // EWS_H
