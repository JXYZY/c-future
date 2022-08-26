// future_functions.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <future>
#include <iostream>

int get_int()
{
	std::cout << "please input one int cout...." << std::endl;
	int x;
	std::cin >> x;
	return x;
}

int get_value()
{
	std::cout << "get_value thread id:" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 10;
}

int main()
{
	std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
#if 0
	//future.get()
	//***�ص㣺���������µ��̵߳�ʱ�򣬻�����첽ִ�У����̲߳�������������������߳�һ��������future.get()���
	//������ʱ����ô���߳̾ͻᱻ����������һֱ�ȵ���ȡ�¿����̵߳ķ���ֵ�����������get����ӵ��thread,join��
	//�Ĺ��ܣ����һ����˻�ȡ����ֵ�Ĺ��ܡ�

	//future get����
	//std::future<int> fut = std::async(std::launch::async,get_int);
	std::future<int> fut = std::async(get_int);
	std::cout << "test..." << std::endl;
	//int x = fut.get();//��������ǰ�̣߳�ֱ����ȡ����ֵ
	//std::cout << "you entered:" << x << std::endl;
	std::cout << "you entered:"<< std::endl;
	std::cin.get();
#endif

#if 0
	//future.share()
	
	std::future<int> fut = std::async(get_value);
	//���Թ�future.share()����������
	std::shared_future<int> shfut = fut.share();

	//shared futures ���Ա���ȡ���
	std::cout << "value:" << shfut.get() << std::endl;
	std::cout << "its double:" << shfut.get() * 2 << std::endl;
#endif
#if 0
	//future.valid() ���future�����Ƿ���Ч
	std::future<int> foo, bar;
	foo = std::async(get_value);
	bar = std::move(foo);
	if (foo.valid())
	{
		std::cout << "foo value is:" << foo.get() << std::endl;
	}
	else
	{
		std::cout << "foo is not valid..." << std::endl;
	}

	if (bar.valid())
	{
		std::cout << "bar value is:" << bar.get() << std::endl;
	}
	else
	{
		std::cout << "bar is not valid..." << std::endl;
	}
	std::cin.get();
#endif
#if 1
	//�ص㣺
	//���������̵߳�ʱ�򣬵���future.wait��future.get���������������̵߳����ã��ȴ����߳�ִ���֮꣬������wait����Ϊ�������߳�����ȷ����
	//Ҫ�ڳ�����ĸ�λ�ý��������ȴ���
	//���û�п����̵߳Ļ�����ô���ú���ֻ����wait����get�����õ�ʱ��Ż�ִ�У��������ʱ���wait�����ó���Աȷ���������������е�ʲôλ�õ�ʱ��
	//�����߳�ȥִ�к����塣�൱�����ĶԳ�������жϡ�
	//future.wait()
	//�����waitֻ�����൱��get���еĵȴ����ܣ��ȴ�����ִ����
	std::future<int> fut = std::async(std::launch::deferred,get_value);
	std::cout << "checking...." << std::endl;
	fut.wait();

	std::cout << "test...." << std::endl;
	if (fut.get())
	{
		std::cout << "is prime" << std::endl;
	}
	else
		std::cout << "is not prime" << std::endl;
#endif
	std::cin.get();
    return 0;
}

