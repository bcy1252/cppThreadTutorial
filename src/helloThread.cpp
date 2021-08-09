#include <iostream>
#include <thread> //c++对多线程的标准库
using namespace std;

void hello() //每个线程都需要一个初始函数，新线程的执行从这里开始
{
    cout << "Hello, Thread" << endl;
}
using namespace std;

int main() //初始线程main()
{
    thread t(hello); //创造一个对象t，该对象拥有新函数hello()作为初始函数。
    t.join(); // 让初始线程等待新线程t结束;
}