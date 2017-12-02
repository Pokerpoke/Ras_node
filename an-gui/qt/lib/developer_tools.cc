#include "logger.h"
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
    cmd0 = new QProcess(this);
    cmd1 = new QProcess(this);
    cmd2 = new QProcess(this);

    ui->output->append("Command Line Output:");

    connect(ui->run, SIGNAL(clicked()), this, SLOT(run()));
    connect(ui->stop, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->clear_output, SIGNAL(clicked()), this, SLOT(clear_output()));
    // connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->quit, SIGNAL(clicked()), this, SLOT(stop_all()));
    connect(ui->voice_send, SIGNAL(clicked()), this, SLOT(voice_send()));
    connect(ui->voice_receive, SIGNAL(clicked()), this, SLOT(voice_receive()));
}

void DeveloperTools::run()
{
    program = "/home/jiang/git/aero-node/build/bin/voice-receive";

    cmd0->start(program);
    
    program += " starting...";
    ui->output->append(program);
}

void DeveloperTools::stop()
{
    program = "/home/jiang/git/aero-node/build/bin/voice-receive";

    cmd0->kill();

    program += " stopped";
    ui->output->append(program);
}

void DeveloperTools::stop_all()
{
    if (cmd0->state() == QProcess::Running)
    {
        cmd0->kill();
    }
    if (cmd1->state() == QProcess::Running)
    {
        cmd1->kill();
    }
    if (cmd2->state() == QProcess::Running)
    {
        cmd2->kill();
    }
}

void DeveloperTools::voice_send()
{
    program = "/home/aero-node/voice-send 192.168.2.1";

    cmd1->start(program);

    ui->output->append(program);
}

void DeveloperTools::voice_receive()
{
    program = "/home/aero-node/voice-receive";

    cmd2->start(program);

    ui->output->append(program);
}

void DeveloperTools::clear_output()
{
    ui->output->clear();
    ui->output->append("Command Line Output:");
}

DeveloperTools::~DeveloperTools()
{
    if (cmd0->state() == QProcess::Running)
    {
        cmd0->kill();
    }
    if (cmd1->state() == QProcess::Running)
    {
        cmd1->kill();
    }
    if (cmd2->state() == QProcess::Running)
    {
        cmd2->kill();
    }
    delete ui;
    delete cmd0;
    delete cmd1;
    delete cmd2;
}
}
}
}