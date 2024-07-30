Unix Shell Simulator and Task Switching Project

Overview

This project consists of two main components: a Unix shell simulator (mysh) and a task switching and process management system. The Unix shell simulator mimics the behavior of the Unix sh for command processing, demonstrating the use of fork, exec, wait, and pipe system calls. The task switching component demonstrates basic multitasking by implementing a simple task scheduler that switches between different processes performing arithmetic operations.
Files

    mysh.c: The Unix shell simulator.
    ts.s: Assembly file that handles low-level task switching and process management.
    t.c: C file that defines the processes and their behaviors.
    FDImage: Contains a disk image for the file descriptor.
    mtximage: MTX image file.
    mtxlib: Library for MTX.

Features
Part 1: Unix Shell Simulator (mysh)
Single Command with I/O Redirection

    Command Input: Accepts commands of the form:

    cmd arg1 arg2 arg3 .... argn

    where cmd is any valid Unix command or executable.

    Built-in Commands:
        cd [directory]: Changes the current working directory to directory. If directory is not provided, changes to the home directory.
        exit: Exits the shell.

    External Commands:
        Forks a child process to execute the command using execve().
        Waits for the child process to terminate and prints the exit status code.

    I/O Redirection:
        < infile: Redirects input from infile.
        > outfile: Redirects output to outfile.
        >> outfile: Appends output to outfile.

Commands with Pipes

    Single Pipe: Handles commands with a single pipe (|), dividing the command into head and tail.
        Example: cmd1 < infile | cmd2 > outfile

    Multiple Pipes: (Bonus) Handles commands with multiple pipes.
        Example: cat file | grep "test" | more

Script Files

    Script Execution: Executes shell script files that start with #!/usr/bin/bash.
        Reads the first 256 characters to check for #!.
        Executes the script using execve().

Part 2: Task Switching and Process Management
Assembly Code (ts.s)

    Initializes the operating system segment.
    Reads the boot block.
    Defines task switching routine _tswitch.
    Provides basic input (_getc) and output (_putc) functions.

C Code (t.c)

    Defines process structures and a simple process table.
    Implements arithmetic operations as separate processes.
    Demonstrates basic task scheduling and switching.

Usage
Compiling and Running the Unix Shell Simulator

Compile and run the mysh program:

sh

gcc mysh.c -o mysh
./mysh

Compiling and Running the Task Switching Program

Compile the assembly and C files and link them together:

sh

gcc -c t.c -o t.o
as ts.s -o ts.o
ld ts.o t.o -o mytask
./mytask

Unix Shell Commands

    To change the directory:

    sh

cd [directory]

To exit the shell:

sh

exit

To execute an external command:

sh

ls -l

To redirect input/output:

sh

command < inputfile > outputfile

To use pipes:

sh

    command1 | command2

Task Switching Processes

    Addition Process
        Prompts for two numbers and performs addition.
    Subtraction Process
        Prompts for two numbers and performs subtraction.
    Multiplication Process
        Prompts for two numbers and performs multiplication.
    Division Process
        Prompts for two numbers and performs division.

Scheduler

    The scheduler switches between the processes in a round-robin fashion.

Example Usage
Unix Shell Simulator

sh

mysh> ls -l
mysh> cd /home/user
mysh> echo "Hello, World!" > output.txt
mysh> cat output.txt | grep "Hello"
mysh> exit

Task Switching Program

sh

MTX starts in main()
Process (Addition) running
Enter two numbers to add: 3 4
Process (Addition):
7
Process (Subtraction) running
Enter two numbers to subtract (a - b): 5 2
Process (Subtraction):
3

License

This project is licensed under the GNU General Public License v3.0.
Contact

For any inquiries or questions, please contact Pholoho Hlaha or pholohohlaha@gmail.com.

This README file provides an overview of the combined Unix shell simulator and task switching projects, including how to compile, run, and use the programs, as well as details on their features and implementation.
