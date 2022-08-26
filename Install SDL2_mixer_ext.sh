#! /bin/bash

cd /tmp # go into tmp

git clone https://github.com/WohlSoft/SDL-Mixer-X.git mixer_ext # clone into a mixer_ext folder

cd mixer_ext # cd into the folder

mkdir build # make build folder

cd build # cd into the folder

cmake -DCMAKE_BUILD_TYPE=Release -DDOWNLOAD_AUDIO_CODECS_DEPENDENCY=ON -DAUDIO_CODECS_BUILD_LOCAL_SDL2=ON .. # Configure the project

make -j 4 # Run the build (where 4 - set number of CPU cores you have)

sudo make install # Install the built library and headers into the system with sudo

cd /tmp # go back to tmp

sudo rm -rf /tmp/mixer_ext # remove all files relating to it

# copy the library files to /usr/lib because they start in /usr/local/lib (not detected by the game :skull:)
sudo cp /usr/local/lib/libSDL2_mixer_ext.a /usr/lib/libSDL2_mixer_ext.a
sudo cp /usr/local/lib/libSDL2_mixer_ext.so /usr/lib/libSDL2_mixer_ext.so
sudo cp /usr/local/lib/libSDL2_mixer_ext.so.2 /usr/lib/libSDL2_mixer_ext.so.2
sudo cp /usr/local/lib/libSDL2_mixer_ext.so.2.6.0.0 /usr/lib/libSDL2_mixer_ext.so.2.6.0.0