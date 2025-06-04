#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

ifstream fin("timbre.in");
ofstream fout("timbre.out");

struct compare{
	bool operator()(pair<int, int> a, pair<int, int> b)
	{
		return a.second > b.second;
	}
};

int main() 
{
	priority_queue<pair<int, int>, vector<pair<int, int>>> q;
	priority_queue<pair<int, int>, vector<pair<int, int>>, compare> q2;
	int n, m, k, dr, c, cost = 0;
	fin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
		fin >> dr >> c, q.push({ dr,c });
	while (n > 0)
	{
		while (!q.empty() && q.top().first >= n)
			q2.push(q.top()), q.pop();
		cost += q2.top().second;
		q2.pop();
		while (!q2.empty())
			q.push(q2.top()), q2.pop();
		n -= k;
	}
	fout << cost;
	return 0;
}