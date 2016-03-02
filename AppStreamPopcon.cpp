#include "AppStreamPopcon.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCoreApplication>
#include <KCompressionDevice>

AppStreamPopcon::AppStreamPopcon(const QUrl& url)
{
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &AppStreamPopcon::popconDownloaded);

    bool b = db.open();
    Q_ASSERT(b);
}

AppStreamPopcon::~AppStreamPopcon()
{}

void AppStreamPopcon::popconDownloaded()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QScopedPointer<KCompressionDevice> dev(new KCompressionDevice(reply, false, KCompressionDevice::GZip));
    if (!dev->open(QIODevice::ReadOnly)) {
        qWarning() << "couldn't open the popcon file";
        QCoreApplication::exit(1);
        return;
    }

    QTextStream cout(stdout);
    QTextStream stream(dev.data());
    while(!stream.atEnd()) {
        const QString line = stream.readLine();
        if(!line.startsWith(QLatin1String("Package:"))) {
            cout << line << '\n';
            continue;
        }
        const QVector<QStringRef> lineContent = line.splitRef(QLatin1Char(' '));

        const QString pkgName = lineContent[1].toString();
        const QList<Appstream::Component> components = db.findComponentsByPackageName(pkgName);
        if (components.isEmpty())
            continue;

        foreach(const Appstream::Component &comp, components) {
            Q_ASSERT(comp.isValid());
            Q_ASSERT(!comp.name().isEmpty());

            cout << QString(line).replace(pkgName, comp.id()) << '\n';
        }
    }

    QCoreApplication::exit(0);
}

