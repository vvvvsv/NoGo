#include "mainsense.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    //创建文件夹
    QDir dir;
    if(!dir.exists("NogoSaveData"))
        dir.mkdir("NogoSaveData");

    //创建Achievement.log，写入初始数据
    //先检查是不是空的
    QFile achFile("NogoSaveData/Achievement.log");
    if(!achFile.exists())
    {
        achFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        QTextStream achOutput(&achFile);
        quint32 data0(0);
        for(int i=1;i<=3;i++)
        {
            for(int j=1;j<=3;j++)
                achOutput<<data0<<" ";
            achOutput<<endl;
        }
        achFile.close();
    }

    //创建SaveBoard0-9.log，写入初始数据
    //一会再写

    QApplication a(argc, argv);
    MainSense w;
    w.show();

    return a.exec();
}
