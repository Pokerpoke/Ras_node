#include <QApplication>
#include <QWidget>

#include "developer_tools.h"

using namespace an::gui::qt;

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    DeveloperTools ui;
    ui.show();

    return app.exec();
}