/**
 * 
 * Copyright (c) 2017-2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-12
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2017-12-07
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "aero-node/logger.h"
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
    connect(ui->backward, SIGNAL(clicked()), this, SLOT(close()));
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
    cmd0->kill();
    cmd1->kill();
    cmd2->kill();
}

void DeveloperTools::voice_send()
{
    program = "/home/aero-node/voice-call -i 192.168.2.3 -p 8338 -l 13374";

    cmd1->start(program);

    ui->output->append(program);
}

void DeveloperTools::voice_receive()
{
    program = "/home/aero-node/voice-call -i 192.168.2.4 -p 13374 -l 8338";

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