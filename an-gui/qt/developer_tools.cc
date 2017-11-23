#include "developer_tools.h"

#include "ui_developer_tools.h"

DeveloperTools::DeveloperTools(QMainWindow *parent):
    QMainWindow(parent),
    ui(new Ui::DeveloperTools)
{
    ui->setupUi(this);
}

DeveloperTools::~DeveloperTools()
{
    delete ui;
}