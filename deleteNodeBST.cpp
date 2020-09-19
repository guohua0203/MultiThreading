#include "headers.h"
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode( int x ) : val(x), left(NULL), right(NULL) {};
};

TreeNode* findParent( TreeNode* root, TreeNode* t ){
    if( !root ){
        return NULL;
    }

    if( root->left == t || root->right == t ){
        return root;
    }

    TreeNode* res = NULL;
    res = findParent( root->left, t );

    if( !res ){
        res = findParent( root->right, t );
    }

    return res;
}

TreeNode* findLeftMax( TreeNode* root ){
    TreeNode* p = root->left;
    while( p->right ){
        p = p->right;
    }
    return p;
}

TreeNode* remove( TreeNode* root, TreeNode* t ){
    if( !root ){
        return NULL;
    }

    if( !t->left && !t->right ){
        TreeNode* p = findParent( root, t );
        if( t == p->left ){
            p->left = NULL;
        }
        else{
            p->right = NULL;
        }
        delete t;
        return root;
    }
    else if( !t->right ){
        if( t == root ){
            TreeNode* newRoot = t->left;
            delete( t );
            return newRoot;
        }
        
        TreeNode* p = findParent( root, t );
        if( t == p->left ){
            p->left = t->left;
        }
        else{
            p->right = t->left;
        }
        delete( t );
        return root;
    }
    else if( !t->left ){
        if( t == root ){
            TreeNode* newRoot = t->right;
            delete( t );
            return newRoot;
        }

        TreeNode* p = findParent( root, t );
        if( t == p->left ){
            p->left = t->right;    
        } 
        else{
            p->right = t->right;
        }
        delete( t );
        return root;
    }
    else{
        TreeNode* lm = findLeftMax( t );
        swap( lm->val, t->val );
        remove( root, lm );
        return root;
    }
}

void printTree( TreeNode* root ){
    if( !root ){
        return;
    }

    vector<TreeNode*> curLevel( 1, root );
    while( !curLevel.empty() ){
        vector<TreeNode*> nextLevel(0);
        for( auto it = curLevel.begin(); it != curLevel.end(); it++ ){
            cout << (*it)->val << ' ';
            if( (*it)->left ){
                nextLevel.push_back( (*it)->left );
            }
            if( (*it)->right ){
                nextLevel.push_back( (*it)->right );
            }
        }
        cout << endl;
        curLevel.clear();
        curLevel = nextLevel;
        nextLevel.clear();
    }
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

    TreeNode* res = remove( n1, n1 );
    printTree( n1 );

    // cout << res->val << endl;
}
