#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void function(int signo, siginfo_t* siginfo){ //handler function.

	if(siginfo->si_code == SI_QUEUE){ //If there is a queueing signal, SI_QUEUE is set 
		printf("signal is queueing\nPID: %d\nSIG number: %d\nData: %d\n",
siginfo->si_pid,siginfo->si_signo,siginfo->si_value.sival_int); //print out queueing signal data
		getchar();//wait for another queueing signal
	}
	else{
		printf("Unix Standard signal\nSIG number: %d\n",signo);
	}
}

int main(){
	struct sigaction act; //struct sigaction

	printf("Process PID is: %d\n",getpid()); //show PID number so that send can use its PID
	
	sigemptyset(&act.sa_mask); //empty signal set
	sigaddset(&act.sa_mask,SIGQUIT); //add SIGQUIT to a set

	act.sa_flags=SA_SIGINFO; //for using struct siginfo_t

	act.sa_handler=function; //set handler for function

	if(sigaction(SIGTSTP,&act,(struct sigaction*)NULL)<0){ //If error
		printf("error\n");
		exit(1);
	}
	else{ //If not error
		printf("Wait process for receive RTS...\n");
		pause(); //wait process for receive RTS
	}
	return 0;
}
