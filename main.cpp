#include <QCoreApplication>
#include "AppStreamPopcon.h"
#include <QCommandLineParser>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QUrl url;
    {
        QCommandLineParser parser;
        parser.addPositionalArgument("url", "popcon url");
        parser.addHelpOption();
        parser.addVersionOption();
        parser.process(app);
        if (parser.positionalArguments().count()!=1)
            parser.showHelp(1);

        url = QUrl::fromUserInput(parser.positionalArguments().first());
    }

    AppStreamPopcon p(url);

    return app.exec();
}
