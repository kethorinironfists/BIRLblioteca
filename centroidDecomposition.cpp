//CENTROID DECOMPOSITION - BY: NICAO
//usando meu template bacana
//Grafo g_in: grafo de entrada
//Grafo g: arvore de centroide
//raiz: raiz da arvore de centroide
//pai[u]: pai de u em g
//nivel[u]: altura de u na arvore g
//dis[k][u]: distancia de u ao k-esimo centroide ancestral de u

const int N = 100050;
const int MAXLOG = 20;

int raiz, n;
int pai[N], sz[N], dist[MAXLOG][N], nivel[N];

vi g_in[N], g[N];

set < int > jafoi;

void dfs(int u, int p, int dis, int nvl) {
	sz[u] = 1;
	if(nvl != -1) dist[nvl][u] = dis;
	for(int v: g_in[u]) {
		if(v == p or jafoi.count(v)) continue;
		dfs(v, u, dis+1, nvl);
		sz[u] += sz[v];
	}
}

int acha(int u, int p, int tot) {
	int mx = tot - sz[u];
	for(int v: g_in[u]) {
		if(v == p or jafoi.count(v)) continue;
		mx = max(mx, sz[v]);
	}

	if(mx <= tot/2) return u;
	else {
		int ret = -1;
		for(int v: g_in[u]) {
			if(v == p or jafoi.count(v)) continue;
			int aux = acha(v, u, tot);
			if(aux != -1) return aux;
		}
		return ret;
	}
}

void novo_centroide(int u, int last, int nvl) {
	dfs(u, -1, 1, nvl-1);

	int novo = acha(u, -1, sz[u]);

	if(last == -1) {
		raiz = novo;
		pai[novo] = -1;
		dist[nvl][novo] = 0;
	}
	else {
		g[last].pb(novo);
		pai[novo] = last;
	}

	nivel[novo] = nvl;
	jafoi.insert(novo);

	for(int v: g_in[novo]) {
		if(jafoi.count(v)) continue;
		novo_centroide(v, novo, nvl+1);
	}
}

void checa(int u, int p) {
	printf("u = %d, pai[u] = %d\n", u, pai[u]);
	for(int v: g[u]) {
		if(v != p) checa(v, u);
	}
}

void centroid_decomposition(int c) {
	novo_centroide(c, -1, 0);
}

/* The End */