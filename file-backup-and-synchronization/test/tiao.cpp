#include <stdio.h>
#include <unistd.h>
 
int main()
 {
	int i = 0;
	char bar[102];
	const char *lable = "|/-\\";
	bar[0] = 0;
	while (i <= 10)
	{
		printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
		fflush(stdout);
	    	bar[i] = '#';
		i++;
		bar[i] = 0;
		//usleep(100000);
		usleep(10000);
	}
	sleep(2);
	while (i <= 20)
	{
		printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
                fflush(stdout);
                bar[i] = '#';
                i++;
                bar[i] = 0;
                //usleep(100000);
                usleep(10000);
	}
	printf("\n");
	return 0;
}
