//
//  main.cpp
//  part-array
//
//  Created by mndx on 30/04/2022.
//  Maximum partition array using
//  dynamic programming.
//

#include <iostream>
#include <vector>

using namespace std;

const int N = 501;

int dp[N];

void init_table() {
    
    for(int i = 0; i < N; ++i)
        dp[i] = 0;
}

int max(int a, int b) {
    int res = 0;
    
    if(a > b) res = a;
    else res = b;
    
    return res;
}

int max_sum(vector<int> & arr, int k, int i) {
    int res = 0;
    
    int n = (int) arr.size();
    
    if(dp[i] != 0)
        return dp[i];
    
    if(i > n) {
        return 0;
    }
    
    for(int j = 0; j < k; ++j) {
        for(int sl = j + 1; sl <= k; ++sl) {
            if(i + j < n && i + sl <= n) {
                int max_loc = arr[i + j] * sl + max_sum(arr, k, i + sl);
                res = max(res, max_loc);
            }
        }
    }
    
    dp[i] = res;
    
    return res;
}

int max_sum_after_partitioning(vector<int> & arr, int k) {
    int res = 0;

    for(int i = 0; i < k; ++i) {
        for(int s = i + 1; s <= k; ++s) {
            int max_loc = arr[i] * s + max_sum(arr, k, s);
            res = max(res, max_loc);
        }
    }
    
    return res;
}

int max_sum_after_partitioning_ref(vector<int> & arr, int k) {
    int n = (int) arr.size();
    int max_mat[N][N];
        
    init_table();
    
    max_mat[0][1] = arr[0];
    dp[0] = arr[0];
    
    for (int i = 1; i < n; ++i){
        dp[i] = 0;
        for (int j = 1; j <= k && i - j >= -1; ++j){
            max_mat[i][j] = j == 1 ? arr[i] : max(max_mat[i - 1][j - 1], arr[i]);
            dp[i] = max(dp[i], (i >= j ? dp[i - j] : 0) + max_mat[i][j] * j);
        }
    }
    
    return dp[n - 1];
}

int main(int argc, const char * argv[]) {

    // Partition constant
    int k = 10;
    
    // Array to be partitioned
    vector<int> arr = {1,4,1,5,7,3,6,1,9,9,3};
    
    // Compute max partition sum
    int max_sum = max_sum_after_partitioning(arr, k);
    
    // Print results
    cout << max_sum << endl;
    
    return 0;
}
