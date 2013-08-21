#include <QtCore/QProcess>
#include <QEventLoop>
#include <QFile>
#include <QDebug>

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
  while (!file.atEnd()) {
    QString line = file.readLine();
    QStringList token = line.split(':');
    channelSet << token[0];
  }
  channels = channelSet.toList();
  channels.sort();
}

Process::Process(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

Process::~Process()
{
  kill();
}

const QString &Process::program() const
{
    return d->program;
}

void Process::setProgram(const QString &program)
{
    if (program == d->program) return;
    d->program = program;
    emit programChanged(d->program);
}

const QStringList &Process::arguments() const
{
    return d->arguments;
}

void Process::setArguments(const QStringList &arguments)
{
    if (arguments == d->arguments) return;
    d->arguments = arguments;
    emit argumentsChanged(d->arguments);
}

const QStringList &Process::channels() const
{
    return d->channels;
}

void Process::start()
{
    d->start(d->program, d->arguments);
}

void Process::terminate()
{
    d->terminate();
}

void Process::kill()
{
    if (d->started) {
      d->kill();
      d->wait();
    }
}

QByteArray Process::readAllStandardError()
{
    return d->readAllStandardError();
}

QByteArray Process::readAllStandardOutput()
{
    return d->readAllStandardOutput();
}

