// ProducerConsumer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "header.h"

// mutex is needed to lock a section of code;
// this only lock the code but does not block the thread;
// to block the thread, Condition Variable is needed -- see below;
mutex mtx;

// Condition Variable is needed to block a thread;
// Call wait(lock) to block a trhead;
condition_variable pCV, cCV;
queue<int> q;
int capacity = 4;
int i = 0;

class Producer {
public:
	int produce() {
		unique_lock<mutex> lk(mtx);
		// "while" is needed and "if" is *not* sufficient,
		// since if using "if" and we have 2 producer threads, 
		// when thread 1 wait and release the lock and 
		// thread 2 get the lock, thread 2 will *not* check the q.size(),
		// thus it will produce more items and put them to the queue;
		//
		// "if" is sufficient if there is only 1 producer thread;
		while (q.size() == capacity) {
			cout << "Queue is full, size = " << q.size() << endl;
			pCV.wait(lk);
		}
		q.push(i);
		cout << "Produced " << i << endl;
		i++;
		cCV.notify_one();

		return 0;
	}

	void run() {
		while (1) {
			produce();
		}
	}
};

class Consumer {
public:
	void consume() {
		unique_lock<mutex> lk2(mtx);
		while (q.empty()) {
			cout << "Queue is empty, size = " << q.size() << endl;
			cCV.wait(lk2);
		}
		int x = q.front();
		q.pop();
		cout << "Consumed " << x << endl;
		this_thread::sleep_for(std::chrono::seconds(1));
		pCV.notify_one();
	}

	void run() {
		while (1) {
			consume();
		}
	}

};

int main() {
	thread pThread1(&Producer::run, Producer());
	thread pThread2(&Producer::run, Producer());
	thread cThread(&Consumer::run, Consumer());
	pThread1.join();
	pThread2.join();
	cThread.join();
}
