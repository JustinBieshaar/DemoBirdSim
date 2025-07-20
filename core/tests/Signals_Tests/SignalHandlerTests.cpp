#include <gtest/gtest.h>
#include <SignalHandler.h>

struct TestEvent
{
    int val;
};

TEST(SignalHandlerTests, CallsObserver)
{
    SignalHandler handler;
    bool triggered = false;

    handler.observeEvent<TestEvent>([&](Event<TestEvent>& e)
        {
            EXPECT_EQ(e.data.val, 100);
            triggered = true;
        });

    handler.invokeEvent(TestEvent{ 100 });
    EXPECT_TRUE(triggered);
}