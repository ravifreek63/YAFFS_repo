#ifndef __YAFFS_TRANSLATE_H__
#define __YAFFS_TRANSLATE_H__

#include "global.h"
//#include "yaffsfs.h"
//#include "stdio.h"

/*
 * Currently file_open does the following translation
 * It receives a path name from TxFS_manager in path , flags for open mode
 * The ext file-system requires the file-descriptor, and so the return value is the fd itself
 * TODO : YAFFS requires the mode to be specified at the time of file-opening, currently we assume that
 * if no permission is provided then the permissions are for read and write both.
 */
int tr_file_open_without_mode (const char *path, int flags);
int tr_file_open_with_mode (const char *path, int flags, int mode);

#endif
