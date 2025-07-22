#pragma once

#include <functional>
#include <queue>
#include <mutex>

namespace ThreadUtils
{
    using MainThreadTask = std::function<void()>;

    inline std::queue<MainThreadTask> mainThreadTasks;
    inline std::mutex taskMutex;                       

    inline void enqueueToMainThread(MainThreadTask task)
    {
        std::lock_guard<std::mutex> lock(taskMutex);
        mainThreadTasks.push(std::move(task));
    }

    inline void processMainThreadTasks()
    {
        std::queue<MainThreadTask> tasksToRun;

        {
            std::lock_guard<std::mutex> lock(taskMutex);
            std::swap(tasksToRun, mainThreadTasks);
        }

        while (!tasksToRun.empty())
        {
            auto task = std::move(tasksToRun.front());
            tasksToRun.pop();
            task();
        }
    }
}