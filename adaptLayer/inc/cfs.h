//
//  cfs.h
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#ifndef __CFS_H__
#define __CFS_H__

typedef int cfs_offset_t;

/**
 * Specify that cfs_seek() should compute the offset from the beginning of the file.
 *
 * \sa cfs_seek()
 */
#ifndef CFS_SEEK_SET
#define CFS_SEEK_SET 0
#endif

/**
 * Specify that cfs_seek() should compute the offset from the current position of the file pointer.
 *
 * \sa cfs_seek()
 */
#ifndef CFS_SEEK_CUR
#define CFS_SEEK_CUR 1
#endif

/**
 * Specify that cfs_seek() should compute the offset from the end of the file.
 *
 * \sa cfs_seek()
 */
#ifndef CFS_SEEK_END
#define CFS_SEEK_END 2
#endif

int cfs_open(const char *name, int flags);

void cfs_close(int fd);

int cfs_read(int fd, void *buf, unsigned int len);

int cfs_write(int fd, const void *buf, unsigned int len);

cfs_offset_t cfs_seek(int fd, cfs_offset_t offset, int whence);

int cfs_remove(const char *name);

#endif /* __CFS_H__ */
