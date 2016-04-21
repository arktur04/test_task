#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create an instance of a server and then start it.
    MyServer server;
    server.startServer();

    return a.exec();
}
