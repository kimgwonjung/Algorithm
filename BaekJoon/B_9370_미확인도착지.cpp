// ���ͽ�Ʈ��

// 1. ������ �ؼ��غ��� ������������ �ĺ��������� ���� �������� g, h ������ ������ ������ ��θ� ã�� �����̴�.
// 2. ������������ ���ͽ�Ʈ�� �˰����� �̿��Ͽ� �ִܰŸ��� ã�Ƴ�����.
// 3. node Ŭ������ Ȯ���ϸ� ������ ����, �Ÿ� �׸��� flag�� �����Ѵ�.
//    flag�� ��� ó�� ���� false�̸� g�� h������ ������ ���� ��� true�� �ٲ��ش�.
// 4. �������� �����Ͽ��� �� �ش� flag�� true�� ��� ������ ���� ����̴�.
// 5. flag�� true�� �ĺ������� �������� �����Ѵ�.

// �޸� : 6980 KB, �ð� : 48 ms

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int T, n, m, t, s, g, h, a, b, d, x;
class node {
public:
	int n, dist;
	bool flag; //g�� h ���̸� �������� �Ǵ� ����
}no;
vector<node> map[2001];
vector<int> answer;
bool visit[2001], predict_d[2001];

class cmp { // �켱���� ť cmp
public:
	bool operator()(node n1, node n2) { 
		if (n1.dist == n2.dist) {
			if (n1.flag) return false;
			if (n2.flag) return true;
			else return false;
		}
		else return n1.dist > n2.dist;// �Ÿ��� ������
	}
};

void init() {
	for (int i = 1; i <= n; i++) {
		visit[i] = false; predict_d[i] = false;
		map[i].clear();
	}
	answer.clear();
}

void dijkstra() {
	priority_queue<node, vector<node>, cmp> pq;
	pq.push({ s,0,false });
	while (!pq.empty()) {
		int cur_n = pq.top().n, dist = pq.top().dist; bool flag = pq.top().flag;
		pq.pop();
		if (visit[cur_n]) continue;
		if (predict_d[cur_n]) {
			if (flag)answer.push_back(cur_n);
		}
		visit[cur_n] = true;
		for (int i = 0; i < map[cur_n].size(); i++) {
			if (visit[map[cur_n][i].n]) continue; // �̹� �湮������
			node new_node; new_node.flag = flag;
			if (cur_n == g && map[cur_n][i].n == h) new_node.flag = true;
			else if (cur_n == h && map[cur_n][i].n == g) new_node.flag = true;
			new_node.n = map[cur_n][i].n, new_node.dist = dist + map[cur_n][i].dist;
			pq.push(new_node);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> n >> m >> t >> s >> g >> h;
		init();
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> d;
			no.n = b, no.dist = d;
			map[a].push_back(no);
			no.n = a;
			map[b].push_back(no);
		}
		for (int i = 0; i < t; i++) {
			cin >> x;
			predict_d[x] = true;
		}
		dijkstra();
		sort(answer.begin(), answer.end());
		for (int i = 0; i < answer.size(); i++) {
			cout << answer[i] << " ";
		}
		cout << "\n";
	}
}