namespace utils
{
    namespace thread
    {
        template<typename F>
        void Pool::push(F f)
        {
            {
                std::unique_lock<std::mutex> lock(mutex_tasks);
                tasks.push_back(std::function<void()>(f));
            }

            cv.notify_one();
        }
    }
}
