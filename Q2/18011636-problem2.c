#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int count=0;

void function1(int signo){ //function for SIGINT
	psignal(signo,"Received Signal::");
	getchar();
}
void function2(int signo){ //function for SIGTSTP
	psignal(signo,"Received Signal:: ");
	getchar();
}
void function3(int signo){ //function for SIGQUIT
	psignal(signo,"");
	exit(1);
}
void function4(int signo){ //function for SIGQUIT
	printf("Waiting for signal to be received! Count:%d\n",count);
	count++;
	getchar();
}



int main(){

	pid_t pid;
	pid=getpid();

	struct sigaction act,act2,act3,act4; //sigaction struct to modify its table
	
	printf("PID is:%d\n",pid);

	sigemptyset(&act.sa_mask); //empty all the data of sigset_t struct(or int)
	sigfillset(&act.sa_mask);

	sigemptyset(&act2.sa_mask); //empty all the data of sigset_t struct(or int)
	sigfillset(&act2.sa_mask);

	sigemptyset(&act2.sa_mask); //empty all the data of sigset_t struct(or int)
	sigfillset(&act2.sa_mask);

	sigemptyset(&act3.sa_mask); //empty all the data of sigset_t struct(or int)
	sigfillset(&act3.sa_mask);

	sigemptyset(&act4.sa_mask); //empty all the data of sigset_t struct(or int)
	sigfillset(&act4.sa_mask);

	act.sa_flags=0; //set flag value to 0 

	act.sa_handler=function1; //set handler to function1 so that function1 will perform if sigcation caught SIGSTP 
	act2.sa_handler=function2;
	act3.sa_handler=function3;
	act4.sa_handler=function4;

	sigaction(SIGINT,&act,(struct sigaction*)NULL);
	sigaction(SIGTSTP,&act2,(struct sigaction*)NULL);
	sigaction(SIGQUIT,&act3,(struct sigaction*)NULL);
	sigaction(SIGUSR1,&act4,(struct sigaction*)NULL);

	pause();

	return 0;
}
/*
	
	printf("signal number %d\n", signo);*/
