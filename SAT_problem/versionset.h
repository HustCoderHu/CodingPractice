#ifndef VERSIONSET_H
#define VERSIONSET_H

#include "version.h"

class VersionSet
{
public:
  VersionSet();

  void appendVer(Version *v);

  Version dummy_versions; // 双链表头
  Version *current;

};

#endif // VERSIONSET_H
