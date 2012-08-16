#include "yaffs_translate.h"

int tr_file_open_with_mode (const char *path, int flags, int mode)
{
  int handle = yaffs_open (path, flags, mode);
  int fd = yaffsfs_HandleToFileDes (handle);
  return fd;
}


int tr_file_open_without_mode (const char *path, int flags)
{
 int fd = tr_file_open_with_mode (path, flags, S_IREAD | S_IWRITE);
 return fd;
}


