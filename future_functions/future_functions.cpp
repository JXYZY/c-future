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
	std::this_thread::sleep_for(std::chrono::seconds(2));
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
#if 0
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
#if 1
	//����wait_for��ʱ��Ҳ������ִ�к�������������趨�ĵȴ�ʱ�䣬ÿ����ô��ʱ����һ�º�����û��ִ����
	//future.wait_for();
	std::future<int> fut = std::async(get_value);
	//wait_for��wait_until�ǲ�����deferred�Ƴ�������ִ�еģ����Բ������ʹ��
	//std::future<int> fut = std::async(std::launch::deferred,get_value);
	std::chrono::milliseconds span(5000);
	std::future_status status;
	do{
		status = fut.wait_for(span);
		if (status == std::future_status::deferred)
		{
			std::cout << "deferred!" << std::endl;
		}
		else if (status == std::future_status::timeout)
		{
			std::cout << "timeout" << std::endl;
		}
		else if(status == std::future_status::ready)
		{
			std::cout << "ready" << std::endl;
		}

		//std::cout << ".";
	} while (status != std::future_status::ready);

	std::cout << std::endl;
	int x = fut.get();
	std::cout << "return value is:" << x << std::endl;
#endif
#if 0
	//wait_until
	//wait_until��ȵ�ĳ��ʱ��㣬�����ǰִ���꣬��ô��ǰ���ȴ��������ĳ��ʱ���ûִ������ôҲ����ȴ�������״̬��timeout
	//wait_until��wait_for�����Զ�����deforred��ʱ��ĺ�������Ϊdeforred��ʱ��ֻ��wait���ߺ�����
	int x;
	auto tp = std::chrono::system_clock::now() + std::chrono::seconds(2);
	std::future<int> fut = std::async(get_value);
	std::future_status s = fut.wait_until(tp);
	if (s == std::future_status::ready)
	{
		x = fut.get();
	}
	if (s == std::future_status::timeout)
	{
		std::cout << "time out������" << std::endl;
	}
	if (fut.valid())
	{
		x = fut.get();
	}

	if (fut.valid() == false)
	{
		std::cout << "������һ��get֮��future����ͱ�ɷǷ�" << std::endl;
	}
	

	std::cout << "x:" << x << std::endl;

#endif
	std::cin.get();
    return 0;
}

