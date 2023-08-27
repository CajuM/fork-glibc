#include <fd_to_filename.h>

#include <assert.h>
#include <string.h>
#include <_itoa.h>

#include <uk/vfscore/file.h>

char *
__fd_to_filename (int descriptor, struct fd_to_filename *storage)
{
  assert (descriptor >= 0);

  struct vfscore_file *fp = vfscore_get_file(descriptor);
  strncpy(storage->buffer, fp->f_dentry->d_path, sizeof(storage->buffer));

  return storage->buffer;
}
