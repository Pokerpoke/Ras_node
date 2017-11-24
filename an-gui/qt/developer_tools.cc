#include "developer_tools.h"

#include "ui_developer_tools.h"

namespace an
{
namespace gui
{
namespace qt
{
DeveloperTools::DeveloperTools(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::DeveloperTools)
{
    ui->setupUi(this);
}

DeveloperTools::~DeveloperTools()
{
    delete ui;
}
}
}
}