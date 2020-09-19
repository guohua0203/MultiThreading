#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <time.h>

using namespace std;

bool flag = 0;
int counter = 0;
mutex mtx;
condition_variable setCV, unsetCV; 
time_t timer1 = time(NULL); 
time_t timer2 = timer1;

void setFlag(){
    unique_lock<mutex> lk( mtx );
    while( flag ){
        setCV.wait( lk );
    }
    
    flag = true;
    counter++;
    unsetCV.notify_one();
}

void unsetFlag(){
    unique_lock<mutex> lk( mtx );
    while( !flag ){
        unsetCV.wait( lk );
    }
    
    flag = false;
    counter++;
    setCV.notify_one();
}

void setAgent(){
    while( difftime( timer2, timer1 ) < 1 ){
        setFlag();
        timer2 = time( NULL );
    }
}

void unsetAgent(){
    while( difftime( timer2, timer1 ) < 1 ){
        unsetFlag();
        timer2 = time( NULL );
    }
}

int main(){
    thread iThread = thread( setAgent );
    thread dThread = thread( unsetAgent );
    iThread.join();
    dThread.join();
    cout << (float) 1 / counter << endl;
}

