#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

ifstream fin("bleach.in");
ofstream fout("bleach.out");

int main() 
{
	priority_queue <long long, vector<long long>, greater<long long>> q;
	int n, k;
	long long x, ans = 0, pw_curent = 0;
	fin >> n >> k;
	k++;
	for (int i = 1; i <= k; i++)
		fin >> x, q.push(x);
	while (!q.empty())
	{
		x = q.top(); q.pop();
		if (x > pw_curent + ans)
			ans = x - pw_curent;
		pw_curent += x;
		if (++k <= n)
			fin >> x, q.push(x);
	}
	fout << ans;
	return 0;
}