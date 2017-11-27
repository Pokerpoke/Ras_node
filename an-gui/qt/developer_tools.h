#ifndef _DEVELOPER_TOOLS_H_
#define _DEVELOPER_TOOLS_H_

#include <QWidget>
#include <QColor>
#include <QString>
#include <QProcess>

#include <string>

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

    QString output_buffer;
    QString program;
    QProcess *cmd;
    QProcess *cmd1;
    QProcess *cmd2;

  private slots:
    void run();
    void voice_receive();
    void voice_send();
    void output_print();
};
}
}
}

#endif // !_DEVELOPER_TOOLS_H_