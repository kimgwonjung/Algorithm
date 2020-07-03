// dp, dfs
// 1. 이차원 dp 배열을 이용한다. 한조각, 반조각
// 2. dfs를 통해 진행하며, 한조각을 먹은 경우 반조각이 생성된다.
//    반조각짜리가 있는 경우 반조각을 하나 줄이며 진행한다.
// 3. 이전에 탐색했던 배열인 경우 해당 dp 값을 반환한다.
// 메모리 : 1992 KB, 시간 0 ms

#include<iostream>
using namespace std;
int n;
long long dp[31][31]; // 각각 한조각, 반조각
long long dfs(int w, int h) {
	if (dp[w][h] != 0) return dp[w][h];
	if (w == 0) return 1;
	dp[w][h] += dfs(w - 1, h + 1); // 한조각을 먹는 경우 w를 줄이고 h를 늘린다.
	if (h > 0) dp[w][h] += dfs(w, h - 1); // 반조각을 먹는 경우
	return dp[w][h];
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while (1) {
		cin >> n;
		if (n == 0) break;
		cout << dfs(n, 0) << "\n"; // 한조각 짜리를 넣어준다.
	}
}