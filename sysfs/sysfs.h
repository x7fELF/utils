/*
 * x7fELF, x7fELF@gmail.com, 2017
 * GNU GPL v2
 */

#ifndef __X7SYSFS_H
#define __X7SYSFS_H

int sysfs_open(const char *pathname, int flags);
ssize_t sysfs_read(int fd, void *buf, size_t count);
off_t sysfs_lseek(int fd, off_t offset, int whence);
int sysfs_poll(int fd, int timeout);
int sysfs_close(int fd);

#endif
