#include "headers.h"

using namespace std;


mutex mtx;
condition_variable pCV, cCV;
queue<int> q;
int size = 4;
int i = 0;

class Producer{
public:
    int produce( int & x ){
        unique_lock<mutex> lk( mtx );
        while( q.size() == size ){
            cout << "Queue is full, size = " << q.size() << endl;
            pCV.wait( lk );
        }
        q.push( x );
        cout << "Produced " << x << endl;
        x++;
        cCV.notify_one();
    }

    void run(){
        while(1){
            produce( i );
        }
    }
};

class Consumer{
public:
    void consume(){
        unique_lock<mutex> lk( mtx );
        while( q.empty() ){
            cout << "Queue is empty, size = " << q.size() << endl;
            cCV.wait( lk );
        }
        int x = q.front();
        q.pop();
        cout << "Consumed " << x << endl;
        sleep(1);
        pCV.notify_one();
    }

    void run(){
        while(1){
            consume();
        }
    }
    
};

int main(){
    thread pThread1( &Producer::run, Producer() );
    thread pThread2( &Producer::run, Producer() );
    thread cThread( &Consumer::run, Consumer() );
    pThread1.join();
    pThread2.join();
    cThread.join();
}
