#include <QApplication>
#include <QPushButton>
#include "Presentation/GUI.h"
#include "appCoord.h"


int main(int argc, char *argv[]) {
    QApplication mainFunction(argc, argv);

    appCoord coord;
    coord.show();

    return QApplication::exec();
}
