// Максимов Гліб, К-28, варіант 6

#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <syncstream>
#include <thread>

using namespace std;

void compute(const string& name, int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
    osyncstream(cout) << name << endl;
}

void slow(const string& name)
{
    compute(name, 7);
}

void quick(const string& name)
{
    compute(name, 1);
}

void work()
{
    auto start = chrono::steady_clock::now();

    future<void> a = async(launch::async, [] {
        quick("A1");
        quick("A3");
    });
    future<void> b = async(launch::async, [] {
        slow("B2");
        quick("C2");
    });

    slow("A2");
    a.get();
    quick("B1");
    quick("C1");
    b.get();

    chrono::duration<double> elapsed = chrono::steady_clock::now() - start;
    osyncstream(cout) << "Time: " << elapsed.count() << " s" << endl
                      << "Work is done!" << endl;
}

int main()
{
    work();
    return 0;
}
