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
//using namespace std;
int calculate_file_size (std::string tar)
{
        int res = 0;
        res = (int)std::filesystem::file_size(tar.c_str());
        return res;
}
int calculate_dir_size (std::string tar)
{
        int res;
        DIR *dir;
        char buf[1024];
        struct dirent *dirin;

        dir = opendir(tar.c_str());

        while (dirin = readdir(dir))
        {
                if (!strcmp(".",dirin->d_name) || !strcmp("..",dirin->d_name))
                {
                        continue;
                }

                sprintf(buf,"%s/%s", tar.c_str(), dirin->d_name);

                std::string s(buf);
                if (dirin->d_type == DT_DIR)
                {
                        calculate_dir_size (s);
                }
                else
                {
                        res += calculate_file_size(s);
                }
        }
        return res;
}

int main()
{
	std::string s;
	std::cin >> s;
	int x = calculate_dir_size(s);
	std::cout << x << "\n";
	return 0;
}

