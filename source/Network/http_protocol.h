#ifndef JELYAZKA_HTTP_PROTOCOL_H
#define JELYAZKA_HTTP_PROTOCOL_H

#include <QString>

class IHttpProtocol
{
public:
    IHttpProtocol () = default;
    virtual ~IHttpProtocol () = default;
    virtual void getRequest (const QString &url) = 0;
    virtual void postRequest (const QString &url) = 0;
};

#endif // JELYAZKA_HTTP_PROTOCOL_H
