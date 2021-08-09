//ref:https://www.cnblogs.com/wangguchangqing/p/6134635.html
#include <iostream>
#include <thread>

using namespace std;

void output(int i)//新线程
{
	cout << i << endl;
}

int main()//主线程
{
	
	for (uint8_t i = 0; i < 4; i++)
	{
        //一定要在thread销毁前，调用t.join或者t.detach来决定线程已何种方式运行；
		thread t(output, i);
        cout << t.get_id() << endl;
        // t.detach(); //启动的线程自主在后台运行，当前的代码继续往下执行，不等待新线程结束。
		//t.join();	//join方式，等待启动的线程完成(阻塞当前代码)，才会继续往下执行
	}
		
	getchar();
	return 0;
}