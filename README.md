<p align="center">
  <img src="http://syncmyl2p.de/images/light-logo.png"/>
</p>

Sync-my-Moodle (formerly Sync-my-L2P) is a program created by students of the RWTH Aachen University for the comfortable download of all available files in RWTH Moodle. It allows you to easily mirror all files from the learning rooms to your hard disk, so that they are available without internet.

After more than 9 years Robert Krajewski, the original maintainer resigned and we, a team at the RWTH IT Center took over maintenance for this project.

# Download and Installation

You can download Sync-my-Moodle either from the [official Website](https://app.rwth-aachen.de/syncmymoodle) or [here](https://github.com/rwthmoodle/Sync-my-Moodle/releases/tag/latest) for Windows, Linux and macOS. While on Windows an installer is provided, on macOS a .dmg or homebrew package, and on Linux an AppImage is distributed.

**Please note that as of yet, QT6 and thus Arm-based devices are not supported.**

## Installation on Windows
Just use the provided installer. 

## Installation on Linux Distributions (tested on Ubuntu 18.04)
Make the AppImage executable and open it with a double click.

## Installation on OSX (.dmg)
Open the .dmg and drag&drop Sync-my-Moodle to your apps.

## Installation on OSX (Cask)
Users with home-brew installed can now install Sync-my-Moodle with the following commands:
`brew tap caskroom/cask` followed by `brew cask install sync-my-l2p`. Updating the program will work with the command `brew update` to update the program formula, followed by `brew upgrade` to upgrade the program itself.

# Compile
For compilation we recommend C++11, Qt (5.15 or higher) and OpenSSL 1.1.1.
The easiest way is to load the .pro file into Qt Creator and compile Sync-my-Moodle there. From the console you can also run qmake (with appropriate arguments) instead and then the preferred C++ compiler.

Note: A ClientID is required for the program to connect to the API of RWTH Moodle. The RWTH does not allow the publication of such a client ID. However, an individual ClientID can easily be requested.

# Distribute
For distributing Sync-my-Moodle on Linux, two options are available:
1. Create an AppImage using the `run.sh` script provided in the `linux` subdirectory.
2. Create an deb package: https://github.com/justin-time/Sync-my-L2P-Linux

# Crashes? Feedback? Questions?
https://github.com/rwthmoodle/Sync-my-Moodle/issues
