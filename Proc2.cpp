#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

ifstream fin("proc2.in");
ofstream fout("proc2.out");

int main() 
{
	priority_queue<int, vector<int>, greater<>> libere;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> s;
	int n, m, ti, d;
	fin >> n >> m;
	for (int i = 1; i <= n; i++)
		libere.push(i);
	for (int i = 1; i <= m; i++)
	{
		fin >> ti >> d;
		while (!s.empty() && ti >= s.top().first)
			libere.push(s.top().second), s.pop();
		int x = libere.top();
		libere.pop();
		s.push({ ti + d, x });
		fout << x << '\n';
	}
	return 0;
}