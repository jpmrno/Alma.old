x64BareBones is a basic setup to develop operating systems for the Intel 64 bits architecture.

The final goal of the project is to provide an entry point for a kernel and the possibility to load extra binary modules separated from the main kernel.

Please read "Manual de Usuario.pdf" for the usage manual and "Informe.pdf" for more information about this project.

Environment setup:
1- Install the following packages before building the Toolchain and Kernel:

nasm qemu gcc make

2- Build the Toolchain

Execute the following commands on the x64BareBones project directory:

  user@linux:$ cd Toolchain
  user@linux:$ make all

3- Clean & Build the Toolchain

From the x64BareBones project directory run:
  user@linux:$ make clean
  user@linux:$ make all

4- Run the kernel

From the x64BareBones project directory run:

  user@linux:$ ./run.sh
  
  or simply run (cleans, makes all, and runs):
  user@linux:$ make run

..CREDITS..
  Base project:
    Author: Rodrigo Rearden (RowDaBoat)
    Collaborator: Augusto Nizzo McIntosh
  
  Modifications:
    Author: Matías Nicolás Comercio Vázquez
    Author: Juan Moreno