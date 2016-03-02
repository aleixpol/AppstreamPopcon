#ifndef AppStreamPopcon_H
#define AppStreamPopcon_H

#include <QtCore/QObject>
#include <AppstreamQt/database.h>

class QNetworkReply;
class AppStreamPopcon : public QObject
{
    Q_OBJECT

public:
    AppStreamPopcon(const QUrl& url);
    virtual ~AppStreamPopcon();

    void popconDownloaded();

private:
    Appstream::Database db;
};

#endif // AppStreamPopcon_H
