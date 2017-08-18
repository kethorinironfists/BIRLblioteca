#include <iostream>
#include <cstring>

using namespace std;

const int tam=2;

typedef struct matriz {
	int m[tam][tam];
	
	void ini(int x) {
		for(int i=0; i<tam; i++) for(int j=0; j<tam; j++) {
			m[i][j] = (i == j) ? x : 0;
		}
	}

	void le(int n) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				cin>>m[i][j];
			}
		}
	}
} matriz;

matriz mult(matriz &m1, matriz &m2) {
	matriz r;
	r.ini(0);
	for(int i=0; i<tam; i++) {
		for(int j=0; j<tam; j++) {
			for(int k=0; k<tam; k++) {
				r.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return r;
}

matriz eleva(matriz m, int pot) {
	matriz r;
	r.ini(1);
	while(pot) {
		if(pot&1)	r = mult(r, m);
		m = mult(m, m);
		pot >>= 1;
	}
	return r;
}

int main() {
	matriz m;
	m.le(tam);
	int pot;
	cin>>pot;
	m = eleva(m, pot);
	cout<<m.m[1][0]<<endl;
	return 0;
}
