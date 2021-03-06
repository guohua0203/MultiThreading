// ProducerConsumer02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "header.h"

mutex mtx;
queue<int> q;
int capacity = 4;
int i = 0;
bool mtxLocked = false;

class Producer {
public:
	void produce(int& x) {
		unique_lock<mutex> lck(mtx);
		mtxLocked = true;
		while(q.size() == capacity) {
			cout << "Queue is full, size = " << q.size() << endl;
			if (mtxLocked) {
				mtxLocked = false;
				lck.unlock();
			}
		}
		q.push(x);
		cout << "Produced " << x << endl;
		x++;
	}

	void run() {
		while (1) {
			produce(i);
		}
	}
};

class Consumer {
public:
	void consume(){
		unique_lock<mutex> lck(mtx);
		mtxLocked = true;
		while (q.empty()) {
			cout << "Queue is empty, size = " << q.size() << endl;
			if (mtxLocked) {
				mtxLocked = false;
				lck.unlock();
			}
		}

		int x = q.front();
		q.pop();
		cout << "Consumed " << x << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}

	void run() {
		while (1) {
			consume();
		}
	}
};

int main()
{
	thread pThread1(&Producer::run, Producer());
	thread cThread(&Consumer::run, Consumer());

	pThread1.join();
	cThread.join();

    return 0;
}

