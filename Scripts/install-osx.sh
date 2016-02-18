#!/bin/bash
set -ev
brew update
brew install nasm
brew install qemu
hdiutil mount ./CrossCompiler/gcc-4.8.1-OSX64.dmg
sudo installer -package /Volumes/gcc-4.8.1-for-linux64/gcc-4.8.1-for-linux64.pkg -target /
hdiutil detach /Volumes/gcc-4.8.1-for-linux64
