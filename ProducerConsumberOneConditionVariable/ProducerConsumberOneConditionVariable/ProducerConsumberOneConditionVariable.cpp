// ProducerConsumberOneConditionVariable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "header.h"

mutex mtx;
condition_variable cv;
queue<int> q;
int capacity = 4;

int i = 0;

struct Producer {
	void produce(int& x) {
		unique_lock<mutex> lck(mtx);
		while (q.size() == capacity) {
			cout << "queue is full" << endl;
			cv.wait(lck);
		}

		q.push(x);
		cout << "Produce " << x << endl;
		x++;
		cv.notify_one();
	}

	void run() {
		while (1) {
			produce(i);
		}
	}
};

struct Consumer {
	void consume() {
		unique_lock<mutex> lck(mtx);
		while (q.empty()) {
			cout << "queue is empty" << endl;
			cv.wait(lck);
		}

		int x = q.front();
		q.pop();
		cout << "Consume " << x << endl;
		this_thread::sleep_for(std::chrono::seconds(1));
		cv.notify_one();
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
	//thread pThread2(&Producer::run, Producer());
	thread cThread(&Consumer::run, Consumer());

	pThread1.join();
	//pThread2.join();
	cThread.join();
    return 0;
}

