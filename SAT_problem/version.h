#ifndef VERSION_H
#define VERSION_H
#include "bitmap.h"
#include "versionedit.h"
#include "versionset.h"

class Version
{
public:
  Version();

  VersionSet *vset;
  Version *next;
  Version *prev;

  void apply(VersionEdit *edit);
  void restore(VersionEdit *edit);

  BitMap bmap;
};

#endif // VERSION_H
