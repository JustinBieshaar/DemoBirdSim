#include <gtest/gtest.h>
#include <SignalHandler.h>
#include <optional>

struct TestEvent
{
    int val;
};

TEST(SignalHandlerTests, CallsObserver)
{
    Signals::SignalHandler handler;
    bool triggered = false;

    handler.observeSignal<TestEvent>([&](Signals::Signal<TestEvent>& e)
        {
            EXPECT_EQ(e.data.val, 100);
            triggered = true;
        });

    handler.invokeSignal(TestEvent{ 100 });
    EXPECT_TRUE(triggered);
}

TEST(SignalHandlerTests, RemovesObserver)
{
    Signals::SignalHandler handler;
    bool triggered = false;

    // Register an observer and store the handle
    auto handle = handler.observeSignal<TestEvent>([&](Signals::Signal<TestEvent>& e)
        {
            triggered = true;
        });

    // Remove the observer
    handler.removeObserver(handle);

    // Trigger the event
    handler.invokeSignal(TestEvent{ 42 });

    // It should NOT be triggered
    EXPECT_FALSE(triggered);
}

TEST(SignalHandlerTests, OnlyRemovesSpecifiedObserver)
{
    Signals::SignalHandler handler;
    bool observer1Triggered = false;
    bool observer2Triggered = false;

    // First observer
    auto handle1 = handler.observeSignal<TestEvent>([&](Signals::Signal<TestEvent>&)
        {
            observer1Triggered = true;
        });

    // Second observer
    handler.observeSignal<TestEvent>([&](Signals::Signal<TestEvent>&)
        {
            observer2Triggered = true;
        });

    // Remove only the first one
    handler.removeObserver(handle1);

    // Trigger the event
    handler.invokeSignal(TestEvent{ 42 });

    // First should not trigger, second should
    EXPECT_FALSE(observer1Triggered);
    EXPECT_TRUE(observer2Triggered);
}

TEST(SignalHandlerTests, RemoveObserverUsingStdOptional)
{
    Signals::SignalHandler handler;
    bool triggered = false;

    // Register an observer and store the handle
    std::optional<Signals::ObserverHandle> handle = handler.observeSignal<TestEvent>([&](Signals::Signal<TestEvent>& e)
        {
            triggered = true;
        });

    // Remove the observer
    handler.removeObserver(*handle);

    // Trigger the event
    handler.invokeSignal(TestEvent{ 42 });

    // It should NOT be triggered
    EXPECT_FALSE(triggered);
}