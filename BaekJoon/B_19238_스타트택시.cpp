//1. bfs�� ���� �մ԰� ������ ������ �ִܰŸ��� �����ش�.
//2. �մ�, �������� ��ǥ�� �ִܰŸ��� �����Ͽ� ���
//3. ó�� �ý� ��� �������� �մ��� �� ��ŭ bfs�� �ݺ��Ͽ� ���� ����� �Ÿ����� ó���Ѵ�.
//4. �ý÷κ��� �մԱ��� �Ÿ��� ���� ��찡 ���� �� ������ ������ ���Ͽ� ���� ������ �մ��� ã�´�.
//5. �ܿ� ������ �̵��� �������� Ȯ�� �� �����ϸ� ��� �����ϸ� �Ұ��� �� ��� �����ش�.
//�޸� : 2124 KB , �ð� : 8 ms

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int n, m, gas, map[21][21], dx[4] = { 0,0,-1,1 }, dy[4] = {-1,1,0,0};
int taxi_y, taxi_x;
bool visit[21][21];
class point {
public:
	int p_y, p_x, e_y, e_x, dist;
}p;
vector<point> v;

class node {
public:
	int x, y, cnt;
};

void init() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			visit[i][j] = false;
		}
	}
}

int bfs(int sx, int sy, int ex, int ey) { // ����� ������ ������ �ִܰŸ��� ���ϱ� ���ؼ�
	init(); // �ʱ�ȭ
	queue<node> q;
	q.push({ sx,sy,0 }); visit[sy][sx] = true;
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y, cnt = q.front().cnt;
		q.pop();
		if (x == ex && y == ey) return cnt;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
			if (map[ny][nx] == -1 || visit[ny][nx]) continue;
			q.push({ nx,ny,cnt + 1 }); visit[ny][nx] = true;
		}
	}
	return -1; // �������� ���� ��찡 ������� �ִ�.
}

class taxi_dest {
public:
	int idx, dist;
};

bool cmp(taxi_dest t1, taxi_dest t2) {
	if (t1.dist == t2.dist) {
		if (v[t1.idx - 1].p_y == v[t2.idx - 1].p_y) return v[t1.idx - 1].p_x < v[t2.idx - 1].p_x;
		else return v[t1.idx - 1].p_y < v[t2.idx - 1].p_y;
	}
	else return t1.dist < t2.dist;
}

int taxi_bfs() {
	int x_ = taxi_x, y_ = taxi_y;
	queue<node> q; vector<taxi_dest> taxi_v;
	for (int i = 0; i < m; i++) { // ��� �� ��ŭ bfs�� �����ش�.
		init();
		q.push({ x_,y_,0 }); visit[y_][x_] = true;
		while (!q.empty()) {
			int x = q.front().x, y = q.front().y, cnt = q.front().cnt;
			q.pop();
			if (1 <= map[y][x] && map[y][x] <= m) {
				taxi_dest t;
				t.idx = map[y][x], t.dist = cnt;
				taxi_v.push_back(t);
			}
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i], ny = y + dy[i];
				if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
				if (map[ny][nx] == -1 || visit[ny][nx]) continue;
				q.push({ nx,ny,cnt + 1 }); visit[ny][nx] = true;
			}
		}
		if (taxi_v.empty()) return -1; // taxi�� ������ ����.
		sort(taxi_v.begin(), taxi_v.end(), cmp); // ���� �տ� �ִ� ���Ͱ� �Ÿ��� ���� ª�� �ε����� ���� ��ġ
		int cur_idx = taxi_v.front().idx, cur_dist = taxi_v.front().dist;
		int cur_x = v[cur_idx - 1].p_x, cur_y = v[cur_idx - 1].p_y;
		map[cur_y][cur_x] = 0; // �ýð� �� ���� ��ġ�� 0���� �ٲ��ش�.
		if (cur_dist + v[cur_idx - 1].dist > gas) return -1; // �ýð� ����� �¿�� ������������ ���� �Ÿ��� gas���� Ŭ ��� -1
		gas -= cur_dist + v[cur_idx - 1].dist;
		gas += v[cur_idx - 1].dist * 2; // ������ �ι�� ä���.
		taxi_v.clear();
		x_ = v[cur_idx - 1].e_x, y_ = v[cur_idx - 1].e_y;
	}
	return gas;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> gas;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) map[i][j] = -1; // map�� 1�� ���̴�. �� ��ġ�� ������� ���� ���� ���� -1�� ��ȯ
		}
	}
	cin >> taxi_y >> taxi_x;
	for (int i = 1; i <= m; i++) {
		cin >> p.p_y >> p.p_x >> p.e_y >> p.e_x;
		map[p.p_y][p.p_x] = i; // map�� �� ��ġ�� ������� ��ȯ
		p.dist = bfs(p.p_x, p.p_y, p.e_x, p.e_y);
		v.push_back(p);
		if (p.dist == -1) { // ���ʿ� �������� ���� ���
			cout << "-1" << "\n";
			return 0;
		}
	}
	cout << taxi_bfs();
}