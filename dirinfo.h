#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

void metaPermissions(char * file);
void listDirectory(char * path);
void listRegFiles(char * path);
void listFiles(char * path);
int totalSize(char * path);
