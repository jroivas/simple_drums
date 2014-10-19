#include <QtGui>
#include <QtWidgets>
//#include <unistd.h>
#include "drums.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

#if 0
    Sound snd;

    snd.play(0);
    usleep(100000);
    snd.play(1);
    usleep(100000);
    snd.play(2);
    usleep(1000);
    snd.play(4);
    usleep(10000000);
    snd.play(4);
    usleep(10000000);
#endif

    Drums dr;
    dr.resize(800, 600);
    dr.show();
    return app.exec();
}
