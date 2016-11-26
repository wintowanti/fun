/*
dex form 0 to n-1 ans is double of
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 250;
// ���鼯ά��
int belong[N];
int findb(int x) {
	return belong[x] == x ? x : belong[x] = findb(belong[x]);
}
void unit(int a, int b) {
	a = findb(a);
	b = findb(b);
	if (a != b) belong[a] = b;
}
int match[N],n;
vector<int> e[N];
int Q[N], rear;
int next[N], mark[N], vis[N];
// �����㷨��ĳ�׶���������������x, y�������������r
int LCA(int x, int y) {
	static int t = 0; t++;
	while (true) {
		if (x != -1) {
			x = findb(x); // ��Ҫ��Ӧ����Ӧ�Ļ���ȥ
			if (vis[x] == t) return x;
			vis[x] = t;
			if (match[x] != -1) x = next[match[x]];
			else x = -1;
		}
		swap(x, y);
	}
}
void group(int a, int p) {
	while (a != p) {
		int b = match[a], c = next[b];

		// next������������ǻ����е�·���ģ��ۺ�match�������ã�ʵ�����γ���
		// ˫����������(x, y)��ƥ��ģ�next[x]��next[y]�Ϳ���ָ���������ˡ�
		if (findb(c) != p) next[c] = b;

		// �滷�еĵ㶼�л��������ҵ�ƥ�䣬���Զ�Ҫ��ǳ�S�͵�ӵ�������ȥ��
		// ���ڵ�ƥ�����ѱ��ͣ������Щ�����ֻ����ƥ��ɹ�һ���㣬��aug��
		// ÿ��ƥ�䵽һ�����break��ֹ�˵�ǰ�׶ε������������½׶εı������
		// �������ģ�����������Ϊ�˱�֤��һ�㡣
		if (mark[b] == 2) mark[Q[rear++] = b] = 1;
		if (mark[c] == 2) mark[Q[rear++] = c] = 1;

		unit(a, b); unit(b, c);
		a = c;
	}
}
// ����
void aug(int s) {
	for (int i = 0; i < n; i++) // ÿ���׶ζ�Ҫ���±��
		next[i] = -1, belong[i] = i, mark[i] = 0, vis[i] = -1;
	mark[s] = 1;
	Q[0] = s; rear = 1;
	for (int front = 0; match[s] == -1 && front < rear; front++) {
		int x = Q[front]; // ����Q�еĵ㶼��S�͵�
		for (int i = 0; i < (int)e[x].size(); i++) {
			int y = e[x][i];
			if (match[x] == y) continue; // x��y��ƥ�䣬����
			if (findb(x) == findb(y)) continue; // x��yͬ��һ�仨������
			if (mark[y] == 2) continue; // y��T�͵㣬����
			if (mark[y] == 1) { // y��S�͵㣬�滷����
				int r = LCA(x, y); // rΪ��i��j��s��·���ϵĵ�һ�������ڵ�
				if (findb(x) != r) next[x] = y; // r��x����ͬһ�����䣬next��ǻ�����·��
				if (findb(y) != r) next[y] = x; // r��y����ͬһ�����䣬next��ǻ�����·��

				// ������r -- x - y --- r���滷���ɵ㣬r��Ϊ������ı�ǽڵ㣬�൱�������еĳ����ڵ�
				group(x, r); // ��·��r --- xΪ��
				group(y, r); // ��·��r --- yΪ��
			}
			else if (match[y] == -1) { // y���ɣ��������㣬R12������
				next[y] = x;
				for (int u = y; u != -1; ) { // ������ȡ��
					int v = next[u];
					int mv = match[v];
					match[v] = u, match[u] = v;
					u = mv;
				}
				break; // �����ɹ����˳�ѭ����������һ�׶�
			}
			else { // ��ǰ�����Ľ�����+y+match[y]�γ��µĽ���������match[y]���������Ϊ���ѽڵ�
				next[y] = x;
				mark[Q[rear++] = match[y]] = 1; // match[y]Ҳ��S�͵�
				mark[y] = 2; // y��ǳ�T��
			}
		}
	}
}
int g[N][N];
int get_match(){
    for(int i=0;i<n;i++) e[i].clear();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]>0) e[i].push_back(j);
        }
    }
    int ans=0;
    memset(match,-1,sizeof(match));
    for(int i=0;i<n;i++){
        if(match[i]==-1) aug(i);
    }
    for(int i=0;i<n;i++){
        if(match[i]!=-1) ans++;
    }
    return ans/2;
}
/*
4 3
1 3
2 3
2 4
*/