// dp, dfs
// 1. ������ dp �迭�� �̿��Ѵ�. ������, ������
// 2. dfs�� ���� �����ϸ�, �������� ���� ��� �������� �����ȴ�.
//    ������¥���� �ִ� ��� �������� �ϳ� ���̸� �����Ѵ�.
// 3. ������ Ž���ߴ� �迭�� ��� �ش� dp ���� ��ȯ�Ѵ�.
// �޸� : 1992 KB, �ð� 0 ms

#include<iostream>
using namespace std;
int n;
long long dp[31][31]; // ���� ������, ������
long long dfs(int w, int h) {
	if (dp[w][h] != 0) return dp[w][h];
	if (w == 0) return 1;
	dp[w][h] += dfs(w - 1, h + 1); // �������� �Դ� ��� w�� ���̰� h�� �ø���.
	if (h > 0) dp[w][h] += dfs(w, h - 1); // �������� �Դ� ���
	return dp[w][h];
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while (1) {
		cin >> n;
		if (n == 0) break;
		cout << dfs(n, 0) << "\n"; // ������ ¥���� �־��ش�.
	}
}