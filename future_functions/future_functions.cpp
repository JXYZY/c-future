// future_functions.cpp : 定义控制台应用程序的入口点。
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
	//***重点：：：当开新的线程的时候，会进行异步执行，主线程不会阻塞，但是如果主线程一旦调用了future.get()这个
	//函数的时候，那么主线程就会被阻塞，并且一直等到获取新开的线程的返回值，类似于这个get函数拥有thread,join的
	//的功能，并且还多了获取返回值的功能。

	//future get函数
	//std::future<int> fut = std::async(std::launch::async,get_int);
	std::future<int> fut = std::async(get_int);
	std::cout << "test..." << std::endl;
	//int x = fut.get();//会阻塞当前线程，直到获取返回值
	//std::cout << "you entered:" << x << std::endl;
	std::cout << "you entered:"<< std::endl;
	std::cin.get();
#endif

#if 0
	//future.share()
	
	std::future<int> fut = std::async(get_value);
	//测试过future.share()并不会阻塞
	std::shared_future<int> shfut = fut.share();

	//shared futures 可以被获取多次
	std::cout << "value:" << shfut.get() << std::endl;
	std::cout << "its double:" << shfut.get() * 2 << std::endl;
#endif
#if 0
	//future.valid() 检测future对象是否有效
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
	//重点：
	//当开启新线程的时候，调用future.wait和future.get都可以起到阻塞主线程的作用，等待子线程执行完，之所以有wait，是为了让主线程灵活的确定需
	//要在程序的哪个位置进行阻塞等待。
	//如果没有开启线程的话，那么调用函数只有在wait或者get被调用的时候才会执行，所以这个时候加wait可以让程序员确定当我主程序运行到什么位置的时候
	//让主线程去执行函数体。相当于灵活的对程序进行中断。
	//future.wait()
	//这里的wait只是在相当于get当中的等待功能，等待函数执行完
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

