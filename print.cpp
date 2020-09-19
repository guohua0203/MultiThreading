#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void print_array(int A[], int n){
  for(int i=0; i<n; i++)
    cout << A[i] << ' ';
  cout << endl;
}

void print_v(vector<int> v){
  for(auto it = v.begin(); it!=v.end(); it++)
    cout << *it << ' ';
  cout << endl;
}

void print_vv(vector< vector<int> > v){
  for(auto it = v.begin(); it!=v.end(); it++){
    for(auto it2 = (*it).begin(); it2!=(*it).end(); it2++){
      cout << *it2 << ' ';
    }
    cout << endl;
  }
}

void print_set(unordered_set<string> s){
  for(auto it = s.begin(); it!=s.end(); it++)
    cout << *it << endl;
}

void print_v(vector<string> v){
  for(auto it = v.begin(); it!=v.end(); it++)
    cout << *it << endl;
}

void print_vv(vector<vector<string> > v){
  for(int i=0; i<v.size(); i++){
    for( int j=0; j<v[i].size(); j++){
      cout << v[i][j] << ' ';
    }
    cout << endl;
  }
}

void print_list(ListNode* head){
  ListNode* p = head;
  while(p){
    cout << p->val << ' ';
    p = p->next;
  }
  cout << endl;
}

void print_set(multiset<int> ms){
  for(auto it=ms.begin(); it != ms.end(); it++){
    cout << *it << ' ';
  }
  cout << endl;
}
