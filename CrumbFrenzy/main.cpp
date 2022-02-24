#include "crumbfrenzy.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CrumbFrenzy w;
    w.show();

    return a.exec();
}
