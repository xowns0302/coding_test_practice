#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int N, T;
int sig[101][101][4]; // sig[r][c][i] = i번째 신호

// entry_group (eg): 1=서쪽에서(동쪽이동), 2=남쪽에서(북쪽이동), 3=동쪽에서(서쪽이동), 4=북쪽에서(남쪽이동)
// (s-1)%4+1 로 신호 s의 그룹 계산

// 직진 delta + 다음 eg
int s_dr[] = {0, 0,-1, 0, 1};
int s_dc[] = {0, 1, 0,-1, 0};
int s_eg[] = {0, 1, 2, 3, 4};

// 좌회전 delta + 다음 eg
int l_dr[] = {0,-1, 0, 1, 0};
int l_dc[] = {0, 0,-1, 0, 1};
int l_eg[] = {0, 2, 3, 4, 1};

// 우회전 delta + 다음 eg
int r_dr[] = {0, 1, 0,-1, 0};
int r_dc[] = {0, 0, 1, 0,-1};
int r_eg[] = {0, 4, 1, 2, 3};

bool vis[101][101][101][4]; // vis[r][c][t][eg-1]
bool cell_vis[101][101];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> T;
    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++)
            for(int i = 0; i < 4; i++)
                cin >> sig[r][c][i];

    // (1,1)은 항상 카운트
    cell_vis[1][1] = true;

    // 초기 진입: (1,1)에 t=0, 남쪽에서 진입(eg=2)
    int init_sig = sig[1][1][0];
    int init_group = (init_sig - 1) % 4 + 1;

    queue<tuple<int,int,int,int>> q; // (r, c, t, eg)
    if(init_group == 2) {
        vis[1][1][0][1] = true;
        q.push(make_tuple(1, 1, 0, 2));
    }

    while(!q.empty()) {
        int cr = get<0>(q.front());
        int cc = get<1>(q.front());
        int ct = get<2>(q.front());
        int ceg = get<3>(q.front());
        q.pop();

        if(ct >= T) continue;

        int s = sig[cr][cc][ct % 4];
        bool can_l = (s <= 8);            // 1~8: 직진+좌회전 가능
        bool can_r = (s <= 4 || s >= 9); // 1~4, 9~12: 직진+우회전 가능

        for(int mi = 0; mi < 3; mi++) {
            if(mi == 1 && !can_l) continue;
            if(mi == 2 && !can_r) continue;

            int nr, nc, neg;
            if(mi == 0) { nr = cr+s_dr[ceg]; nc = cc+s_dc[ceg]; neg = s_eg[ceg]; }
            else if(mi == 1) { nr = cr+l_dr[ceg]; nc = cc+l_dc[ceg]; neg = l_eg[ceg]; }
            else { nr = cr+r_dr[ceg]; nc = cc+r_dc[ceg]; neg = r_eg[ceg]; }

            int nt = ct + 1;
            if(nr < 1 || nr > N || nc < 1 || nc > N) continue;
            if(nt > T) continue;

            // 다음 교차로의 신호가 진입방향과 일치하는지 확인
            int ns = sig[nr][nc][nt % 4];
            int ngroup = (ns - 1) % 4 + 1;
            if(ngroup != neg) continue;

            cell_vis[nr][nc] = true;

            if(!vis[nr][nc][nt][neg-1]) {
                vis[nr][nc][nt][neg-1] = true;
                q.push(make_tuple(nr, nc, nt, neg));
            }
        }
    }

    int count = 0;
    for(int r = 1; r <= N; r++)
        for(int c = 1; c <= N; c++)
            if(cell_vis[r][c]) count++;

    cout << count << "\n";
    return 0;
}
