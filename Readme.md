# ![Zhoue Logo](/Docs/logo.png)

Zhoue is based on x64BareBones which is a basic setup to develop operating systems for the Intel 64 bits architecture.

The final goal of x64BareBones's project is to provide an entry point for a kernel and the possibility to load extra binary modules separated from the main kernel.

Please read "Manual de Usuario.pdf" for the usage manual and "Informe.pdf" for more information about Zhoue.

This project was made for our Computer Architecture subject of the ITBA University (at Buenos Aires, Argentina).

## Requisites

### Linux

This project needs the following packages: `nasm qemu gcc binutils make`

### Mac OS

0) *Requisite:* Install BREW (http://brew.sh)

	ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

1) Install QEMU

	brew install qemu

2) Install NASM

	brew install nasm

3) *Optional:* Install the newest version of MAKE

	brew install make

## Usage

From the project's directory run:

	make run

## Credits

- Zhoue β (project's structure & kernel modifications): 
	- Author: Juan Moreno

- Zhoue α (kernel implementation): 
	- Author: Matías Nicolás Comercio Vázquez 
	- Author: Juan Moreno

- x64BareBones (base project): 
	- Author: Rodrigo Rearden (RowDaBoat) 
	- Collaborator: Augusto Nizzo McIntosh
