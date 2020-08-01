
Debian
====================
This directory contains files used to package koinmudrad/koinmudra-qt
for Debian-based Linux systems. If you compile koinmudrad/koinmudra-qt yourself, there are some useful files here.

## koinmudra: URI support ##


koinmudra-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install koinmudra-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your koinmudraqt binary to `/usr/bin`
and the `../../share/pixmaps/koinmudra128.png` to `/usr/share/pixmaps`

koinmudra-qt.protocol (KDE)

