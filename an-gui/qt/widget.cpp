#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textBrowser->hide();
    connect(ui->pushButton,SIGNAL(clicked()),ui->textBrowser,SLOT(show()));
}

Widget::~Widget()
{
    delete ui;
}
