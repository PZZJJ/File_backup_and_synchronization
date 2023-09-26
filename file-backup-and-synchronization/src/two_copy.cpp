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

extern int fp,fp_tar;
extern int source_size;
extern sem_t sem;

void *two_start_routine (void *args)
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

void *two_start_routine2 (void *args)
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


bool two_copy_file (std::string source, std::string tar, std::string s)
{
        pthread_t th,th2;
        sem_init(&sem,0,0);
        // touch file
	std::string tmp;
	if (s[0] == tar[0])
	{
		tmp = source;
		source = tar;
		tar = tmp;
	}
        if ( (fp = open( s.c_str(), O_RDONLY)) == -1)
        {
                return perror("two cpoy file 68 -> open source file err"),false;
        }
	s = s.substr(tar.length(), source.length()-tar.length());
        if ( (fp_tar = open((tar+s).c_str(), O_RDONLY|O_WRONLY|O_CREAT,0777) ) == -1)
        {
                return perror("two copy 73 open error tar"),false;
        }
        // size
        source_size = lseek(fp,0,SEEK_END);
        lseek(fp,0,SEEK_SET);

        sem_post(&sem);
        if ( pthread_create(&th, NULL, two_start_routine,NULL) )
        {
                perror("two copy 82 pthread_create");
                return false;
        }

        if ( pthread_create(&th2, NULL, two_start_routine2, NULL) )
        {
                perror("two copy 88 pthread_create 2 ");
                return false;
        }
        sem_destroy(&sem);
        pthread_exit(0);
        return true;
}
