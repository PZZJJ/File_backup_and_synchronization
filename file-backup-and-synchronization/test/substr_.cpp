#include<bits/stdc++.h>
using namespace std;

int main()
{
	string s,ss;
	s = "12/345";
	string a = "dd";	
	s=s.substr(a.length(), s.length()-a.length());
	cout << s << "\n";
	cout << "sub = " << a << "\n";
}
