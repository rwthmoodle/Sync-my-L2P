#!/bin/bash
cd linux
wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
wget http://security.ubuntu.com/ubuntu/pool/main/i/icu/libicu52_52.1-3ubuntu0.8_amd64.deb
dpkg -i libicu52_52.1-3ubuntu0.8_amd64.deb
dos2unix Sync-my-Moodle.desktop
chmod a+x ./linuxdeployqt-continuous-x86_64.AppImage
./linuxdeployqt-continuous-x86_64.AppImage --appimage-extract
export PATH=/work/linux/squashfs-root/usr/bin/:$PATH
mkdir -p usr/bin
cp ../bin/Sync-my-Moodle ./usr/bin/Sync-my-Moodle
squashfs-root/AppRun ./usr/bin/Sync-my-Moodle -verbose=1 -appimage

