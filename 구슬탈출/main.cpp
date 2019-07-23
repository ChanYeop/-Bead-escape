#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX_V 1001

struct info {
	int rx, ry, bx, by, count;
};

vector< vector<char> > v(MAX_V, vector<char>(MAX_V, 0));
//int go[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
const int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 };
queue<info> q;
bool check[10][10][10][10];

void move(int &x, int &y, int &c, int gox, int goy) {
	while (v[x+gox][y+goy] != '#' && v[x][y] != 'O') {
		x += gox;
		y += goy;
		c++;
	}
}

int BFS() {
	while (!q.empty()) {
		int rx = q.front().rx;
		int ry = q.front().ry;
		int bx = q.front().bx;
		int by = q.front().by;
		int count = q.front().count;
		q.pop();
		if (count >= 10) break;
		for (int i = 0; i < 4; i++) {
			int crx = rx; int cry = ry; int cbx = bx; int cby = by; int ccount = count+1;
			int rct = 0; int bct = 0;
			move(crx, cry, rct,dx[i], dy[i]);
			move(cbx, cby, bct, dx[i], dy[i]);

			if (v[cbx][cby] == 'O') continue;
			if (v[crx][cry] == 'O') {
				cout << ccount << endl;
				return 0;
			}
			if (crx == cbx && cry == cby) {
				if (rct > bct) {
					crx -= dx[i];
					cry -= dy[i];
				}
				else {
					cbx -= dx[i];
					cby -= dy[i];
				}
			}
			if (check[crx][cry][cbx][cby])continue;
			else {
				check[crx][cry][cbx][cby] = true;
				q.push({ crx,cry,cbx,cby,ccount });
			}
		}
	}
	cout << "-1" << endl;
}

int main() {
	int a, b;
	char c;
	cin >> a >> b;
	int rx, ry, bx, by;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			cin >> c;
			if (c == 'R') {
				rx = i;
				ry = j;
			}
			else if (c == 'B') {
				bx = i;
				by = j;
			}
			v[i][j] = c;
		}
	}
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			cout << v[i][j];
		}
		cout << endl;
	}
	q.push({ rx, ry, bx, by, 0 });
	check[rx][ry][bx][by] = true;
	BFS();
	return 0;
}