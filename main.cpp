#include <QString>
#include <QStringList>
#include <QFile>
#include <QSet>
#include <QDebug>

int main(int argc, const char *argv[])
{
  QFile file("/etc/mplayer/channels.conf");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Cannot open file";
    return EXIT_FAILURE;
  }

  QSet<QString> channel;
  while (!file.atEnd()) {
    QString line = file.readLine();
    QStringList token = line.split(':');
    channel << token[0];
  }
  QList<QString> list = channel.toList();
  qSort(list);
  qDebug() << "Found " << list.size() << "channels";
  foreach(QString c, list) {
    qDebug() << c;
  }
  return EXIT_SUCCESS;
}
