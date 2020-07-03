//�ùķ��̼� ����
//1. �־��� ���ǵ��� ���� ����� ��ǥ�� ����, ����� �켱���� ������ ����������
//   map���� �ش� ��ġ�� ����ȣ, ���� ī��Ʈ�� ����������
//   falg�� �ش� �ð��� ������ ����� ���� ī��Ʈ�� ������ �ʰ� �ϱ� ���� ����
//
//2. �� �Ѹ��� ���������� �ݺ��ؼ� �����Ѵ�.
//   ������ ������ ���� "���� ������ ĭ �� �ƹ� ������ ���� ĭ�� �������� ��´�. �׷� ĭ�� ������ �ڽ��� ������
//   �ִ� ĭ�� �������� ��´�." ��� �����ִ�.
//   ���� ������ ĭ �߿� �ƹ� ������ ���� ĭ�� �켱���� ������� Ȯ�� ��, �������� ���� ���
//   �ڽ��� ������ �ִ� ĭ�� �켱������ Ž���Ͽ� �̵��ϴ� ������ �ؼ��ߴ�.
//   ���� ���� 4���� Ž���� ���� ī��Ʈ�� ���ְ� ī��Ʈ�� 4�� �� ��� �ڽ��� ������ �ִ� ��ġ�� 4���� Ž���Ͽ� ã�� �ȴ�.
//
//3. �� ������ ���� ��� ������ map�� ����� ������ ��� ������ ������ �������ش�.
//   �̵��ϴ� �������� �� ��ġ�� ��찡 ����µ� ���� ��ȣ�� �� ��Ƴ��� �ȴ�.
//   cnt_map�� ���� �ش� ��ǥ�� ����� �ε����� ������ �����Ͽ�����, �̸� ���� ����� ���� ���� Ȯ�� �� �� �ִ�.
//   �ش� ��ǥ�� ����� ������ 2�� �̻��� ��� ������ ���� ���� ��ȣ�� �� �����ش�.
//
//4. �� �� �� �̵������� ���� ī��Ʈ�� ���ҽ�Ų��. �̶� �ش� �ð��� �̵��� ����� ������ �����ϸ� �ȵǱ� ������
//   flag�� false�� �͸� ���� ��Ų��.
//   ���� �ð��� ���۵Ǹ� ���� �ð��� �̵��� ��� ��ġ�� flag�� true���� false�� �ٲ��ش�.

// �޸� : 2176 KB, �ð� 4 ms
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, m, k, dx[5] = { 0,0,0,-1,1 }, dy[5] = { 0,-1,1,0,0 };

class Map {
public:
	int shark_num, small_cnt;
	bool flag; // �� ó�� �����̰� ���� �� ������ �����ؼ��� �ȵȴ�.
};

class point {
public:
	int y, x, dir;
}p;
vector<point> shark_point[401]; // ���� �����ϴ� ����� ��ġ
class point2 {
public:
	int idx, dir;
};
Map map[21][21];
int shark_move[401][5][4]; // ���� 400�������� �����ϸ� ������ �����¿쿡 ���� 4���� �켱������ ����
vector<point2> cnt_map[21][21]; // �� �� Ÿ�� �̵� �� �ش� �ʿ� ����� ����
void small_count_down() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].small_cnt >= 1 && !map[i][j].flag) { // ���� ī��Ʈ�� ������, flag�� false�� ���
				map[i][j].small_cnt -= 1; // ���� ����
				if (map[i][j].small_cnt == 0) map[i][j].shark_num = 0; // 0�̸� ���ش�.
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
	while (1 < total_cnt) { // �� �Ѹ��� ���������� �����Ѵ�.
		if (time >= 1000) return -1;
		convert_flag(); // true ������ false�� �ٲ��ش�.
		for (int i = 1; i <= m; i++) { // ������ȣ�� ������ �̵��� ��Ų��. ����� ��ǥ�� 0,0�̸� �̹� ���� ����̴�.
			if (shark_point[i][0].x == 0 && shark_point[i][0].y == 0) continue; // ��ǥ�� 0,0�̸� �о�
			int x = shark_point[i][0].x, y = shark_point[i][0].y, cur_dir = shark_point[i][0].dir; 
			int dir_cnt = 0;// �� �������� �Ǵ� ����
			for (int j = 0; j < 4; j++) {
				int nx = x + dx[shark_move[i][cur_dir][j]], ny = y + dy[shark_move[i][cur_dir][j]];
				if (nx <= 0 || nx > n || ny <= 0 || ny > n) { dir_cnt++; continue; } // ������ �Ѿ ���
				if (map[ny][nx].shark_num != 0 && map[ny][nx].small_cnt <= k) { dir_cnt++; continue; }
				if (map[ny][nx].shark_num == 0) { // �̵��� ���, �� ��쿡�� �� ������ �� �ִ�.
					cnt_map[ny][nx].push_back({ i, shark_move[i][cur_dir][j] }); // cnt_map�� ��� ��ȣ�� �־��ش�.
					break;
				}
				dir_cnt++;
			}
			if (dir_cnt == 4) { // 4������ Ž���ص� ������ ���� ��� �Դ����� ���ư���.
				for (int j = 0; j < 4; j++) {
					int nx = x + dx[shark_move[i][cur_dir][j]], ny = y + dy[shark_move[i][cur_dir][j]];
					if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;// ������ �Ѿ ���
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
		small_count_down();//����ī���͸� ����
		time++;
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