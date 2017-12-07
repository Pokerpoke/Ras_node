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
#ifndef _DEVELOPER_TOOLS_H_
#define _DEVELOPER_TOOLS_H_

#include <QWidget>
#include <QColor>
#include <QString>
#include <QProcess>

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
  QProcess *cmd0;
  QProcess *cmd1;
  QProcess *cmd2;

private slots:
  void run();
  void stop();
  void stop_all();
  void clear_output();
  void voice_receive();
  void voice_send();
};
}
}
}

#endif // !_DEVELOPER_TOOLS_H_