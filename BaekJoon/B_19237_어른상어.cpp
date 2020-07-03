#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, m, k, dx[5] = { 0,0,0,-1,1 }, dy[5] = { 0,-1,1,0,0 };

class Map {
public:
	int shark_num, small_cnt;
	bool flag; // 상어가 처음 움직이고 났을 땐 냄새가 감소해서는 안된다.
};
Map map[21][21];
int shark_move[401][5][4]; // 상어는 400마리까지 존재하며 각각의 상하좌우에 대해 4가지 우선순위가 존재
class point {
public:
	int y, x, dir;
}p;
vector<point> shark_point[401]; // 실제 존재하는 상어의 위치
class point2 {
public:
	int idx, dir;
};
vector<point2> cnt_map[21][21];
void small_count_down() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].small_cnt >= 1 && !map[i][j].flag) { // 냄새 카운트가 있으며, flag가 false인 경우
				map[i][j].small_cnt -= 1; // 냄새 감소
				if (map[i][j].small_cnt == 0) map[i][j].shark_num = 0; // 0이면 없앤다.
			}
		}
	}
}
void convert_flag() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].flag) map[i][j].flag = false;
		}
	}
}
bool cmp(point2 p1, point2 p2) {
	return p1.idx < p2.idx;
}
int simulation() {
	int total_cnt = m, time = 0;
	while (1 < total_cnt) { // 상어가 한마리 남을때까지 지속한다.
		if (time >= 1000) return -1;
		convert_flag(); // true 값들을 false로 바꿔준다.
		for (int i = 1; i <= m; i++) { // 작은번호의 상어부터 이동을 시킨다. 상어의 좌표가 0,0이면 이미 먹힌 상어이다.
			if (shark_point[i][0].x == 0 && shark_point[i][0].y == 0) continue; // 좌표가 0,0이면 패쓰
			int x = shark_point[i][0].x, y = shark_point[i][0].y, cur_dir = shark_point[i][0].dir; 
			int dir_cnt = 0;// 상어가 먹혔는지 판단 여부
			for (int j = 0; j < 4; j++) {
				int nx = x + dx[shark_move[i][cur_dir][j]], ny = y + dy[shark_move[i][cur_dir][j]];
				if (nx <= 0 || nx > n || ny <= 0 || ny > n) { dir_cnt++; continue; } // 범위를 넘어간 경우
				if (map[ny][nx].shark_num != 0 && map[ny][nx].small_cnt <= k) { dir_cnt++; continue; }
				if (map[ny][nx].shark_num == 0) { // 이동한 경우, 이 경우에만 상어가 먹혀질 수 있다.
					cnt_map[ny][nx].push_back({ i, shark_move[i][cur_dir][j] }); // cnt_map에 상어 번호만 넣어준다.
					break;
				}
				dir_cnt++;
			}
			if (dir_cnt == 4) { // 4방향을 탐색해도 갈곳이 없는 경우 왔던길을 돌아간다.
				for (int j = 0; j < 4; j++) {
					int nx = x + dx[shark_move[i][cur_dir][j]], ny = y + dy[shark_move[i][cur_dir][j]];
					if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;// 범위를 넘어간 경우
					if (map[ny][nx].shark_num == i) {
						map[ny][nx].shark_num = map[y][x].shark_num, map[ny][nx].small_cnt = k, map[ny][nx].flag = true;
						shark_point[i][0].x = nx, shark_point[i][0].y = ny, shark_point[i][0].dir = shark_move[i][cur_dir][j];
						break;
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (cnt_map[i][j].size() == 1) {
					map[i][j].shark_num = cnt_map[i][j].front().idx, map[i][j].small_cnt = k, map[i][j].flag = true;
					shark_point[map[i][j].shark_num][0].x = j, shark_point[map[i][j].shark_num][0].y = i, shark_point[map[i][j].shark_num][0].dir = cnt_map[i][j].front().dir;
					cnt_map[i][j].clear();
				}
				else if (cnt_map[i][j].size() > 1) {
					sort(cnt_map[i][j].begin(), cnt_map[i][j].end(),cmp);
					map[i][j].shark_num = cnt_map[i][j].front().idx, map[i][j].small_cnt = k, map[i][j].flag = true;
					shark_point[map[i][j].shark_num][0].x = j, shark_point[map[i][j].shark_num][0].y = i, shark_point[map[i][j].shark_num][0].dir = cnt_map[i][j].front().dir;
					total_cnt -= cnt_map[i][j].size() - 1;
					for (int k = 1; k < cnt_map[i][j].size(); k++) {
						shark_point[cnt_map[i][j][k].idx][0].x = 0, shark_point[cnt_map[i][j][k].idx][0].y = 0;
					}
					cnt_map[i][j].clear();
				}
			}
		}
		small_count_down();//냄새카운터를 감소
		time++;
		//cout << time << "\n";
		//for (int i = 1; i <= n; i++) {
		//	for (int j = 1; j <= n; j++) {
		//		cout << map[i][j].shark_num << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";
		//for (int i = 1; i <= n; i++) {
		//	for (int j = 1; j <= n; j++) {
		//		cout << map[i][j].small_cnt << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";
	}
	return time;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j].shark_num;
			if (map[i][j].shark_num != 0) {
				map[i][j].small_cnt = k; map[i][j].flag = true;
				p.y = i, p.x = j;
				shark_point[map[i][j].shark_num].push_back(p);
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		cin >> shark_point[i][0].dir;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> shark_move[i][j][k];
			}
		}
	}
	cout << simulation() <<"\n";
}