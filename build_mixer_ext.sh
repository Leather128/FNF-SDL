#! /bin/bash
# Use is for people who don't already have SDL2_mixer_ext installed!
# (Run from a copy of the source of https://github.com/WohlSoft/SDL-Mixer-X btw)

# Prepare the build directory
mkdir build
cd build

# Configure the project
cmake -DCMAKE_BUILD_TYPE=Release -DDOWNLOAD_AUDIO_CODECS_DEPENDENCY=ON -DAUDIO_CODECS_BUILD_LOCAL_SDL2=ON ..

# Run the build
make -j 4 #where 4 - set number of CPU cores you have

# Install the built library and headers into the system
make install

# Copy lib files to right directory for proper installation (because apparently the program doesn't run otherwise)
sudo cp /usr/local/lib/libSDL2_mixer_ext.a /usr/lib/libSDL2_mixer_ext.a

sudo cp /usr/local/lib/libSDL2_mixer_ext.so /usr/lib/libSDL2_mixer_ext.so

sudo cp /usr/local/lib/libSDL2_mixer_ext.so.2 /usr/lib/libSDL2_mixer_ext.so.2
sudo cp /usr/local/lib/libSDL2_mixer_ext.so /usr/lib/libSDL2_mixer_ext.so