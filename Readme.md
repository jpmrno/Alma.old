# ![Zhoue Logo](Docs/logo.png)

[![Build Status](https://travis-ci.com/jpmrno/Zhoue.svg?token=rrzVPFKtpAUUPF2Pp1UE&branch=master)](https://travis-ci.com/jpmrno/Zhoue)

Zhoue is based on x64BareBones which is a basic setup to develop operating systems for the Intel 64 bits architecture.

The final goal of x64BareBones's project is to provide an entry point for a kernel and the possibility to load extra binary modules separated from the main kernel.

Please read "Manual de Usuario.pdf" for the usage manual and "Informe.pdf" for more information about Zhoue.

This project was made for our Computer Architecture subject of the ITBA University (at Buenos Aires, Argentina).

## Requisites

This project needs the following packages: `nasm qemu gcc binutils make`.

### Linux

*Assuming you already have `gcc binutils make` installed...*

This will install `nasm` and `qemu` into your system.

From the project's directory, run:

	sudo apt-get update
	sudo apt-get install nasm
	sudo apt-get install qemu

Or simply run the installation script: `./Scripts/install-linux.sh`.

### OS X

*Assuming you already have `brew` (http://brew.sh) installed...*

This will install `nasm`, `qemu` and a `Cross Compiler` ([CrossCompiler](CrossCompiler/)/[gcc-4.8.1-OSX64.dmg](CrossCompiler/gcc-4.8.1-OSX64.dmg)) into your system.

From the project's directory, run:

	brew update
	brew install nasm
	brew install qemu
	hdiutil mount ./CrossCompiler/gcc-4.8.1-OSX64.dmg
	sudo installer -package /Volumes/gcc-4.8.1-for-linux64/gcc-4.8.1-for-linux64.pkg -target /
	sudo hdiutil detach /Volumes/gcc-4.8.1-for-linux64

Or simply run the installation script: `./Scripts/install-osx.sh`.

## Usage

From the project's directory, simply run:

	make run

If you want to just compile the project, run `make all`, then use this script to run: `./Scripts/run.sh` (not yet supported).

## Credits

- Zhoue β (project's structure & kernel modifications): 
	- Author: Juan Moreno

- Zhoue α (kernel implementation): 
	- Author: Matías Nicolás Comercio Vázquez 
	- Author: Juan Moreno

- x64BareBones (base project): 
	- Author: Rodrigo Rearden (RowDaBoat) 
	- Collaborator: Augusto Nizzo McIntosh
