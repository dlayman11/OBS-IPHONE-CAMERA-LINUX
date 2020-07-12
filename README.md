<div align = "center">
<img src=".github/obs-logo.svg" width="128" height="128" />
</div>


obs-ios-camera-source Linux branch
==============
This is a fork of [obs-ios-camera-source](https://github.com/wtsnz/obs-ios-camera-source) that supports Linux.

To use this you use the [accompanying iOS app](https://will.townsend.io/products/obs-iphone/) to begin streaming in OBS.

## Downloads

Linux binaries are not provided; instead, compilation and manual installation instructions for Ubuntu 18.04 are supplied below.

## Building

These instructions are tested on Ubuntu 18.04. For other distros/versions, YMMV.

- Install OBS Studio using the [instructions on the OBS wiki](https://obsproject.com/wiki/install-instructions#ubuntu-installation).
- Install prerequisites: `sudo apt install build-essential git cmake libavcodec-dev`
- Download the OBS Studio source code somewhere: 
  - `cd ~/Downloads`
  - `git clone https://github.com/obsproject/obs-studio.git`
- Download this plugin source code:
  - `git clone https://github.com/dougg3/obs-ios-camera-source.git`
- Build the plugin:
  - `cd obs-ios-camera-source`
  - `mkdir build`
  - `cd build`
  - `cmake .. -DLIBOBS_INCLUDE_DIR=~/Downloads/obs-studio/cmake`
  - `make -j$(nproc)`
- Manually install the plugin by copying relevant files into your OBS plugins directory (assuming 64-bit Linux):
  - `mkdir -p ~/.config/obs-studio/plugins/obs-ios-camera-source/data/locale`
  - `mkdir -p ~/.config/obs-studio/plugins/obs-ios-camera-source/bin/64bit`
  - `cp ../data/locale/en-US.ini ~/.config/obs-studio/plugins/obs-ios-camera-source/data/locale/`
  - `cp obs-ios-camera-source.so ~/.config/obs-studio/plugins/obs-ios-camera-source/bin/64bit/`

## Special thanks
- [wtsnz](https://github.com/wtsnz) for creating an awesome plugin/app for using your iOS camera in OBS!
