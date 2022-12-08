#!/bin/bash

sudo apt install -y git python3-pip libgtk2.0-dev libva-dev libvdpau-dev libx11-xcb-dev libfontenc-dev libxaw7-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxvmc-dev libxxf86vm-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-util-dev libxcb-util0-dev cmake

sudo pip install conan

git clone https://github.com/graySquirrel/pickleball-court-detection

cd pickleball-court-detection
mkdir build
cd build
conan install .. --build missing --build=openjpeg --build=libx264 --build=libx265

sed 's/_GLIBCXX_USE_CXX11_ABI 1/_GLIBCXX_USE_CXX11_ABI 0/' < /usr/include/x86_64-linux-gnu/c++/11/bits/c++config.h > tmp
sudo mv tmp /usr/include/x86_64-linux-gnu/c++/11/bits/c++config.h

cmake ..
cmake --build . -v

