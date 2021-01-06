// async.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <future>
#include<vector>
#include<mutex>

void wait_func()
{
    std::mutex _mutex;
    std::vector<std::future<int>> futures;

    for (size_t idx = 0; idx < 10; idx++)
    {
        futures.push_back(std::async(std::launch::async,
            [&]()
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::scoped_lock lock(_mutex);
            std::cout << "Hello form thread!\n ";
            return 1;
        }));


    }


    for (auto& x : futures)
    {
        int val = x.get();
    }
}

void render_func()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Renedering data..." << std::endl;

    }

}

int main()
{
    std::thread th_wait(wait_func), th_render(render_func);

    if (th_wait.joinable())
    {
        th_wait.join();
    }

    if (th_render.joinable())
    {
        th_render.join();
    }
    return 0;
}

