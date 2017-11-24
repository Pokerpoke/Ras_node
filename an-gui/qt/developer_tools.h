#ifndef _DEVELOPER_TOOLS_H_
#define _DEVELOPER_TOOLS_H_

#include <QWidget>

namespace Ui
{
class DeveloperTools;
}

namespace an
{
namespace gui
{
namespace qt
{
class DeveloperTools : public QWidget
{
    Q_OBJECT

  public:
    explicit DeveloperTools(QWidget *parent = 0);
    ~DeveloperTools();

  private:
    Ui::DeveloperTools *ui;
};
}
}
}

#endif // !_DEVELOPER_TOOLS_H_