// 다익스트라

// 1. 문제를 해석해보면 시작지점에서 후보지점까지 가는 과정에서 g, h 사이의 간선을 지나는 경로를 찾는 문제이다.
// 2. 시작지점에서 다익스트라 알고리즘을 이용하여 최단거리를 찾아나간다.
// 3. node 클래스를 확인하면 도착할 정점, 거리 그리고 flag가 존재한다.
//    flag의 경우 처음 값은 false이며 g와 h사이의 간선을 지난 경우 true로 바꿔준다.
// 4. 목적지에 도착하였을 때 해당 flag가 true인 경우 간선을 지난 경우이다.
// 5. flag가 true인 후보지들을 오름차순 정렬한다.

// 메모리 : 6980 KB, 시간 : 48 ms

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int T, n, m, t, s, g, h, a, b, d, x;
class node {
public:
	int n, dist;
	bool flag; //g와 h 사이를 지났는지 판단 여부
}no;
vector<node> map[2001];
vector<int> answer;
bool visit[2001], predict_d[2001];

class cmp { // 우선순위 큐 cmp
public:
	bool operator()(node n1, node n2) { 
		if (n1.dist == n2.dist) {
			if (n1.flag) return false;
			if (n2.flag) return true;
			else return false;
		}
		else return n1.dist > n2.dist;// 거리가 작은거
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
			if (visit[map[cur_n][i].n]) continue; // 이미 방문했으면
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