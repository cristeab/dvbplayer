#include <QEventLoop>
#include <QFile>
#include <QDebug>

#include "dvbplayer.h"
#include "dvbplayer_p.h"


DVBPlayer::DVBPlayer(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

DVBPlayer::~DVBPlayer()
{
  kill();
}

const QString &DVBPlayer::program() const
{
    return d->program;
}

void DVBPlayer::setProgram(const QString &program)
{
    if (program == d->program) return;
    d->program = program;
    emit programChanged(d->program);
}

const QStringList &DVBPlayer::arguments() const
{
    return d->arguments;
}

void DVBPlayer::setArguments(const QStringList &arguments)
{
    if (arguments == d->arguments) return;
    d->arguments = arguments;
    emit argumentsChanged(d->arguments);
}

const QStringList &DVBPlayer::channels() const
{
    return d->channels;
}

const QString &DVBPlayer::errorMsg() const
{
    return d->errorMsg;
}

void DVBPlayer::start()
{
    d->start(d->program, d->arguments);
}

void DVBPlayer::terminate()
{
    d->terminate();
}

void DVBPlayer::kill()
{
    if (d->started) {
      d->kill();
      d->wait();
    }
}

QByteArray DVBPlayer::readAllStandardError()
{
    return d->readAllStandardError();
}

QByteArray DVBPlayer::readAllStandardOutput()
{
    return d->readAllStandardOutput();
}

bool DVBPlayer::programExists()
{
  return d->programExists();
}

