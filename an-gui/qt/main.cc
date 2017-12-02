#include <QApplication>
#include <QWidget>
#include <QFile>

#include "config.h"
#include "logger.h"

#include "developer_tools.h"

using namespace an::gui::qt;

int main(int argc, char *argv[])
{
    logger_init();

    QApplication app(argc, argv);

    // Load an application style
#ifdef ENABLE_DEBUG
    QFile styleFile("an-gui/qt/themes/light.qss");
#else
    QFile styleFile("themes/light-tiny4412.qss");
#endif
    if (!styleFile.open(QFile::ReadOnly))
    {
        LOG(ERROR) << "Open style sheet file failed.";
    }

    // Apply the loaded stylesheet
    QString style(styleFile.readAll());
    app.setStyleSheet(style);

    DeveloperTools ui;
#ifdef AN_TARGET_TINY4412
    ui.showFullScreen();
#else
    ui.show();
#endif

    return app.exec();
}