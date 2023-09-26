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

bool source_sync_to_tar (std::string source, std::string tar)
{
	//计算源目录大小
        int source_max = calculate_dir_size (source);

        //DIR dir_source = opendir (source.c_str());
        //DIR dir_tar = opendir (tar.c_str());

	std::set<std::string> f,t;
	std::vector<std::string> des;
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
                                if (k > 0)
                                {
                                        des.push_back(s);
					flag = true;
					break;
                                }
				//else if (k < 0)
				//{
				//	des.push_back(x);
				//}
                        }
                }
		if (flag)
		{
			continue;
		}
		des.push_back(s);	
        }
	// 删除不相同的文件
	for (auto x : t)
	{
		bool flag = false;
		for (auto y : f)
		{
			std::string s,ss;	
			ss = x.substr(tar.length(),x.length()-tar.length());
			s = y.substr(source.length(),y.length()-source.length());
			if (s == ss)
			{
				int k;
				k = comp_filetime(x,y);
				if (!k)
					flag = true;				
				break;
			}
		}
		if (flag)
		{
			continue;
		}
		//不存在，删掉
		int p;
		if ((p = remove(x.c_str())) == -1)
		{
			return perror("sync_to->  remove err! line 49"),false;
		}
	}


	int cur = 0;
	int i = 0;
        char bar[102];
        const char *lable = "|/-\\";
        bar[0] = 0;
	while (i <= 100)
        {
                printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
                fflush(stdout);
                bar[i] = '#';
                i++;
                bar[i] = 0;
        }
	sleep(1);
	for (auto x : des)
	{
		int y = calculate_file_size((source+x).c_str());
		if (copy_file(source,tar,x) == false)
		{
			return perror("sou sync to tar 109 copy file err!"),false;		
		}
			cur += y / source_max;
			while (i <= cur)
        		{
                	printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
                	fflush(stdout);
                	bar[i] = '#';
                	i++;
                	bar[i] = 0;
        	}
	}
	 while (i <= 100)
        {
                printf("[%-100s][%d%%][%c]\r", bar, i, lable[i%4]);
                fflush(stdout);
                bar[i] = '#';
                i++;
                bar[i] = 0;
        }
	printf("\n");
        return true;
}
