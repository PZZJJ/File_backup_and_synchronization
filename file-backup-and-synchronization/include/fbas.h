/*
 *
 *
 *
 *
 */
#include<bits/stdc++.h>

void solve();

bool delete_file (std::string );

bool delete_dir (std::string );

bool source_sync_to_tar (std::string , std::string );

bool two_way_synchronization (std::string , std::string );

int calculate_file_size (std::string );

int calculate_dir_size (std::string );

bool read_tar (std::string , std::set<std::string> &);

bool copy_file (std::string , std::string , std::string);

bool two_copy_file (std::string, std::string, std::string);

int comp_filetime (std::string , std::string );

void *start_routine2 (void *);

void *start_routine (void *);

void *two_start_routine (void *);

void *two_start_routine (void *);
