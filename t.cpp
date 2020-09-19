#include "headers.h"
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode( int x ) : val(x), left(NULL), right(NULL) {};
};

void pp( TreeNode* root, vector<int>& sol ){
//    if( !root ){
  //      return;
    //}

    if( !root->left && !root->right ){
        sol.push_back( root->val );
        print_v( sol );
        sol.pop_back();
        return;
    }

    sol.push_back( root->val );
    pp( root->left, sol );
    pp( root->right, sol );
    sol.pop_back();
}

void printPath( TreeNode* root ){
    if( !root ){
        return;
    }

    vector<int> sol(0);
    pp( root, sol );
}


int main(){
    TreeNode* n1 = new TreeNode(10);
    TreeNode* n2 = new TreeNode(5);
    TreeNode* n3 = new TreeNode(2);
    TreeNode* n4 = new TreeNode(20);    
    TreeNode* n5 = new TreeNode(30);
    TreeNode* n6 = new TreeNode(8);
    
    n1->left = n2;
    n2->left = n3;
    n2->right = n6;
    n1->right = n4;
    n4->right = n5;
    
    printPath( n1 );
}
