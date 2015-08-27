# Alma OS 0.1

Alma OS is based on x64BareBones wich is a basic setup to develop operating systems for the Intel 64 bits architecture.

The final goal of x64BareBones's project is to provide an entry point for a kernel and the possibility to load extra binary modules separated from the main kernel.

Please read "Manual de Usuario.pdf" for the usage manual and "Informe.pdf" for more information about Alma OS.

## Environment setup: 
1) Install the following packages before building the Toolchain and Kernel:

`nasm qemu gcc make`

2) Build the Toolchain by executing the following commands on the x64BareBones project directory:

`cd Toolchain`

`make all`

3) Clean & Build the Toolchain. From the project's directory main run: 

`make all`

4) Run the kernel. From the project's directory main run:

`./run.sh`

or simply run (cleans, makes all, and runs):

`make run`

## Credits: 
- x64BareBones (base project): 
	- Author: Rodrigo Rearden (RowDaBoat) 
	- Collaborator: Augusto Nizzo McIntosh

- Alma OS (kernel modifications): 
	- Author: Matías Nicolás Comercio Vázquez 
	- Author: Juan Moreno
