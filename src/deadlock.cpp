#include<iostream>
#include<thread>
#include<list>
#include<mutex>
using namespace std;
mutex m0,m1;
int i = 0;
// 线程0刚上锁0，上下文切换到线程1，线程1加锁1.此时两个线程都想向下执行的话，
// 线程1必须等线程0解锁0,线程0就必须等待线程1解锁1，就这样两个线程一直阻塞，形成死锁。
// 解决方法，(1)按顺序上锁，一个上了m0，另一个线程要等他解锁才能上 (2)或者同时上锁lock(m0,m1), g0(m0,adopt_lock) //adopt_lock该参数防止再次上锁
void fun0()
{
	while (i < 100)
	{
		lock_guard<mutex> g0(m0);  //线程0加锁0
		lock_guard<mutex> g1(m1);  //线程0加锁1
		cout << "thread 0 running..." << endl;
	}
	return;
}
void fun1()
{
	while (i < 100)
	{
		lock_guard<mutex> g1(m1);  //线程1加锁1 //改成g0(m0),g1(m1)就不会死锁
		lock_guard<mutex> g0(m0);  //线程1加锁0
		cout << "thread 1 running...   "<< i << endl;
	}
	return;
}
int main()
{
	thread p0(fun0);
	thread p1(fun1);
	p0.join();
	p1.join();
    return 0;
}
