#include "header.h"

struct Semaphore {
	mutex mtx;
	condition_variable cv;
	int amt;

	Semaphore(){}

	Semaphore(int amt){
		this->amt = amt;
	}

	void dec() {
		unique_lock<mutex> lck(mtx);
		while(amt <= 0) cv.wait(lck);
		amt--;
		cv.notify_one();
	}

	void inc() {
		unique_lock<mutex> lck(mtx);
		amt++;
		cv.notify_one();
	}
};

#define NUM_PHILOSOPHER 5
#define NUM_ALLOWED_TO_EAT NUM_PHILOSOPHER - 1

Semaphore semaphore(NUM_ALLOWED_TO_EAT);
vector<mutex> mtxForks(NUM_PHILOSOPHER);
mutex mtxCout;

struct Philosopher {
	int id;
	Philosopher(int id) {
		this->id = id;
	}

	void eat() {
		semaphore.dec();
		unique_lock<mutex> lck1(mtxForks[id]);
		unique_lock<mutex> lck2(mtxForks[(id + 1) % NUM_PHILOSOPHER]);
		unique_lock<mutex> lck3(mtxCout);
		cout << id << " is eating" << endl;
		this_thread::sleep_for(std::chrono::seconds(1));
		semaphore.inc();
	}
};


int main()
{
	vector< Philosopher* > ph(0);

	for (int i = 0; i< NUM_PHILOSOPHER; i++) {
		ph.push_back(new Philosopher(i));
	}

	while (1) {
		vector<thread> threads(0);
		for (int i = 0; i < NUM_PHILOSOPHER; i++) {
			threads.push_back(thread(&Philosopher::eat, ph[i]));
		}

		for (int i = 0; i < NUM_PHILOSOPHER; i++) {
			threads[i].join();
		}

		cout << "End of an iteration." << endl;
	}
}
