#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s,ss;
	char tar[101];
	s = "as";
        ss = "agt";
	sprintf(tar, "%s/%s", s.c_str(), ss.c_str());
	cout << s << "\n";
	cout << tar << "\n";
	return 0;
}
