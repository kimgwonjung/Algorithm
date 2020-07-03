// 메모이제이션

// 1. 각 좌표에 대해서 dfs를 반복한다.
// 2. 한 번 탐색한 위치는 같은 값을 반복하므로 dp 배열에 값을 저장한다.
// 3. 해당 위치가 탐색한 곧인 경우 dp[y][x]를 반환한다.
//    아직 방문을 하지 않은 배열인 경우 그 위치는 초기값이 1이다.
//    4 방향 탐색을 진행하며, 그 중 가장 큰 값을 저장한다.
//    그 위치의 값은 4방향 탐색 중 나온 가장 큰 값이다.

// 메모리 : 4008 KB, 시간 36 ms

#include<iostream>
#include<algorithm>
using namespace std;

int n, map[500][500], dp[500][500], dx[4] = { 0,0,-1,1 }, dy[4] = { -1,1,0,0 };

int dfs(int y, int x) {
	if (dp[y][x] != 0) return dp[y][x];// 이미 한번 방문을 한 경우
	dp[y][x] = 1; // 방문을 안했을 경우 그 위치의 초기값은 1
	int max_value = dp[y][x];
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue; // 범위 밖으로 넘어간 경우
		if (map[ny][nx] <= map[y][x]) continue; // 크기가 작은경우
		max_value = max(max_value, dp[y][x] + dfs(ny, nx)); // 4방향 dfs를 통해 가장 큰 값을 찾는다.
	}
	dp[y][x] = max_value;
	return dp[y][x];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	int answer = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = dfs(i, j);
			answer = max(answer, dp[i][j]);
		}
	}
	cout << answer << "\n";
}