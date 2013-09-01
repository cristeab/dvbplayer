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
  channels.clear();//an empty list is used to signal an error
  QFile file("/etc/mplayer/channels.conf");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    errorMsg = tr("Cannot open configuration file (")+file.fileName()+")";
    return;
  }
  QSet<QString> channelSet;
  QTextCodec *codec = QTextCodec::codecForLocale();
  if (NULL == codec) {
    errorMsg = tr("Cannot get locale codec");
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
  if (channels.isEmpty()) {
    errorMsg = tr("No channel found (configuration file might not have the expected format)");
  } else {
    errorMsg = "";//successful operation
  }
}

bool Process::Private::programExists() {
  QProcess proc;
  QStringList args;
  args << "-v";
  proc.start(program, args);
  proc.waitForFinished();
  QString out = proc.readAllStandardOutput();
  bool ok = true;
  if (!out.contains(QRegExp("\\S+:\\s+mplayer"))) { //look for 'Usage:   mplayer'
    ok = false;
    errorMsg = tr("Cannot find ")+program;
  } else {
    errorMsg = "";
  }
  return ok;
}

