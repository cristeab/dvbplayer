#ifndef PROCESS_P_H_
#define PROCESS_P_H_

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QEventLoop>
#include "process.h"

class Process::Private : public QProcess
{
    Q_OBJECT
public:
    Private(Process *parent);
    void wait() {
      if (started) {
        finishedEvt.exec();
      }
    }

    QString program;
    QStringList arguments;
    QStringList channels;
    bool started;
private slots:
  void onStarted() {
    qDebug() << "started";
    started = true;
  }
  void onFinished() {
    qDebug() << "finished";
    started = false;
    if (finishedEvt.isRunning()) {
      finishedEvt.quit();
    }
  }
private:
  void loadChannels();
  Process *q;
  QEventLoop finishedEvt;
};

#endif
