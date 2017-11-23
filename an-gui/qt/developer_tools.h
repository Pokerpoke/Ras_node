#ifndef _DEVELOPER_TOOLS_H_
#define _DEVELOPER_TOOLS_H_

#include <QMainWindow>
#include <QWidget>

namespace Ui
{
class DeveloperTools;
}

class DeveloperTools : public QMainWindow
{
    Q_OBJECT

  public:
    explicit DeveloperTools(QMainWindow *parent = 0);
    ~DeveloperTools();
  private:
    Ui::DeveloperTools *ui;
};

#endif // !_DEVELOPER_TOOLS_H_