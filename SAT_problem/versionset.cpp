#include "versionset.h"

VersionSet::VersionSet()
{

}

void VersionSet::appendVer(Version *v)
{
  current = v;

  v->prev = dummy_versions.prev;
  v->next = &dummy_versions;
  v->prev->next = v;
  v->next->prev = v;
}
