//https://leetcode.com/problems/fizz-buzz-multithreaded/

/*
Think about what need to be synchronized, and what should be inside the critical section. So in this problem, the read/update
of n should be inside the critical section and get synchronized. Therefore we can use one mutex to protect it.
*/

class FizzBuzz {
private:
    int n;
    int counter;
    mutex m;

public:
    FizzBuzz(int n) {
        this->n = n;
        counter = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (1){
            m.lock();
            if (counter > n){
                m.unlock();
                return;
            }
            if (counter % 3 == 0 && counter % 5 != 0){
                printFizz();
                counter++;
            }
            m.unlock();
	    }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (1){
            m.lock();
            if (counter > n){
                m.unlock();
                return;
            }
            if (counter % 3 != 0 && counter % 5 == 0){
                printBuzz();
                counter++;
            }
            m.unlock();
	    }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while (1){
            m.lock();
            if (counter > n){
                m.unlock();
                return;
            }
            if (counter % 3 == 0 && counter % 5 == 0){
                printFizzBuzz();
                counter++;
            }
            m.unlock();
	    }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (1){
            m.lock();
            if (counter > n){
                m.unlock();
                return;
            }
            if (counter % 3 != 0 && counter % 5 != 0){
                printNumber(counter);
                counter++;
            }
            m.unlock();
	    }
    }
};
