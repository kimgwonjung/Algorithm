//1. bfs를 통해 손님과 목적지 사이의 최단거리를 구해준다.
//2. 손님, 목적지의 좌표와 최단거리를 저장하여 사용
//3. 처음 택시 출발 지점부터 손님의 수 만큼 bfs를 반복하여 가장 가까운 거리부터 처리한다.
//4. 택시로부터 손님까지 거리가 같은 경우가 생길 수 있으니 정렬을 통하여 먼저 가야할 손님을 찾는다.
//5. 잔여 가스로 이동이 가능한지 확인 후 가능하면 계속 진행하며 불가능 할 경우 멈춰준다.
//메모리 : 2124 KB , 시간 : 8 ms

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

int bfs(int sx, int sy, int ex, int ey) { // 사람과 목적지 사이의 최단거리를 구하기 위해서
	init(); // 초기화
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
	return -1; // 도달하지 못한 경우가 생길수도 있다.
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
	for (int i = 0; i < m; i++) { // 사람 수 만큼 bfs를 돌려준다.
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
		if (taxi_v.empty()) return -1; // taxi가 갈곳이 없다.
		sort(taxi_v.begin(), taxi_v.end(), cmp); // 가장 앞에 있는 벡터가 거리가 가장 짧고 인덱스가 낮은 위치
		int cur_idx = taxi_v.front().idx, cur_dist = taxi_v.front().dist;
		int cur_x = v[cur_idx - 1].p_x, cur_y = v[cur_idx - 1].p_y;
		map[cur_y][cur_x] = 0; // 택시가 갈 곳의 위치를 0으로 바꿔준다.
		if (cur_dist + v[cur_idx - 1].dist > gas) return -1; // 택시가 사람을 태우고 도착지점으로 가는 거리가 gas보다 클 경우 -1
		gas -= cur_dist + v[cur_idx - 1].dist;
		gas += v[cur_idx - 1].dist * 2; // 가스를 두배로 채운다.
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
			if (map[i][j] == 1) map[i][j] = -1; // map에 1은 벽이다. 그 위치를 사람으로 쓰기 위해 벽을 -1로 변환
		}
	}
	cin >> taxi_y >> taxi_x;
	for (int i = 1; i <= m; i++) {
		cin >> p.p_y >> p.p_x >> p.e_y >> p.e_x;
		map[p.p_y][p.p_x] = i; // map에 그 위치를 사람으로 변환
		p.dist = bfs(p.p_x, p.p_y, p.e_x, p.e_y);
		v.push_back(p);
		if (p.dist == -1) { // 애초에 도달하지 못할 경우
			cout << "-1" << "\n";
			return 0;
		}
	}
	cout << taxi_bfs();
}