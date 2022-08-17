#pragma execution_character_set("utf-8")
#include "ColorWidget.h"

#include <QApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QFileInfo>
#include <QMessageBox>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //连接LocalServer
    QString serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    QLocalSocket socket;
    socket.connectToServer(serverName);
    if(socket.waitForConnected(1000)){
        ColorWidget::Instance()->show();
    }

    // 如果连接成功，说明已经存在指定的LocalServer，说明已经有应用启动了，此时直接退出应用即可
    // 如果没有指定的LocalServer存在，则connectToServer会返回错误信息，此时创建LocalServer
    else
    {
        //创建LocalServer
        QLocalServer server;
        if (server.listen(serverName)) {
            // 此时监听失败，可能是程序崩溃时,残留进程服务导致的,移除之
            if(server.serverError()== QAbstractSocket::AddressInUseError){
                QLocalServer::removeServer(serverName);
                server.listen(serverName);
            }
        }
        ColorWidget::Instance()->show();
    }

    std::vector<std::pair<std::string, int>> v;
    v.push_back({"yxj",24});
    return a.exec();
}
