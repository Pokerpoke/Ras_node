#include <QApplication>
#include <QWidget>

#include "developer_tools.h"

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    // QMainWindow window;
    DeveloperTools ui;
    // ui.setupUi(&window);
    ui.show();

    return app.exec();
}