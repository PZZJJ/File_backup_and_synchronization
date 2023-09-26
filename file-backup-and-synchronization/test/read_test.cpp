#include<stdio.h>
#include<stdlib.h>
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

bool read_tar (std::string tar, std::set<std::string> &f)
{
        DIR *dir_tar;
	if ( (dir_tar = opendir (tar.c_str())) == NULL)
	{
		perror("openerroe");
		return false;
	}

        struct dirent *read_t,*read_s;
        char buf[1024];
        while (read_s = readdir(dir_tar))
        {
                if (!strcmp(".",read_s->d_name) || !strcmp("..",read_s->d_name))
                {
                        continue;
                }
                sprintf(buf, "%s/%s", tar.c_str(), read_s->d_name);
                if (read_s->d_type == DT_DIR)
                {
                        std::string s(buf);
                        read_tar (s,f);
                }
                else
                {
                        std::string s(buf);
                        f.insert(s);
                }
        }
        return true;
}

int main()
{
	std::string tar;
	std::set<std::string> f;
	std::cin >> tar;
	read_tar(tar,f);
	for (auto x : f)
	{
		std::cout << x << "\n";
	}
	return 0;
}


