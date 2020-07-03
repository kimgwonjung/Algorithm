// �޸������̼�

// 1. �� ��ǥ�� ���ؼ� dfs�� �ݺ��Ѵ�.
// 2. �� �� Ž���� ��ġ�� ���� ���� �ݺ��ϹǷ� dp �迭�� ���� �����Ѵ�.
// 3. �ش� ��ġ�� Ž���� ���� ��� dp[y][x]�� ��ȯ�Ѵ�.
//    ���� �湮�� ���� ���� �迭�� ��� �� ��ġ�� �ʱⰪ�� 1�̴�.
//    4 ���� Ž���� �����ϸ�, �� �� ���� ū ���� �����Ѵ�.
//    �� ��ġ�� ���� 4���� Ž�� �� ���� ���� ū ���̴�.

// �޸� : 4008 KB, �ð� 36 ms

#include<iostream>
#include<algorithm>
using namespace std;

int n, map[500][500], dp[500][500], dx[4] = { 0,0,-1,1 }, dy[4] = { -1,1,0,0 };

int dfs(int y, int x) {
	if (dp[y][x] != 0) return dp[y][x];// �̹� �ѹ� �湮�� �� ���
	dp[y][x] = 1; // �湮�� ������ ��� �� ��ġ�� �ʱⰪ�� 1
	int max_value = dp[y][x];
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue; // ���� ������ �Ѿ ���
		if (map[ny][nx] <= map[y][x]) continue; // ũ�Ⱑ �������
		max_value = max(max_value, dp[y][x] + dfs(ny, nx)); // 4���� dfs�� ���� ���� ū ���� ã�´�.
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