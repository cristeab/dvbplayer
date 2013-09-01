#include "dvbplayer_plugin.h"
#include "dvbplayer.h"

#include <QtDeclarative/qdeclarative.h>

QML_DECLARE_TYPE(DVBPlayer)

void DVBPlayerPlugin::registerTypes(const char *uri)
{
    // @uri DVBPlayer
    qmlRegisterType<DVBPlayer>(uri, 0, 1, "DVBPlayer");
}

Q_EXPORT_PLUGIN2(DVBPlayer, DVBPlayerPlugin)

