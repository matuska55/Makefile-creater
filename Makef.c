#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "Makef.h"

DIR *dir;
FILE *makef;

void make_flags()
{
    fprintf(makef, "CC = gcc\n");
    fprintf(makef, "CFLAGS = -g -pedantic -Wall -Wextra\n");
    fprintf(makef, "LDFLAGS = \n\n");
}

void load_Cfiles()
{
    struct dirent *entry;
    int endName;

    fprintf(makef, "SRC = ");
    while ((entry = readdir(dir)) != NULL)
    {
        endName = strlen(entry->d_name);

        if (entry->d_name[endName - 1] == 'c' && entry->d_name[endName - 2] == '.')
            fprintf(makef, "%s ", entry->d_name);
    }
    fprintf(makef, "\n");
}

void set_execName(int argv, char **argc)
{
    fprintf(makef, "OBJ = $(SRC:.c=.o)\n");

    if (argv <= 1)
        fprintf(makef, "EXEC = a.out\n\n");
    else
        fprintf(makef, "EXEC = %s\n\n", argc[1]);
}

void set_all()
{
    fprintf(makef, "all: $(EXEC)\n\n");

    fprintf(makef, "$(EXEC): $(OBJ)\n");
    fprintf(makef, "\t$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)\n\n");

    fprintf(makef, "%c.o: %c.c\n", '%', '%');
    fprintf(makef, "\t$(CC) $(CFLAGS) -c $< -o $@\n\n");
}

void run_and_clean()
{
    fprintf(makef, "run:\n");
    fprintf(makef, "\t./$(EXEC)\n\n");

    fprintf(makef, ".PHONY: clean\n");
    fprintf(makef, "clean:\n");
    fprintf(makef, "\trm -f $(OBJ) $(EXEC)\n\n");
}

void make_depend()
{
    const char *command = "gcc -MM *.c > dep";
    int result = system(command);

    if (result == -1)
    {
        perror("system");
        exit(EXIT_FAILURE);
    }
    fprintf(makef, "-include dep\n");
}

void open_dir(DIR **dir, const char *name)
{
    *dir = opendir(name);
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
}

void open_file(FILE **file, const char *name, const char *format)
{
    *file = fopen(name, format);
    if (file == NULL)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
}

void close_file(FILE **file)
{
    if (file != NULL && *file != NULL)
        fclose(*file);
}

void close_dir(DIR **dir)
{
    if (dir != NULL && *dir != NULL)
        closedir(*dir);
}

int main(int argv, char **argc)
{
    open_dir(&dir, ".");
    open_file(&makef, "makefile", "w");

    make_flags();
    load_Cfiles();
    set_execName(argv, argc);
    set_all();
    run_and_clean();
    make_depend();

    close_file(&makef);
    close_dir(&dir);
}