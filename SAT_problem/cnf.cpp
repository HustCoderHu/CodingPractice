#include "cnf.h"

Cnf::Cnf()
{

}

void Cnf::parseFromFile(const char *fpath)
{

}

bool Cnf::existClause(unsigned int pos)
{
  return bmap.get(pos);
}

void Cnf::rmClause(unsigned int pos)
{
  bmap.set(pos, false);
}

void Cnf::snapshot()
{

}
