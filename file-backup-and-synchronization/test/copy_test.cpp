#include<stdio.h>
#include<stdlib.h>
//#include<fbas.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<ctype.h>
#include<string.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<semaphore.h>
#include<dirent.h>
#include<string>
#include <filesystem>
#include <fstream>
#include<bits/stdc++.h>

int fp,fp_tar;
int source_size = 0;
sem_t sem;

void *start_routine (void *args)
{
        sem_wait(&sem);
        int rd_ = 0;
	//std::cout << "1\n";
        char buf[101];
        while (rd_ = read(fp, buf ,source_size-source_size /2))
        {
                write (fp_tar, buf, rd_);
        }
	std::cout << "1\n";
        sem_post(&sem);
        pthread_exit (0);
}

void *start_routine2 (void *args)
{
        sem_wait(&sem);
        int rd_ = 0;
	std::cout <<"2\n";
        char buf[101];
        while (rd_ = read(fp, buf, source_size /2))
        {
                 write (fp_tar, buf, rd_);
        }
        pthread_exit (0);
}


int main()
{
	std::string source, tar ,s;
	std::cin >> source >> tar >> s;
	std::cout << "->>>>\n";
        pthread_t th,th2;
        sem_init(&sem,0,0);
        // l file
        if ( (fp = open( (source+s).c_str(), O_RDONLY)) == -1)
        {
                return perror("cpoy file -> open source file err"),false;
        }
        if ( (fp_tar = open((tar+s).c_str(), O_RDONLY|O_WRONLY|O_CREAT,0777) ) == -1)
        {
                return perror("open error tar"),false;
        }
	std::cout << tar+s << "\n";
        // size
        source_size = lseek(fp,0,SEEK_END);
        lseek(fp,0,SEEK_SET);

        sem_post(&sem);
        if ( pthread_create(&th, NULL, start_routine,NULL) )
        {
                perror("pthread_create");
                return false;
        }

        if ( pthread_create(&th2, NULL, start_routine2, NULL) )
        {
                perror("pthread_create 2 ");
                return false;
        }
        sem_destroy(&sem);
        pthread_exit(0);
        return 0;
}
