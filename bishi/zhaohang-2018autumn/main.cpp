#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void q1()
{
  vector<int> gvec;
  vector<int> svec;

  char c;
  int v;

  string gstr;
//  gstr = "1 2 3";
  getline(cin, gstr);
  int idx = gstr.find_first_not_of(' ');
  v = 0;
  for (; idx < gstr.length(); ++idx) {
    c = gstr.at(idx);
    if (c == ' ') {
      gvec.push_back(v);
      v = 0;
      continue;
    }
    v = v*10 + c-'0';
  }
  if (v)
    gvec.push_back(v);

  string sstr;
//  sstr = "1 1";
  getline(cin, sstr);
  idx = sstr.find_first_not_of(' ');
  v = 0;
  for (; idx < sstr.length(); ++idx) {
    c = sstr.at(idx);
    if (c == ' ') {
      svec.push_back(v);
      v = 0;
      continue;
    }
    v = v*10 + c-'0';
  }
  if (v)
    svec.push_back(v);

//  cout << gvec. << endl;
//  cout << svec << endl;

  sort(gvec.begin(), gvec.end());
  sort(svec.begin(), svec.end());
  int cnt = 0;
  int i = 0;
  for (int sj : svec) {
    if (sj >= gvec.at(i)) {
      ++cnt;
      ++i;
    }
  }
  cout << cnt << endl;
}

void q2()
{
  int n;
  int ppre, pre, cur;

  cin >> n;

  switch (n) {
  case 1:
    cur = 1;
    break;
  case 2:
    cur = 2;
  default:
    break;
  }

  ppre = 1;
  pre = 2;

  for (int i = 3; i <= n; ++i) {
    cur = ppre + pre;

    ppre = pre;
    pre = cur;
  }
  cout << cur;
}

int mypow(int b, int e)
{
  int v = 1;
  for (int i = 0; i < e; ++i)
    v *= b;
  return v;
}

bool isok(int n)
{
  int tn = n;

  int reversed = 0;

  int rad = 1;

  while (tn) {
    int yu = tn % 10;
    switch (yu) {
    case 0:
    case 1:
    case 8:
      reversed += yu * rad;
      break;
    case 2:
      reversed += 5 * rad;
      break;
    case 5:
      reversed += 2 * rad;
      break;
    case 6:
      reversed += 9 * rad;
      break;
    case 9:
      reversed += 6 * rad;
      break;
    default:
      return false;
    }
    rad *= 10;
    tn /= 10;
  }

  if (reversed == n)
    return false;

  return true;
}

void q3()
{
  int n;
  n = 10;
//  cin >> n;

  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    if (isok(i))
      ++cnt;
  }
  cout << cnt;
  return;


  int h;
  int len = 1;
  while (n/10 != 0) {
    ++len;
    n /= 10;
  }
  h = n;
//  cout << len << endl;

//  int cnt = 0;
  for (int i = 1; i < len; ++i) {
    cnt += mypow(4, i);
  }

  if (2 <= h && h < 5)
    cnt += mypow(4, len-1);
  else if (h == 5)
    cnt += 2*mypow(4, len-1);
  else if (6 <= h && h < 9)
    cnt += 3*mypow(4, len-1);
  else if (h == 9)
    cnt += mypow(4, len);

  cout << cnt << endl;
}

int main()
{
//  q1();
  q3();
  return 0;
}
