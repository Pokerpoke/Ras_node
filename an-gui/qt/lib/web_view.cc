#include "web_view.h"

#include "ui_web_view.h"

namespace an
{
namespace gui
{
namespace qt
{
WebView::WebView(QWidget *parent) : QWidget(parent),
									ui(new Ui::WebView)
{
	ui->setupUi(this);
}
WebView::~WebView()
{
	delete ui;
}
}
}
}