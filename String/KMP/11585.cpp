#include <iostream>
#include <algorithm>
using namespace std;

int n, cnt;
string roulette, pat;
int failure[1000000];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

void fail() {
	int j;
	int len = pat.length();

	failure[0] = -1;
	for (int i = 1; i < len; i++) {
		j = failure[i - 1];

		while (j >= 0 && (pat[i] != pat[j + 1]))
			j = failure[j];

		if (pat[i] == pat[j + 1]) failure[i] = j + 1;
		else failure[i] = -1;
	}
}

void kmp() {
	int i = 0, j = 0;
	int lenr = roulette.length();
	int lenp = pat.length();

	for (int i = 0; i < lenr; i++) {
		while (j > 0 && roulette[i] != pat[j]) j = failure[j - 1] + 1;
		if (roulette[i] == pat[j]) j++;
		if (j == lenp) {
			cnt++;
			j = failure[j - 1] + 1;
		}
	}
}

int main() {
	cin >> n;
	char c;
	for (int i = 0; i < n; i++) {
		cin >> c;
		roulette.append(1, c);
	}
	for (int i = 0; i < n; i++) {
		cin >> c;
		pat.append(1, c);
	}
	roulette.append(roulette);
	roulette.pop_back();
	fail();
	kmp();
	int num = gcd(n, cnt);
	cout << cnt / num << "/" << n / num;
}
