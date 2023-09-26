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

// struct dirent {
//               ino_t          d_ino;       /* Inode number */
//               off_t          d_off;       /* Not an offset; see below */
//               unsigned short d_reclen;    /* Length of this record */
//               unsigned char  d_type;      /* Type of file; not supported
//                                              by all filesystem types */
//               char           d_name[256]; /* Null-terminated filename */
//           };

// delete file
bool delete_file (std::string tar)
{
	if (remove(tar.c_str()) == -1)
	{
		return perror("func 38 remove file error"),false;
	}
	return true;
}

//delete dir
bool delete_dir (std::string tar)
{
	DIR *dir;
	char buf[1024];
	struct dirent *dirin;
	
	if ( dir = opendir(tar.c_str()))
	{
		return perror("func delete 52 dir open err!"),false;
	}

	while (dirin = readdir(dir))
	{
		if (!strcmp(".",dirin->d_name) || !strcmp("..",dirin->d_name))
		{
			continue;
		}

		sprintf(buf,"%s/%s", tar.c_str(), dirin->d_name);		
		
		if (dirin->d_type == DT_DIR)
		{
			std::string s(buf);
			delete_dir (s);
		}
		else
		{
			if (remove(buf) == -1)
			{
				return perror("delete files in directory err!"),false;
			}
		}
	}

	if (remove(tar.c_str()) == -1)
	{
		return perror("func delete 80 dir err!"),false;
	}
	return true;
}


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

//Read all file information in a directory
bool read_tar (std::string tar, std::set<std::string> &f)
{
        DIR *dir_tar ; 
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
			read_tar(s,f);
                }
                else
                {	
			std::string s(buf);
			f.insert(s);
                }
        }
	return true;
}

//bool copy_file(std::string source, std::string tar, std::string s)
//{
	

//}

int comp_filetime(std::string source_file1, std::string source_file2)
{
	struct stat att,att2;
	//char path[101], path2[101];
	//path = source_file1.c_str();
	//path2 = source_file2.c_str();
        stat (source_file1.c_str(),&att);
        stat (source_file2.c_str(),&att2);
        if (att.st_mtim.tv_sec > att2.st_mtim.tv_sec)
        {
		return 1;
        }
        else if (att.st_mtim.tv_sec == att2.st_mtim.tv_sec)
        {
                return 0;
        }
        else
        {
                //std::cout << " error comp filetime!\n";
		return -1;
        }		
}







