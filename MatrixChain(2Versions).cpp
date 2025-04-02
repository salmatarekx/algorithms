// GROUP:   X
// ID:      XXXXXXXX
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b){
    if(a+1==b){
        T[a][b]=0;
        return 0;
    }
    if(T[a][b]!=-1) return T[a][b];
    int q,v=INT_MAX;
    for(int k=a+1;k<b;k++){
        int r=p[a]*p[k] * p[b] + MatChain(a,k)+ MatChain(k,b);
        if(r<v){
            v=r;
            q=k;
        }


    }
    T[a][b]=v; D[a][b]=q;
    return v;
} // Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
void MatChainTopDown(int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            T[i][j]=-1;
        }
    }
    MatChain(0,n);

} // Initialize T then call MatChain(0,n)

// BottomUp version
void MatChainBottomUp(int n){
    for(int i=0;i<n;i++){
        T[i][i+1]=0;

    }
    for(int t=2;t<=n;t++){
        for(int i=0;i+t<=n;i++){
            int j=i+t;
            int q,v=INT_MAX;
            for(int k=i+1;k<j;k++){
                int r=T[i][k] + T[k][j] + p[i] * p[k] * p[j];
                if(r<v){
                    v=r;
                    q=k;
                }

            }
            T[i][j]=v;
            D[i][j]=q;
        }
    }
}


// Recursive to output the solution for both versions
void MatChainSol(int a, int b){

    if(a+1==b){
        cout<<"A"<<a;
        return;
    }
    int k=D[a][b];
    cout<<"(";
    MatChainSol(a,k);
    cout<<"*";
    MatChainSol(k,b);
    cout<<")";


}

void Compute() {
    int caseNum = 1;

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break; // End of input

        for (int i = 0; i < n; i++) {
            int rows, cols;
            cin >> rows >> cols;
            p[i] = rows;
            if (i == n - 1) p[i + 1] = cols; // Store the last column dimension
        }

        // Solve using Bottom-Up or Top-Down
        MatChainBottomUp(n);

        // Output result
        cout << "Case " << caseNum++ << ": ";
        MatChainSol(0, n);
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
