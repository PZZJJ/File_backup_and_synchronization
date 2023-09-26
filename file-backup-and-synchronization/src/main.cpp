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

void solve()
{
	printf("please press number to indicate what you want to do!\n");
	printf("[1]: backup file \n");
	printf("[2]: Sync source directory to target directory \n");
	printf("[3]: Two-way synchronization of two directories \n ");
	int x = 0;
	scanf("%d",&x);
	if (x == 1)
	{
		std::cout << "Enter the source directory and destination directory names:\n";
		std::cout << "source: ";
		std::string sou,tar;
		std::cin >> sou;
		std::cout << "target: ";
		std::cin >> tar;
		if (source_sync_to_tar(sou,tar) == false)
		{
			perror("main 42 copy error!");
			return;
		}
	}
	else if(x == 2)
	{
		std::cout << "Enter the source directory and destination directory names:\n";
                std::cout << "source: ";
                std::string sou,tar;
                std::cin >> sou;
                std::cout << "target: ";
                std::cin >> tar;
                if (source_sync_to_tar(sou,tar) == false)
                {
                        perror("main 56 copy error!");
			return;
                }
	}
	else if (x == 3)
	{
		std::cout << "Enter the directory names:\n";
                std::cout << "dir1: ";
                std::string sou,tar;
                std::cin >> sou;
                std::cout << "dir2: ";
                std::cin >> tar;
                if (two_way_synchronization (sou,tar) == false)
                {
                        perror("main 71  error!");
			return;
                }
	}
	return;
}

int main()
{
	solve();
	return 0;
}

