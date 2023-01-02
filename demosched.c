#include "types.h"
#include "user.h"


#define SLEEP_COUNTER 50000000


void sleep_bound_cpu(void)
{
	volatile int x = 0, i;

	for (i = 0; i < SLEEP_COUNTER; i++) {
		x = x + 3.14 * 89.64;
		x /= 6.325;
		x += 123;
		x *= 1.1112;
		x = 10;

	}


}

void processWork(int priority)
{
	setprio(priority);
	
	sleep_bound_cpu();
	printf(1, "Process: %d done, With priority: %d\n", getpid(), getprio());
	exit(); // terminate process

}

void handleForkFail(int fork_value)
{
	if(fork_value == -1) { 
		printf(1, "fork failed, exiting...\n");
		while(wait() != -1); // reap all child processes
		exit(); // terminate
	}
}


int main(void)
{

	int fork_value = fork();
	handleForkFail(fork_value);

	// first child process
	if (fork_value == 0) {
		processWork(1); 
	}


	// father process forks again
	else {
		fork_value = fork();
		handleForkFail(fork_value);
		
		// second process
		if (fork_value == 0) {	
			processWork(3); 
		}

		// father process forks again
		else {
			fork_value = fork();
			handleForkFail(fork_value);
		
			
			// third process
			if (fork_value == 0) {	
				processWork(4); 
			}

			// father forks again
			else {
				fork_value = fork();
				handleForkFail(fork_value);
				
				// fourth process
				if (fork_value == 0) {	
					processWork(6);
				}

				
				// father forks again
				else {
					fork_value = fork();
					handleForkFail(fork_value);

					// 5th process
					if (fork_value == 0) {	
						processWork(7);
					}

					// father waits for all processes to finish
					else {
						while(wait() != -1);
					}
				}
			}


		}

	}

	exit(); // terminate

}

