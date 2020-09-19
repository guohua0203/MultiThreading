#include "headers.h"

using namespace std;

mutex mtx;
condition_variable pushCV, popCV; 

class MyStack{
    stack<int> st;
    int cap;
 public:
    MyStack( int c );
    void push( int x );
    void pop();
    int top();
    int empty();
};

MyStack :: MyStack(int c ){
    cap = c;
}

void MyStack :: push( int x ){
    unique_lock<mutex> lk( mtx );
    while( st.size() == cap ){
        cout << "Stack is full, size = " << st.size() << endl; 
        pushCV.wait( lk );
    }
    
    st.push( x );
    cout << "Pushed " << x << endl;
    popCV.notify_one();
}

void MyStack :: pop( ){
    unique_lock<mutex> lk( mtx );
    while( st.empty() ){
        cout << "Stack is empty, size = " << st.size() << endl;
        popCV.wait( lk );
    }

    int x = st.top();
    st.pop();
    cout << "Poped " << x << endl;
    sleep(1);
    pushCV.notify_one();
}

MyStack mst(4);
vector<thread> threads(0);

void pushAgent(){
    while(1){
        mst.push(5);
    }    
}

void popAgent(){
    while(1){
        mst.pop();
    }
}

int main(){
    for(int i=0; i<2; i++){
        threads.push_back( thread( pushAgent ) );
    }
    
    threads.push_back( thread( popAgent ) );
        
    for( int i=0; i<threads.size(); i++ ){
        threads[i].join();
    }
}
