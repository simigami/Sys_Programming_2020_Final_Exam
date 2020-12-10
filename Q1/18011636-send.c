#include<stdio.h>
#include<signal.h>

int main(){
	union sigval sig; //sigval variable is need to set a user data
	int PID; //PID and data information to send
	int student_number = 18011636;
	
	printf("Process ID that want to send to another process:"); //input a PID, PID should be a receive process
	scanf("%d",&PID);

	sig.sival_int = student_number; //set a int data as my student number

	sigqueue(PID, SIGTSTP, sig); //queue a signal to receive
}
