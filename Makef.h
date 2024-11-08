#ifndef __MAKEF_H__
#define __MAKEF_H__

#include <dirent.h>
#include <stdio.h>


void make_flags();
void set_execName(int argv, char **argc);
void load_Cfiles();
void set_all();
void run_and_clean();
void make_depend();

void open_dir(DIR **dir, const char *name);
void open_file(FILE **file, const char *name, const char *format);

void close_file(FILE **file);
void close_dir(DIR **dir);

#endif