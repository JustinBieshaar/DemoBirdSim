/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) */

#pragma once

#include <functional>
#include <queue>
#include <mutex>

namespace ThreadUtils
{
    // A task is simply a void function taking no arguments
    // using this name for clarification
    using MainThreadTask = std::function<void()>;

    // Global task queue that holds tasks submitted to the main thread
    inline std::queue<MainThreadTask> mainThreadTasks;

    // Mutex to protect access to the task queue (ensures thread safety)
    inline std::mutex taskMutex;

    /// <summary>
    /// Enqueues a task to be executed on the main thread.
    /// Thread-safe: can be called from any thread.
    /// 
    /// CAUTION; make sure ThreadUtils::processMainThreadTask is called in the main thread
    /// update loop. Otherwise it won't work.
    /// </summary>
    /// <param name="task">The task (lambda or function) to run later on the main thread.</param>
    inline void enqueueToMainThread(MainThreadTask task)
    {
        std::lock_guard<std::mutex> lock(taskMutex); // Lock to ensure thread-safe access
        mainThreadTasks.push(std::move(task)); // Push the task onto the shared queue
    }

    /// <summary>
    /// Processes and executes all pending main thread tasks.
    /// Should be called from the main thread periodically (e.g., in the main loop).
    /// </summary>
    inline void processMainThreadTasks()
    {
        std::queue<MainThreadTask> tasksToRun;
        {
            std::lock_guard<std::mutex> lock(taskMutex);
            std::swap(tasksToRun, mainThreadTasks); // Swap to avoid holding the lock during execution
        }

        // Execute all queued tasks
        while (!tasksToRun.empty())
        {
            auto task = std::move(tasksToRun.front());
            tasksToRun.pop();
            task(); // Invoke the task
        }
    }
}