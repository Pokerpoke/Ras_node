#include <QApplication>
#include <QWidget>

#include "ui_developer_tools.h"

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    QMainWindow window;
    Ui::developer_tools ui;
    ui.setupUi(&window);
    window.show();

    return app.exec();
}