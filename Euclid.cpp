#include <fstream>
#include <algorithm>
#define DIM 401
using namespace std;

ifstream fin("euclid.in");
ofstream fout("euclid.out");

int D[9][DIM][DIM];
int L[DIM][DIM];
int E[DIM];
int m, n, h, w, i, j, t, e, sol, T;

int cmmdc(int a, int b) 
{
	int r;
	while (b) 
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int maxim(int a, int b) 
{
	return a > b ? a : b;
}

int main() 
{
	/// precalculare: E[i] = exponentul celei mai mari
	/// puteri de 2 mai mica sau egala cu i
	E[1] = 0;
	for (i = 2; i <= 400; i++)
		E[i] = 1 + E[i / 2];
	fin >> T;
	for (t = 1; t <= T; t++) {
		sol = 0;
		fin >> m >> n >> h >> w;
		for (i = 1; i <= m; i++)
			for (j = 1; j <= n; j++)
				fin >> D[0][i][j];
		/// calculam in D cmmdc pentru secvente
		/// de lungime putere de 2, pe linii
		for (e = 1; (1 << e) <= n; e++)
			for (i = 1; i <= m; i++)
				for (j = 1; j <= n; j++) 
				{
					D[e][i][j] = D[e - 1][i][j];
					if (j + (1 << (e - 1)) <= n)
						D[e][i][j] = cmmdc(D[e - 1][i][j],
							               D[e - 1][i][j + (1 << (e - 1))]);
				}
		/// interogam D si obtinem in L cmmdc pe secvente
		/// de lungime w, pe linii
		for (i = 1; i <= m; i++)
			for (j = 1; j + w - 1 <= n; j++) 
			{
				e = E[w];
				L[i][j] = cmmdc(D[e][i][j], D[e][i][j + w - (1 << e)]);
			}
		/// aplicam asupra lui L (care practic a contractat
		/// rezultatul de pe w coloane in una singura) acelasi
		/// rationament dar pe coloane
		/// obtinem in D cmmdc pe secvente din L
		/// de lungime putere de 2, pe coloane
		for (i = 1; i <= m; i++)
			for (j = 1; j + w - 1 <= n; j++)
				D[0][i][j] = L[i][j];
		/// interogand noul D pe secvente de lungime h
		/// si luand maximul dintre rezultate,
		/// obtinem rezultatul
		for (e = 1; (1 << e) <= m; e++)
			for (j = 1; j + w - 1 <= n; j++)
				for (i = 1; i <= m; i++) 
				{
					D[e][i][j] = D[e - 1][i][j];
					if (i + (1 << (e - 1)) <= m)
						D[e][i][j] = cmmdc(D[e][i][j],
							D[e - 1][i + (1 << (e - 1))][j]);
				}
		for (j = 1; j + w - 1 <= n; j++)
			for (i = 1; i + h - 1 <= m; i++) 
			{
				e = E[h];
				sol = max(sol, cmmdc(D[e][i][j],
					           D[e][i + h - (1 << e)][j]));
			}
		fout << "Case #" << t << ": " << sol << "\n";
	}
	return 0;
}
