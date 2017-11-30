#include <QApplication>
#include <QWidget>

#include "config.h"

#include "web_view.h"

using namespace an::gui::qt;

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

	WebView index;
#ifdef AN_TINY4412
	index.showFullScreen();
#else
	index.show();
#endif

	return app.exec();
}