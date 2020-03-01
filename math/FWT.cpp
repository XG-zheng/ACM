void FWT(int *a, int len, const int P,int o = 1) {  // o=-1 UFWT
	const int inv2 = P + 1 >> 1;
	for (int k = 0; 1 << k < len; ++k) rep(i, 0, len) if (~i >> k & 1) {
		int j = i ^ (1 << k), x, y;
		x = (a[i] + a[j]) % P, y = (a[i] - a[j] + P) % P; // xor
		if (o == -1) x = (ll)x * inv2 % P, y = (ll)y * inv2 % P;
		//x = (a[i] + a[j]) % P, y = a[j]; // and
		//if (o == -1) x = (a[i] - a[j] + P) % P;
		//x = a[i], y = (a[i] + a[j]) % P; // or
		//if (o == -1) y = (a[j] - a[i] + P) % P;
		a[i] = x, a[j] = y;
	}
}
