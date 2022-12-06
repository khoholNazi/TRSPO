#include <thread>
#include <iostream>
#include <mutex>
#include <ctime>

class A {
public:
    void addA(double a) {
        this->a += a;
    }

    double getA() {
        return a;
    }

private:
    double a=0;
};

class B {
public:
    void addB(double a) {
        this->b += a;
    }

    double getB() {
        return b;
    }

private:
    double b=0;
};

void addValueToB(double value,  B& classB);
void addValueToA(double value, A& classA);
double generateRandVal();
void baseFunc_firstHalf(A& a, B& b);
void baseFunc_secondHalf(A& a, B& b);

int main()
{
    srand(time(0));
    
    A a;
    B b;

    int N = 10 + rand() % 11; // random  count of threads from 10 to 20
    auto* arr = new std::thread[N];
    for (int n = 0; n < N/2; n++) {
        std::thread th(baseFunc_firstHalf,std::ref( a),  std::ref(b));
        arr[n] = th;
    }
    for (int n = N - (N / 2); n > 0; n--) {
        std::thread th(baseFunc_secondHalf, std::ref( a), std::ref( b));
        th.join();
        arr[n] = th;
    }

    for (auto& t : arr) {
        t.join();
    }

    std::cout << "resul a: " << a.getA() << std::endl
        << "result b: " << b.getB() << std::endl << "runtime:= " << clock() / 1000.0 << std::endl;
    
    return 0;
}

std::mutex mtx;

void addValueToA(double value,A& classA) {
    mtx.lock();
    classA.addA(value);
    mtx.unlock();
}

void addValueToB(double value, B& classB) {
    mtx.lock();
    classB.addB(value);
    mtx.unlock();
}

double generateRandVal() {
    return 10000 + rand() % 20000;
}

void baseFunc_firstHalf(A& a, B& b) {
    mtx.lock();
    for (int i = 0; i < generateRandVal(); i++)
    {
        a.addA(generateRandVal());
        b.addB(generateRandVal());
    }
    mtx.unlock();

}

void baseFunc_secondHalf(A& a, B& b) {
    mtx.lock();
    for (int i = 0; i < generateRandVal(); i++)
    {
        b.addB(generateRandVal());
        a.addA(generateRandVal());
    }
    mtx.unlock();
}
