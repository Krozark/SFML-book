#ifndef UTILS_THREAD_HPP
#define UTILS_THREAD_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>
#include <deque>

namespace utils
{
    /**
     * \brief namespace for thread classes
     */
    namespace thread
    {
        /**
         * \brief a class to manage a thread pool
         */
        class Pool
        {
            public:
                Pool(size_t size);///< construct a Pool of size size
                ~Pool(); ///< destruct the object. wait for the end of running task and skip the others.

                template<typename F>
                void push(F f); ///< add a function of type F to queue

                size_t size();///< return the number of function to call

                void wait(std::chrono::milliseconds d =std::chrono::milliseconds(500)); ///< wait for the end of all tasks

            private:
                std::atomic<bool> stop;
                std::deque<std::function<void()>> tasks;
                std::vector<std::thread> workers;
                //sync
                std::mutex mutex_tasks;
                std::condition_variable cv;


                class Worker
                {
                    public:
                        Worker(Pool& parent);
                        void operator()();
                    private:
                        Pool& parent;
                };


        };
    }
}
#include <utils/thread.tpl>
#endif
