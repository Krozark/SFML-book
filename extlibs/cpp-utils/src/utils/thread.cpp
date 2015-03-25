#include <utils/thread.hpp>

namespace utils
{
    namespace thread
    {
        Pool::Pool(size_t number) : stop(false)
        {
            workers.reserve(number);
            for(size_t i= 0;i<number;++i)
                workers.emplace_back(Worker(*this));
        }

        Pool::~Pool()
        {
            stop = true;
            cv.notify_all();

            for(auto& w : workers)
                w.join();
        }

        size_t Pool::size()
        {
            std::unique_lock<std::mutex> lock(mutex_tasks);
            return  tasks.size();
        }

        void Pool::wait(std::chrono::milliseconds d)
        {
            while(size()>0)
                std::this_thread::sleep_for(d);
        }
        

        Pool::Worker::Worker(Pool& parent) : parent(parent)
        {
        }

        void Pool::Worker::operator()()
        {
            std::function<void()> task;
            while(true)
            {
                {
                    std::unique_lock<std::mutex> lock(parent.mutex_tasks);

                    // look for a work item
                    while(not parent.stop && parent.tasks.empty())
                    { // if there are none wait for notification
                        parent.cv.wait(lock);
                    }

                    if(parent.stop)
                        return;

                    task = parent.tasks.front();
                    parent.tasks.pop_front();
                }

                task();
            }
        }
    }
}
