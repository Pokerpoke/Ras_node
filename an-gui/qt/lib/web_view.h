#ifndef _WEB_VIEW_H_
#define _WEB_VIEW_H_

#include <QWidget>
#include <QWebView>

namespace Ui
{
class WebView;
}

namespace an
{
namespace gui
{
namespace qt
{
class WebView : public QWidget
{
	Q_OBJECT
public:
		WebView(QWidget *parent=0);
		~WebView();
private:
	Ui::WebView *ui;
};
}
}
}

#endif // !_WEB_VIEW_H_
