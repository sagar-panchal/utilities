#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <chrono> 
#include <ctime> 
#include <iostream> 

using namespace std;
void periodic_task  (int signum)
{
 static int count = 0;
 printf (" periodic task in C++ timer %d \n", ++count);
    auto timenow = 
      chrono::system_clock::to_time_t(chrono::system_clock::now()); 
  
    cout << ctime(&timenow) << endl;
}

int main ()
{
 struct sigaction sa;
 struct itimerval timer;

 /* Install periodic_task  as the signal handler for SIGVTALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &periodic_task ;
 sigaction (SIGVTALRM, &sa, NULL);

 /* Configure the timer to expire after 250 msec... */
 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = 250000;

 /* ... and every 250 msec after that. */
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = 250000;

 /* Start a virtual timer. It counts down whenever this process is    executing. */
 setitimer (ITIMER_VIRTUAL, &timer, NULL);

 /* Do busy work. */
 while (1);

}
