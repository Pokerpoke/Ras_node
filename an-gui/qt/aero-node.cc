/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-05-08
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include <QApplication>
#include <QWidget>
#include <QFile>

#include <unistd.h>
#include <errno.h>
#include <string>

#include "config.h"
#include "aeronode/logger.h"

#include "developer_tools.h"

using namespace std;
using namespace an::gui::qt;

int main(int argc, char *argv[])
{
    logger_init();

    QApplication app(argc, argv);

    string themes_dir;
#ifdef ENABLE_DEBUG
    themes_dir += "an-gui/qt/themes/light.qss";
#else
    themes_dir += "themes/light-tiny4412.qss";
#endif

    // Load an application style
    QFile styleFile(themes_dir.c_str());
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