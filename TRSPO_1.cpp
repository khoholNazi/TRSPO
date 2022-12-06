#include <iostream>
#include <thread>

void foo(int x)
{
    for (int i = 0; i < x; i++) {
        std::cout << "Thread using function"
            " pointer as callable\n";
    }
}

void foo2(int x)
{
    for (int i = 0; i < x; i++) {
        std::cout << "Thread using function_2"
            " pointer as callable\n";
    }
}

class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++)
            std::cout << "Thread using function"
            " object as  callable\n";
    }
};

int main()
{
    std::cout << "Threads 1 and 2 and 3 "
        "operating independently" << std::endl;

    std::thread th1(foo, 3);
    std::thread th2(thread_obj(), 3);
    std::thread th3(foo2, 3);
    th1.join();
    th2.join();
    th3.join();

    return 0;
}
