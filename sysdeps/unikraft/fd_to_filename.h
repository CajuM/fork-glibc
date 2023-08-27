#ifndef _FD_TO_FILENAME_H
#define _FD_TO_FILENAME_H

#include <intprops.h>
#include <uk/nolibc/limits.h>

struct fd_to_filename
{
  /* A positive int value has at most 10 decimal digits.  */
  char buffer[PATH_MAX];
};

/* Writes the path associated with the file DESCRIPTOR to *STORAGE and
   returns a pointer to the start of the string.  DESCRIPTOR must be
   non-negative.  */
char *__fd_to_filename (int descriptor, struct fd_to_filename *storage)
  attribute_hidden;

#endif /* _FD_TO_FILENAME_H */
