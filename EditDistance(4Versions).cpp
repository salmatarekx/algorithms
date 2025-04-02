#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m) {
    if (n == 0) return m;
    if (m == 0) return n;
    if (T1[n][m] != -1) return T1[n][m];

    int cost = (a[n - 1] == b[m - 1]) ? 0 : 1;
    int insertOp = EditDist1(n, m - 1) + 1;
    int deleteOp = EditDist1(n - 1, m) + 1;
    int replaceOp = EditDist1(n - 1, m - 1) + cost;

    T1[n][m] = min({insertOp, deleteOp, replaceOp});
    return T1[n][m];
}

int ComputeEditDist1(int N, int M) {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            T1[i][j] = -1;
        }
    }
    return EditDist1(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) {
    for (int i = 0; i <= N; i++) T2[i][0] = i;
    for (int j = 0; j <= M; j++) T2[0][j] = j;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            T2[i][j] = min({T2[i - 1][j] + 1, T2[i][j - 1] + 1, T2[i - 1][j - 1] + cost});
        }
    }
    return T2[N][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) {
    for (int j = 0; j <= M; j++) T3[0][j] = j;

    for (int i = 1; i <= N; i++) {
        T3[i % 2][0] = i;
        for (int j = 1; j <= M; j++) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            T3[i % 2][j] = min({T3[(i - 1) % 2][j] + 1, T3[i % 2][j - 1] + 1, T3[(i - 1) % 2][j - 1] + cost});
        }
    }
    return T3[N % 2][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) {
    for (int j = 0; j <= M; j++) T4[j] = j;

    for (int i = 1; i <= N; i++) {
        int prev = T4[0];
        T4[0] = i;
        for (int j = 1; j <= M; j++) {
            int temp = T4[j];
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            T4[j] = min({T4[j - 1] + 1, T4[j] + 1, prev + cost});
            prev = temp;
        }
    }
    return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int EditDistSol(int N, int M) {
    int i = N, j = M;
    int operations = 0;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && D[i][j] == D[i - 1][j - 1] + ((a[i - 1] != b[j - 1]) ? 1 : 0)) {
            if (a[i - 1] != b[j - 1]) {
                cout << operations + 1 << " Replace " << j << "," << b[j - 1] << endl;
                operations++;
            }
            i--; j--;
        } else if (j > 0 && D[i][j] == D[i][j - 1] + 1) {
            cout << operations + 1 << " Insert " << j << "," << b[j - 1] << endl;
            operations++;
            j--;
        } else {
            cout << operations + 1 << " Delete " << i << endl;
            operations++;
            i--;
        }
    }
    return operations;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) {
    // Uncomment to switch methods
    // return ComputeEditDist1(N, M);
    // return ComputeEditDist2(N, M);
    // return ComputeEditDist3(N, M);
    return ComputeEditDist4(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute() {
    int cas = 0;
    while (true) {
        a[0] = 0; b[0] = 0;
        if (!fgets(a, 82, stdin)) break;
        fgets(b, 82, stdin);
        a[strlen(a) - 1] = 0;
        b[strlen(b) - 1] = 0;
        if (cas) cout << endl;
        int N = strlen(a), M = strlen(b);
        ComputeEditDist(N, M);
        EditDistSol(N, M);
        cas++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    Compute();
    return 0;
}
