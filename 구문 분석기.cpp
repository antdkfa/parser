#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef pair <int, int> p;
typedef pair<p, p>pp;
vector<vector<vector<char>>> dp_table;
int N, Wlen, mid;
string W, rule[105];

void solve(string left, int l, int r, string right, char parent) {
	if (l == r) {
		printf("=>",l);
		for (int i = 0; i <= l; i++) printf("%c",W[i]);
		cout << right <<endl;
	}
	else {
		for (int i = l; i < r;i++) {
			if (dp_table[l][i].size() && dp_table[i + 1][r].size()) {
				int li_size = dp_table[l][i].size(), ir_size = dp_table[i + 1][r].size();
				for (int q = 0; q < li_size; q++) {
					for (int w = 0; w < ir_size; w++) {
						for (int j = 0; j < N; j++) {
							if (rule[j][0] == parent && dp_table[l][i][q] == rule[j][3] && dp_table[i + 1][r][w] == rule[j][4]) {
								printf("=>");
								cout << left;
								printf("%c%c", rule[j][3], rule[j][4]);
								cout << right;
								printf("\n");
								string tmp1 = "", tmp2 = "";
								tmp1 = rule[j][4] + right;
								solve(left, l, i, tmp1, rule[j][3]);
								for (int e = 0; e <= i; e++) tmp2 += W[e];
								solve(tmp2, i + 1, r, right, rule[j][4]);
								return;
							}
						}
					}
				}
			}
		}
	}
}

int main() {
	cin >> W;
	Wlen = W.size();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		string tmp;
		cin >> tmp;
		rule[i] = tmp + ' ';
	}
	dp_table.resize(105);
	for (int i = 0; i < 105; i++) dp_table[i].resize(105);
	for (int i = 0; i < Wlen; i++) for (int j = 0; j < N; j++) if (W[i] == rule[j][3]) dp_table[i][i].push_back(rule[j][0]);
	for (int i = 0; i < Wlen; i++) {
		for (int j = i; j >= 0; j--) {
			if (j != i) {
				for (int k = j; k < i; k++) {
					if (dp_table[j][k].size() && dp_table[k + 1][i].size()) {
						for (int q = 0; q < N; q++) {
							int jk_size = dp_table[j][k].size(),ki_size = dp_table[k+1][i].size();
							for (int l = 0; l < jk_size; l++) {
								for (int m = 0; m < ki_size; m++) {
									if (rule[q][3] == dp_table[j][k][l] && rule[q][4] == dp_table[k + 1][i][m]) {
										int flag = 0, ji_size = dp_table[j][i].size();
										for (int w = 0; w < ji_size; w++) if (dp_table[j][i][w] == rule[q][0]) flag = 1;
										if (!flag)dp_table[j][i].push_back(rule[q][0]);
									}
								}
							}
						}
					}

				}
			}
		}
	}
	int flag = 0;
	for (int i = 0; i < dp_table[0][Wlen - 1].size(); i++) if (dp_table[0][Wlen - 1][i] == 'S') flag = 1;
	if (!flag) printf("no\n");
	else {
		flag = 0;
		printf("yes\nS\n=>");
		for (int i = 0; i < Wlen - 1; i++) {
			if (dp_table[0][i].size() && dp_table[i + 1][Wlen - 1].size()) {
				for (int j = 0; j < N; j++) {
					if (rule[j][0] == 'S') {
						int zi_size = dp_table[0][i].size(), iWlen = dp_table[i + 1][Wlen - 1].size();
						for (int k = 0; k < zi_size; k++) {
							for (int q = 0; q < iWlen; q++) {
								if (dp_table[0][i][k] == rule[j][3] && dp_table[i + 1][Wlen - 1][q] == rule[j][4]) {
									printf("%c%c\n", rule[j][3], rule[j][4]);
									string empty = "";
									string tmp = "";
									tmp = rule[j][4];
									solve(empty, 0, i, tmp, rule[j][3]);
									tmp = "";
									for (int z = 0; z < i + 1; z++) tmp += W[z];
									solve(tmp, i + 1, Wlen - 1, empty, rule[j][4]);//소문자로 바꿔야함
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}