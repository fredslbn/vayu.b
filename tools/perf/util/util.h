/* SPDX-License-Identifier: GPL-2.0 */
#ifndef GIT_COMPAT_UTIL_H
#define GIT_COMPAT_UTIL_H

#define _BSD_SOURCE 1
/* glibc 2.20 deprecates _BSD_SOURCE in favour of _DEFAULT_SOURCE */
#define _DEFAULT_SOURCE 1

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <linux/compiler.h>
#include <linux/types.h>
#include "namespaces.h"

/* General helper functions */
void usage(const char *err) __noreturn;
void die(const char *err, ...) __noreturn __printf(1, 2);

static inline void *zalloc(size_t size)
{
	return calloc(1, size);
}

#define zfree(ptr) ({ free(*ptr); *ptr = NULL; })

struct dirent;
struct strlist;

int mkdir_p(char *path, mode_t mode);
int rm_rf(const char *path);
struct strlist *lsdir(const char *name, bool (*filter)(const char *, struct dirent *));
bool lsdir_no_dot_filter(const char *name, struct dirent *d);
int copyfile(const char *from, const char *to);
int copyfile_mode(const char *from, const char *to, mode_t mode);
int copyfile_ns(const char *from, const char *to, struct nsinfo *nsi);
int copyfile_offset(int fromfd, loff_t from_ofs, int tofd, loff_t to_ofs, u64 size);

ssize_t readn(int fd, void *buf, size_t n);
ssize_t writen(int fd, const void *buf, size_t n);

size_t hex_width(u64 v);

extern unsigned int page_size;
extern int cacheline_size;

int fetch_kernel_version(unsigned int *puint,
			 char *str, size_t str_sz);
#define KVER_VERSION(x)		(((x) >> 16) & 0xff)
#define KVER_PATCHLEVEL(x)	(((x) >> 8) & 0xff)
#define KVER_SUBLEVEL(x)	((x) & 0xff)
#define KVER_FMT	"%d.%d.%d"
#define KVER_PARAM(x)	KVER_VERSION(x), KVER_PATCHLEVEL(x), KVER_SUBLEVEL(x)

const char *perf_tip(const char *dirpath);

#ifndef HAVE_GET_CURRENT_DIR_NAME
char *get_current_dir_name(void);
#endif

#ifndef HAVE_SCHED_GETCPU_SUPPORT
int sched_getcpu(void);
#endif

#ifndef HAVE_SETNS_SUPPORT
int setns(int fd, int nstype);
#endif

#endif /* GIT_COMPAT_UTIL_H */
