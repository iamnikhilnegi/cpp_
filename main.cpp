#include <bits/stdc++.h>

using namespace std;

int minDistance(string A, string B)
{
  int len1 = A.length();
  int len2 = B.length();
  int DP[2][len2 + 1];
  memset(DP, 0, sizeof DP);
  for (int i = 0; i <= len2; ++i)
  {
    DP[0][i] = i;
  }
  for (int i = 1; i <= len1; ++i)
  {
    DP[i % 2][0] = i;
    for (int j = 1; j <= len2; ++j)
    {
      if (A[i - 1] == B[j - 1])
      {
        DP[i % 2][j] = DP[(i - 1) % 2][j - 1];
      }
      else
      {
        DP[i % 2][j] = 1 + min(DP[(i - 1) % 2][j], min(DP[i % 2][j - 1], DP[(i - 1) % 2][j - 1]));
      }
    }
  }
  return DP[len1 % 2][len2];
}
int lis(const vector<int> &A)
{
  int size = A.size();
  vector<int> DP(size);

  for (int i = 0; i < size; ++i)
  {
    DP[i] = 1;
    for (int j = 0; j < i; ++j)
    {
      if (A[i] > A[j] && DP[j] + 1 > DP[i])
      {
        DP[i] = DP[j] + 1;
      }
    }
  }
  return DP[size - 1];
}
auto adjacent(vector<vector<int>> &A)
{
  int size = A[0].size();
  vector<int> DP(size);
  DP[0] = max(A[0][0], A[1][0]);
  if (size == 1)
  {
    return DP[0];
  }
  DP[1] = max(max(A[0][0], A[1][0]), max(A[0][1], A[1][1]));
  if (size == 2)
  {
    return DP[1];
  }
  for (int i = 2; i < size; ++i)
  {
    DP[i] = max(DP[i - 1], DP[i - 2] + max(A[0][i], A[1][i]));
  }
  return DP[size - 1];
}

int seats(string A)
{
  int MOD = 10000003;
  vector<int> positions;
  for (int i = 0; i < A.length(); ++i)
  {
    if (A[i] == 'x')
    {
      positions.push_back(i);
    }
  }
  int sum = 0;

  int medianPos = positions.size() / 2;
  int left = 1;
  for (int i = medianPos - 1; i >= 0; i--)
  {
    sum = (sum + positions[medianPos] % MOD - left % MOD - positions[i] % MOD) % MOD;
    left++;
  }
  int right = 1;
  for (int i = medianPos + 1; i < positions.size(); ++i)
  {
    sum = (sum + positions[i] % MOD - positions[medianPos] - right % MOD) % MOD;
    right++;
  }
  return sum;
}
int candy(vector<int> &A)
{
  int sum = 0;
  int prev = INT_MIN;
  int curCan = 0;
  int cur;
  vector<int> arr(A.size());
  for (int i = 0; i < A.size(); ++i)
  {
    if (A[i] == prev)
    {
      arr[i] = curCan;
    }
    else if (A[i] > prev)
    {
      curCan++;
      arr[i] = curCan;
      prev = A[i];
    }
    else
    {
      arr[i] = 1;
      prev = A[i];
      curCan = 1;
    }
  }
  curCan = 0;
  prev = INT_MIN;
  for (int i = A.size() - 1; i >= 0; i--)
  {
    if (A[i] == prev)
    {
      arr[i] = max(curCan, arr[i]);
    }
    else if (A[i] > prev)
    {
      curCan++;
      arr[i] = max(curCan, arr[i]);
      prev = A[i];
    }
    else
    {
      arr[i] = max(arr[i], 1);
      prev = A[i];
      curCan = 1;
    }
  }
  for (int i = 0; i < A.size(); ++i)
  {
    sum += arr[i];
  }
  return sum;
}
int solve(int A, int B)
{
    int MOD = 1000000007;
  int DP[A][B+1];
  memset(DP, 0, sizeof DP);
  for(int i = 0; i<=9 & i<=B ;++i){
    DP[0][i] = 1;
  }
  for(int i = 0; i<A;++i){
    DP[i][0] = 1;
  }
  int maxSum;
  for(int i = 1; i< A;++i){
    maxSum = min(9*(i+1),B);
    for(int j = 1; j <= maxSum;++j){
      int sum = 0;
      for(int k = 0; k<=9 & k<=j; ++k){
        sum = (sum%MOD + DP[i-1][j-k]%MOD) % MOD;
      }
      DP[i][j] = sum%MOD;
    }
  }
  int ans = DP[A-1][B] - DP[A-2][B];
  return ans > 0? ans : ans + MOD;
}
vector<vector<int> > solve(int A, vector<vector<int> > &B) {
  int n = B.size();
  int DP[n][n];
  int max = INT_MIN;
  for(int i = 0 ; i < A; ++i ){
    for(int j = 0; j < A & i + j < A; ++j){
      if(B[i][j] > max ) {
        max = B[i][j];
      }
    }
  }
  DP[0][0] = max;

}

int findmaxRect(vector<int> arr){
  int size = arr.size();
  stack<int> reg;
  reg.push(0);
  int maxArea = INT_MIN;
  for(int i =1; i<size;++i){
    if(arr[i] >= arr[i-1]){
      reg.push(i);
    } else {
      int cur = reg.top();
      int prev;
      reg.pop();
      int area;
      while(arr[cur] > arr[i]){
        if(reg.empty()){
          area = arr[cur]*(i);
          break;
        }else{
          prev = reg.top();
          area = arr[cur]*(i-prev-1);
          cur = prev;
          reg.pop();
        }
        if(area > maxArea){
          maxArea = area;
        }
      }
      reg.push(i);
    }
  }
  int cur = reg.top();
  int prev;
  reg.pop();
  while(!reg.empty()){
    prev = reg.top();
    int area = arr[cur]*(size - prev - 1);
    if(area > maxArea){
      maxArea = area;
    }
    cur = prev;
    reg.pop();
  }
  prev = 0;
  int area = arr[cur]*size;
  if(area > maxArea){
    maxArea = area;
  }
  return maxArea;
}
int maximalRectangle(vector<vector<int> > &A) {
  vector<int> DP(A[0].size());
  int maxRect = INT_MIN;
  for(int i = 0; i < A.size();++i){
    for(int j = 0;j<A[0].size();++j){
      if(A[i][j]==1){
        DP[j] = DP[j]+1;
      } else {
        DP[j] = 0;
      }
    }
    int area = findmaxRect(DP);
    if(area > maxRect){
      maxRect = area;
    }

  }
  return maxRect;
}



int main()
{

  vector<vector<int>>  arr{{1, 0, 0, 1, 0, 0, 1, 1},{0, 1, 0, 1, 1, 1, 0, 1},{0, 0, 1, 0, 0, 0, 0, 0}};
  int ar[] = {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1};
  vector<vector<int>> arr2{{0, 0, 1, 0, 0, 0, 1, 0, 1},
                           {0, 1, 1, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 1, 0, 1, 0, 1},
                           {0, 1, 0, 0, 0, 1, 1, 0, 1},
                           {0, 1, 0, 0, 0, 0, 1, 1, 1},

                           {0, 1, 0, 0, 0, 0, 1, 1, 1},
                           {1, 0, 1, 1, 1, 0, 1, 1, 1},
                           {1, 1, 1, 1, 0, 1, 1, 1, 1}};

  string str = "....x..xx...x..";

vector<int> A{5,4,2};
  int n = maximalRectangle(arr2);
  int x = findmaxRect(A);
  int m = -1%9;
  std::cout << x << endl;
  return 0;
}