#include <QFile>
#include <QSet>
#include <QTextCodec>
#include "process_p.h"

Process::Private::Private(Process *parent)
    : QProcess(parent)
    , started(false)
    , q(parent)
{
    connect(this, SIGNAL(started()), q, SIGNAL(started()));
    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
    connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), q, SIGNAL(finished(int)));
    connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished()));
    connect(this, SIGNAL(readyReadStandardOutput()), q, SIGNAL(readyReadStandardOutput()));
    connect(this, SIGNAL(readyReadStandardError()), q, SIGNAL(readyReadStandardError()));
    loadChannels();
}

void Process::Private::loadChannels()
{
  QFile file("/etc/mplayer/channels.conf");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Cannot open file";
    return;
  }
  QSet<QString> channelSet;
  QTextCodec *codec = QTextCodec::codecForLocale();
  if (NULL == codec) {
    qDebug() << "Cannot get locale codec";
    return;
  }
  while (!file.atEnd()) {
    QByteArray line = file.readLine();
    QString conv_line = codec->toUnicode(line);
    QStringList token = conv_line.split(':');
    channelSet << token[0];
  }
  channels = channelSet.toList();
  channels.sort();
}
