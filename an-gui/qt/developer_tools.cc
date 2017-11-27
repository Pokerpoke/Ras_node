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
    program = "";
    cmd = new QProcess(this);
    cmd1 = new QProcess(this);
    cmd2 = new QProcess(this);

    QColor white(255, 255, 255);
    ui->output->setTextColor(white);

    connect(ui->run, SIGNAL(clicked()), this, SLOT(output_print()));
    connect(ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(ui->voice_send, SIGNAL(clicked()), this, SLOT(voice_send()));
    connect(ui->voice_receive, SIGNAL(clicked()), this, SLOT(voice_receive()));

}

void DeveloperTools::run()
{
    program = "/home/jiang/git/aero-node/build/bin/voice-receive";

    cmd->start(program);
    QColor white(255, 255, 255);

    ui->output->setTextColor(white);
}

void DeveloperTools::voice_send()
{
    program = "/home/aero-node/voice-send 192.168.2.1";

    cmd1->start(program);

    ui->output->append("voice-send");
}

void DeveloperTools::voice_receive()
{
    program = "/home/aero-node/voice-receive";

    cmd2->start(program);

    ui->output->append("voice-receive");
}

void DeveloperTools::output_print()
{
    QColor white(255, 255, 255);

    ui->output->setTextColor(white);
}

DeveloperTools::~DeveloperTools()
{
    delete ui;
    delete cmd;
    delete cmd1;
    delete cmd2;
}
}
}
}