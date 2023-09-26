#include<stdio.h>
#include<stdlib.h>
#include<fbas.h>
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
	char buf[101];
	while (rd_ = read(fp, buf ,source_size-source_size /2))
        {
                write (fp_tar, buf, rd_);
        }
        sem_post(&sem);
        pthread_exit (0);
}

void *start_routine2 (void *args)
{
        sem_wait(&sem);
	int rd_ = 0;
	char buf[101];
	while (rd_ = read(fp, buf, source_size /2))
        {
                 write (fp_tar, buf, rd_);
        }
        pthread_exit (0);
}


bool copy_file (std::string source, std::string tar, std::string s)
{
        pthread_t th,th2;
        sem_init(&sem,0,0);
	// touch file
	if ( (fp = open( (source+s).c_str(), O_RDONLY)) == -1)
	{
		return perror("cpoy file 61 -> open source file err"),false;
	}
	if ( (fp_tar = open((tar+s).c_str(), O_RDONLY|O_WRONLY|O_CREAT,0777) ) == -1)
        {
                return perror("copy.cpp 65 open error tar"),false;
        }
	// size
	source_size = lseek(fp,0,SEEK_END);
        lseek(fp,0,SEEK_SET);

        sem_post(&sem);
        pthread_create(&th, NULL, start_routine,NULL) ;
        pthread_create(&th2, NULL, start_routine2, NULL) ;
        sem_destroy(&sem);
        pthread_exit(0);
        return true;
}

