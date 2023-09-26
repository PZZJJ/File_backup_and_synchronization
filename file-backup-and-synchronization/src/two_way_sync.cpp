#include<stdio.h>
#include<stdlib.h>
#include<fbas.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/types.h>
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

bool two_way_synchronization (std::string source, std::string tar)
{
        //计算源目录大小
        int source_max = calculate_dir_size (source);

        //DIR dir_source = opendir (source.c_str());
        //DIR dir_tar = opendir (tar.c_str());

        std::set<std::string> f,t;
        std::set<std::string> des;
        //struct dirent *read_s, *read_t;
        char buf[101];

        read_tar(source,f);
        read_tar(tar,t);
        // 判断是否需要copy,将需要的也就是文件内容不相同的放入容器
        for (auto x : f)
        {
                bool flag = false;
                std::string s,ss;
                s = x.substr(source.length(),x.length()-source.length());
                for (auto y : t)
                {
                        if (s == ss)
                        {
                                ss = y.substr(tar.length(),y.length()-tar.length());
                                int k;
                                k = comp_filetime(x,y);
                                if (k >= 0)
                                {
                                        des.emplace(x);
                                        flag = true;
                                        break;
                                }
                                else if (k < 0)
                                {
                                      des.emplace(y);
                                }
                        }
                }
                if (flag)
                {
                        continue;
                }
                des.emplace(x);
        }
        for (auto x : t)
        {
		des.emplace(x);
        }

        int i = 0;
        char bar[102];
        const char *lable = "|/-\\";
        bar[0] = 0;
        int cur = 0;
        for (auto x : des)
        {
                int y = calculate_file_size((source+x).c_str());
                if (two_copy_file(source,tar,x) == false)
                {
                        return perror("two sync 84 copy file err!"),false;
                }
                cur += y / source_max;
                while (i <= cur)
                {
                        printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
                        fflush(stdout);
                        bar[i] = '#';
                        i++;
                        bar[i] = 0;
                        usleep(100000);
                        //usleep(10000);
                }

        }
        while (i <= 100)
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
        return true;
}
