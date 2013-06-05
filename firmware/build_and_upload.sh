#!/bin/sh
set -xe

# remove Arduino IDE build files
rm -rf src/irkit/build-uno/

~/src/ino/bin/ino build -m pro5v328
~/src/ino/bin/ino upload -m pro5v328