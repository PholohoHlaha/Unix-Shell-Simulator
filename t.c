/********************************************************************
Copyright 2010-2015 K.C. Wang, <kwang@eecs.wsu.edu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/
#define NPROC 4                // number of PROCs
#define SSIZE 1024             // per proc stack area
//#define RED

typedef struct proc {
    struct proc *next;
    int *ksp;
    int pid;
    int result;
    int kstack[SSIZE];
} PROC;

PROC proc[NPROC], *running;
int procSize = sizeof(PROC);
//extern int color;

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return (a - b);
}

int multiply(int a, int b) {
    return (a * b);
}

int divide(int a, int b) {
    if (b == 0) {
        prints("Error: Division by zero!\n");
        return 0;
    }
    return (a / b);
}

int prints(char *s)
{
// write YOUR code
   while(*s)
      putc(*s++);
}


int a;
int b;
//char * output;

int bodyadd() {
    //int pid = running->pid;
    //int result;

    while (1) {
        prints("Process (Addition) running\n");
        prints("Enter two numbers to add: ");
        a = getc();
        b = getc(); 

        running->result = add(a, b);
        //running->result = result;
        prints("Process  (Addition):\n");
        prints(running->result);
        tswitch();
    }
}

int bodysubtract() {
	//int result;
    while (1) {
        prints("Process (Subtraction) running\n");
        prints("Enter two numbers to subtract (a - b): ");
        a = getc();
        b = getc();

        running->result = subtract(a, b);
        //running->result = result;
        prints("Process (Subtraction):\n");
        prints(running->result);


        tswitch();
    }
}

int bodymultiply() {
	//int result;
    while (1) {
        prints("Process (Multiplication) running\n");
        prints("Enter two numbers to multiply: ");
        a = getc();
        b = getc();

        running->result = multiply(a, b);
        //running->result = result;
        prints("Process (Multiplication):\n");
        prints(running->result);

        tswitch();
    }
}

int bodydivide() {
	//int result;
    while (1) {
        prints("Process (Division) running\n");
        prints("Enter two numbers to divide (a / b): ");
        a = getc();
        b = getc();

        if (b == 0) {
            prints("Error: Division by zero!\n");
            continue;
        }

        running->result = divide(a, b);
        //running->result = result;
        prints("Process (Division):\n");
        prints(running->result);


        tswitch();
    }
}

int init() {
    PROC *p;
    int i, j;

    for (i = 0; i < NPROC; i++) {
        p = &proc[i];
        p->pid = i;
        p->next = &proc[i + 1];

        if(i == 0){
               p->kstack[SSIZE - 1] = (int)bodyadd;
         }
         else if(i == 1){
               p->kstack[SSIZE - 1] = (int)bodysubtract;
               
        }
        else if(i == 2){
               p->kstack[SSIZE - 1] = (int)bodymultiply;
        }
        else{
               p->kstack[SSIZE - 1] = (int)bodydivide;
        }

        for (j = 2; j < 10; j++)
            p->kstack[SSIZE - j] = 0;
        p->ksp = &(p->kstack[SSIZE - 9]);
    }

    proc[NPROC - 1].next = &proc[0];
    running = &proc[0];
}

int scheduler() {
    running = running->next;
}

int main() {
 
  prints("MTX starts in main()\n");
  init();
  while(1){
    prints("proc 0  running : enter a key : \n");
    getc();
    tswitch();
  }
}

