#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "dirinfo.h"

void metaPermissions(char * file){ //add permissions and file size
  struct stat stat_buff;
  stat(file, &stat_buff);
  int perm = stat_buff.st_mode % 01000;
  int user = perm / 0100;
  int group = perm % 0100 / 010;
  int other = perm % 010;

  char * wholePerm[3] = {"", "", ""};
  char * perms[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};

  for (int i = 0; i < 3;i++) {
    wholePerm[0] = perms[user];
    wholePerm[1] = perms[group];
    wholePerm[2] = perms[other];
  }

  printf("\t%s%s%s    %lld    ", wholePerm[0],wholePerm[1],wholePerm[2], stat_buff.st_size);
}

void listRegFiles(char * path){
  DIR * stream = opendir(path);
  if (stream == NULL) { //checking if directory exists
    printf ("Error opening directory %s: %s\n", path, strerror(errno));
  }
  struct dirent * entry = readdir(stream);
  printf("Regular Files:\n");
  while (entry != NULL){
    if(entry->d_type == 8){ //checking file type
      metaPermissions(entry->d_name);
      printf("%s\n", entry->d_name);
    }
    entry = readdir(stream);
  }
}

void listDirectory(char * path){
  DIR * stream = opendir(path);
  if (stream == NULL) { //checking if directory exists
    printf ("Error opening directory %s: %s\n", path, strerror(errno));
  }
  struct dirent * entry = readdir(stream);
  printf("Directories:\n");
  while (entry != NULL){
    if(entry->d_type == 4){ //checking file type
      metaPermissions(entry->d_name);
      printf("%s\n", entry->d_name);
    }
    entry = readdir(stream);
  }
}

void listFiles(char * path){ //combines reg and dir types
  listDirectory(path);
  listRegFiles(path);
}

int totalSize(char * path){
  DIR * stream = opendir(path);
  if (stream == NULL) {
    printf ("Error opening directory %s: %s\n", path, strerror(errno));
  }
  struct dirent * entry = readdir(stream);
  int size = 0;
  struct stat stat_buff;
  while (entry != NULL){
    stat(entry->d_name, &stat_buff); //checks metadata of file for size
    size += stat_buff.st_size;
    entry = readdir(stream);
  }
  return size;
}

int main(int argc, char *argv[]){
  if (argc < 2) {
    printf("Statistics for directory: .\n");
    printf("Total Diectory Size: %d Bytes\n", totalSize("."));
    listFiles(".");
  } else {
    printf("Statistics for directory: %s\n", argv[1]);
    printf("Total Diectory Size: %d Bytes\n", totalSize(argv[1]));
    printf("All Files:\n");
    listFiles(argv[1]);
  }
  return 0;
}
