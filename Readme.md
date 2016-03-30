# ![λlma](http://imgh.us/alma_2.svg)
[![λlma's build status](https://travis-ci.com/jpmrno/Alma.svg?token=rrzVPFKtpAUUPF2Pp1UE&branch=master)](https://travis-ci.com/jpmrno/Alma)

λlma is based on x64BareBones which is a basic setup to develop operating systems for the Intel 64 bits architecture.

The final goal of x64BareBones's project is to provide an entry point for a kernel and the possibility to load extra binary modules separated from the main kernel.

Please read "Manual de Usuario.pdf" for the usage manual and "Informe.pdf" for more information about λlma.

This project was made for our Computer Architecture subject at ITBA University (Buenos Aires, Argentina).

## Requisites

This project needs the following packages: `nasm gcc binutils make qemu`.

### Linux

This will install `make`, `build-essential`, `nasm` and `qemu` into your system.

From the project's directory, run:

	sudo apt-get update
	sudo apt-get install make build-essential nasm qemu

Or simply run the installation script: `./Scripts/install-linux.sh`.

### OS X

*Assuming you already have [homebrew](http://brew.sh) installed...*

This will install `nasm`, `qemu` and a `cross compiler` ([CrossGCC](http://crossgcc.rts-software.org/doku.php?id=compiling_for_linux#bit_linux_binaries_for_mac_intel1)) into your system.

From the project's directory, run:

	brew update
	brew install nasm
	brew install qemu
	curl -o gcc-4.8.1-OSX64.dmg http://crossgcc.rts-software.org/download/gcc-4.8.1-for-linux32-linux64/gcc-4.8.1-for-linux64.dmg
	hdiutil mount gcc-4.8.1-OSX64.dmg
	sudo installer -package /Volumes/gcc-4.8.1-for-linux64/gcc-4.8.1-for-linux64.pkg -target /
	hdiutil detach /Volumes/gcc-4.8.1-for-linux64
	rm -f gcc-4.8.1-OSX64.dmg

Or simply run the installation script: `./Scripts/install-osx.sh`.

## Usage

From the project's directory, simply run:

	make all

If you want to just build the project, run `make build` then use `make run` to run.

## Credits

- λlma β (project's structure & kernel modifications): 
	- Author: Juan Moreno

- λlma α (kernel implementation): 
	- Author: [Matías Comercio](https://github.com/MatiasComercioITBA)
	- Author: Juan Moreno

- [x64BareBones](https://bitbucket.org/RowDaBoat/x64barebones/) (base project): 
	- Author: Rodrigo Rearden
	- Collaborator: Augusto Nizzo McIntosh
