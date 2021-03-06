#pragma once

#include <vector>
#include <thread>
#include <memory>
#include <future>
#include <functional>
#include <type_traits>
#include <cassert>
#include "ThreadQueue.h"

class thread_pool
{
public:
    thread_pool(
        unsigned int queueDepth = std::thread::hardware_concurrency(),
        size_t threads = std::thread::hardware_concurrency())
    : m_workQueue()
    {
        assert(queueDepth != 0);
        assert(threads != 0);
        for(size_t i = 0; i < threads; ++i)
            m_threads.emplace_back(std::thread([this]() {
                while(true)
                {
                    Proc workItem;
                    m_workQueue.WaitAndPop(workItem);
                    if(workItem == nullptr)
                    {
                        m_workQueue.Push(nullptr);
                        break;
                    }
                    workItem();
                }
            }));
    }

    ~thread_pool() noexcept
    {
        m_workQueue.Push(nullptr);
        for(auto& thread : m_threads)
            thread.join();
    }

    using Proc = std::function<void(void)>;

    template<typename F, typename... Args>
    void enqueue_work(F&& f, Args&&... args)
    {
        m_workQueue.Push([=]() { f(args...); });
    }

    template<typename F, typename... Args>
    auto enqueue_task(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();
        m_workQueue.Push([task](){ (*task)(); });
        return res;
    }

private:
    using ThreadPool = std::vector<std::thread>;
    ThreadPool m_threads;
    ThreadQueue<Proc> m_workQueue;
};
