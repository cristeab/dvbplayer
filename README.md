      DVB-T/DAB-T player


  Description

This KDE plasmoid uses mplayer in order to play digital content from a dvb tunner device. The channels
are read from /etc/mplayer/channels.conf file that must be generated using dvb-t_scanner utility
(https://github.com/cristeab/dvb-t_scanner). Double click a channel name on the list to start playing
, double click again to stop playing the current channel.


  Plugin Compilation and Installation

A QML plugin (shared library) is needed in order to start mplayer process and read the channel configuration
file. From the main directory of the project:
 cd plugins
 mkdir build
 cd build
 cmake ..
 make
 sudo make install


  Plasmoid Package Creation and Installation

From the main directory of the project:
 cd plasmoid
 zip -r ../dvbplayer.plasmoid .
 plasmapkg -i dvbplayer.plasmoid
