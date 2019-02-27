#ifndef VERSIONEDIT_H
#define VERSIONEDIT_H
#include "bitmap.h"

class VersionEdit
{
public:
  VersionEdit(int n)
    : deleted(n)
  {

  }

  void del(int var)
  {
    deleted.set(var, 1);
  }

  BitMap deleted;
};

#endif // VERSIONEDIT_H
