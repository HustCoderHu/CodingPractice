#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_multimap<int, int> p2c;
typedef unordered_multimap<int,int>::iterator int_multimap;

//unordered_map<int, int>::const_iterator itr;
int sd = -1;

int dep(int pa)
{
  if (p2c.count(pa) == 0)
    return 1;

  unordered_multimap<int, int>::const_iterator itr;
  pair<int_multimap,int_multimap> p = p2c.equal_range(pa);

  int maxd = -1;
  for (itr = p.first; itr != p.second; ++itr) {
    pa = itr->second;
    sd = dep(pa);
    if (sd > maxd) maxd = sd;
  }

  return maxd+1;
}

void q1()
{
  unordered_set<int> pset;
  unordered_set<int> childSet;

  int p, child;

  while(cin>>p) {
    cin >> child;
    pset.insert(p);
    childSet.insert(child);
    p2c.insert({p, child});
  }

  // get root
  for (int pa : pset) {
    if (childSet.end() == childSet.find(pa)) {
      p = pa;
      break;
    }
  }
  cout << p << endl;
  sd = dep(p);
  cout << dep(p) << endl;
}

class Grade {
public:
  Grade(string s, int idx, int sc)
    :name(s), inIdx(idx), score(sc) { }
  string name;
  int inIdx;
  int score;
};

int getavg(string& name, const string& str)
{
  int total = 0;
  int v = 0;
  int cnt = 0;
  int idx = str.find_first_of(' ') + 1;
  name = str.substr(idx);

  char c;
  for (; idx < str.length(); ++idx) {
    c = str.at(idx);
    if (c == ' ') {
      total += v;
      v = 0;
      ++cnt;
      continue;
    }
    v = v*10 + c-'0';
  }
  if (v)
     total += v;

  return total/cnt;
}

void q2()
{
  string instr;
  string name;

  vector<Grade> gvec;
  int idx = 1;
  while (getline(cin, instr)) {
    int avg = getavg(name, instr);
    gvec.emplace_back(name, idx, avg);
  }

  auto cmp = [](const Grade& a, const Grade& b) {
    if (a.score == b.score)
      return a.inIdx < b.inIdx;
    return a.score > b.score;
  };

  sort(gvec.begin(), gvec.end(), cmp);
  for (Grade &g : gvec) {
    cout << g.name << " " << g.score << endl;
  }
}

int main()
{
//  q1();
  q2();
  return 0;
}
