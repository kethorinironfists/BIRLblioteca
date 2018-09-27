//retorna area maxima em um histograma

ll area(vi v) {
	ll ret = 0;
	stack<int> s;
	v.insert(v.begin(), -1);
	v.insert(v.end(), -1);
	s.push(0);

	int n = v.size();
	for(int i = 0; i < n; i++) {
		while (v[s.top()] > v[i]) {
			ll h = v[s.top()]; s.pop();
			ret = max(ret, h * (i - s.top() - 1));
		}
		s.push(i);
	}
  
	return ret;
}
