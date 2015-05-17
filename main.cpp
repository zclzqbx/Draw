#include "drawdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawDlg w;
    w.show();

    return a.exec();
}
