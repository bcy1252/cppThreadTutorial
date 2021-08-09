#include<iostream>
#include<thread>
#include<list>
#include<mutex>
using namespace std;
// 1. 原子性：把一个互斥量锁定为一个原子操作，这意味着如果一个线程锁定了一个互斥量，没有其他线程在同一时间可以成功锁定这个互斥量；

// 2. 唯一性：如果一个线程锁定了一个互斥量，在它解除锁定之前，没有其他线程可以锁定这个互斥量；

// 3. 非繁忙等待：如果一个线程已经锁定了一个互斥量，第二个线程又试图去锁定这个互斥量，则第二个线程将被挂起（不占用任何cpu资源），直到第一个线程解除对这个互斥量的锁定为止，第二个线程则被唤醒并继续执行，同时锁定这个互斥量。

class msgList
{
private:
	list<int>mylist;
	mutex m;
	int i = 0;
public:
    void WriteList()
	{
		while(i<10000)
		{
            lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
			//m.lock();   
			if (i >= 10000)
			{
				//m.unlock();   //由于有了guard，这里就无需unlock()了
				break;
			}
			mylist.push_back(i++);
			//m.unlock();
		}
		return;
    }
	void showList()
	{
		for (auto p = mylist.begin(); p != mylist.end(); p++)   
		{
			cout << (*p) << " ";
		}
		cout << endl;
		cout << "size of list : " << mylist.size() << endl;
		return;
	}
};
int main()
{
	msgList mlist;
	thread pwrite0(&msgList::WriteList, &mlist);
	thread pwrite1(&msgList::WriteList, &mlist);
 
	pwrite0.join();
	pwrite1.join();
	cout << "threads end!" << endl;
 
	mlist.showList();  //子线程结束后主线程打印list
    return 0;
}