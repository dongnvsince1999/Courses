//use command: gcc Lab3.c -pthread
//kill all text editor file, not only kill abcd.text! :'(

#include"stdio.h"
#include"pthread.h"
#include"signal.h"
#include<stdlib.h>
#include<unistd.h>

int MSSV = 17520350;
pthread_t idthread;
int isloop = 1;

void RequestA()
{
	printf("Welcome to IT007, I am %d", MSSV);
	printf("\n");
}

void *RequestB(void* message)
{	
	system("gedit abcd.txt");
}

void on_sigint(){
	system("pkill gedit");
 	printf("\nYou are pressed CTRL+C! Goodbye!\n");
isloop = 0;
		
} 

void RequestC()
{
	pthread_create(&idthread,NULL,&RequestB,NULL);		
	signal(SIGINT, on_sigint);
}

int main()
{
isloop = 1;
RequestA();
RequestC();

while(isloop){}

return 0;
}
