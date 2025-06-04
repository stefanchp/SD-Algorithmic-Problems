#include <fstream>
#include <algorithm>
#define DIM 502
using namespace std;

ifstream fin("plantatie.in");
ofstream fout("plantatie.out");

int n, m, i1, i2, j1, j2, lat, L, len, k;
int r[10][DIM][DIM];
int E[DIM];

int main() 
{
	fin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) 
			fin >> r[0][i][j];
	for (int p = 1, lat = 2; lat <= n; p++, lat *= 2) 
		for (int i1 = 1; i1 <= n - lat + 1; i1++) 
			for (int j1 = 1; j1 <= n - lat + 1; j1++)
			{
				i2 = i1 + (lat >> 1);
				j2 = j1 + (lat >> 1);
				r[p][i1][j1] = max({r[p - 1][i1][j1], r[p - 1][i2][j1], 
								    r[p - 1][i1][j2], r[p - 1][i2][j2]});
			}
	E[1] = 0;
	for (int i = 2; i <= n; i++)
		E[i] = 1 + E[i / 2];
	while(m > 0) 
	{
		fin >> i1 >> j1 >> L;
		k = E[L];
		len = (1 << k); /// cea mai mare putere de 2 <= latura
		/// patratului de la interogare
		i2 = i1 + L - len;
		j2 = j1 + L - len;
		fout << max({ r[k][i1][j1], r[k][i1][j2], r[k][i2][j1], r[k][i2][j2] }) << "\n";
		m--;
	}
	return 0;
}
