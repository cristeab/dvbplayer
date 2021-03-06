#ifndef PROCESS_P_H_
#define PROCESS_P_H_

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QEventLoop>
#include "dvbplayer.h"

class DVBPlayer::Private : public QProcess
{
    Q_OBJECT
public:
  Private(DVBPlayer *parent);
  void wait() {
    if (started) {
      finishedEvt.exec();
    }
  }
  bool programExists();

  QString program;
  QStringList arguments;
  QStringList channels;
  QString errorMsg;
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
  DVBPlayer *q;
  QEventLoop finishedEvt;
};

#endif
