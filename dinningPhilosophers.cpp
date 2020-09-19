#include "headers.h"

using namespace std;

#define NUM 5

class Semaphore{
    mutex mtx;
    condition_variable cv;
    int amt;
public:
    Semaphore( int a ): amt(a){};
    void wait();
    void notify();
};

void Semaphore :: wait(){
    unique_lock<mutex> lk( mtx );
    while( amt <= 0 ){
        cv.wait( lk );
    }
    amt--;
}

void Semaphore :: notify(){
    unique_lock<mutex> lk;
    amt++;
    cv.notify_one();
}

mutex mtx;
Semaphore numAllowToEat( NUM - 1 );
vector< Semaphore* > forks( 0 );

class Philosopher{
    int id;
public:
    Philosopher( int id) : id(id){};
    void eat(){
        numAllowToEat.wait();
        
        forks[ id ]->wait();
        {
            unique_lock<mutex> lk( mtx );
            cout << "philosopher " << id << " grab " << "fork " << id << endl;
        }    
        
        forks[ ( id+1 ) % NUM ]->wait();
        {
            unique_lock<mutex> lk( mtx);
            cout << "philosopher " << id << " grab " << "fork " << ( id+1)%NUM << endl;
        }

        forks[ id ]->notify();
        forks[ (id+1)%NUM ]->notify();

        sleep(1);
        numAllowToEat.notify();
    }
};


vector< Philosopher* > ph( 0 );

int main(){
    for(int i=0; i<NUM; i++){
        ph.push_back( new Philosopher(i) );
        forks.push_back( new Semaphore(1) );
    }

    while(1){
        vector<thread> threads(0);
        for(int i=0; i<NUM; i++){
            threads.push_back( thread( &Philosopher::eat, ph[i] ) );
        }

        for(int i=0; i<NUM; i++){
            threads[i].join();
        }

        cout << "End of an iteration." << endl;
    }
}
