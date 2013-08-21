#include <QtCore/QProcess>
#include <QEventLoop>
#include <QFile>
#include <QDebug>

#include "process.h"
#include "process_p.h"


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

