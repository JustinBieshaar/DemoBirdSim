#include <gtest/gtest.h>
#include "DIContainer.h"
#include "Lifetime.h"

// Mock interfaces and implementations for testing

struct IService
{
    virtual ~IService() = default;
    virtual int doSomething() = 0;
};

class ServiceImpl : public IService
{
public:
    int doSomething() override { return 42; }
};

class AnotherServiceImpl : public IService
{
public:
    int doSomething() override { return 100; }
};

class ParamService : public IService
{
public:
    explicit ParamService(int value) : m_value(value) {}
    int doSomething() override { return m_value; }

private:
    int m_value;
};

TEST(SimpleDITest, SingletonBindingReturnsSameInstance)
{
    DIContainer container;
    container.bind<IService, ServiceImpl>(DI::Lifetime::Singleton);

    auto instance1 = container.resolve<IService>();
    auto instance2 = container.resolve<IService>();

    EXPECT_EQ(instance1->doSomething(), 42);
    EXPECT_EQ(instance1, instance2); // Must be the same instance
}

TEST(SimpleDITest, TransientBindingReturnsNewInstanceEachTime)
{
    DIContainer container;
    container.bind<IService, ServiceImpl>(DI::Lifetime::Transient);

    auto instance1 = container.resolve<IService>();
    auto instance2 = container.resolve<IService>();

    EXPECT_EQ(instance1->doSomething(), 42);
    EXPECT_NE(instance1, instance2); // Must be different instances
}

TEST(SimpleDITest, BindInstanceReturnsSameInjectedObject)
{
    DIContainer container;

    auto realInstance = std::make_shared<ServiceImpl>();
    container.bindInstance<IService>(realInstance);

    auto resolved = container.resolve<IService>();

    EXPECT_EQ(resolved->doSomething(), 42);
    EXPECT_EQ(resolved, realInstance); // Must be the exact same shared_ptr
}

TEST(SimpleDITest, ThrowsOnUnboundType)
{
    DIContainer container;

    EXPECT_THROW({
        container.resolve<IService>();
        }, std::runtime_error);
}

TEST(SimpleDITest, BindingDifferentImplementationsWorks)
{
    DIContainer container;

    container.bind<IService, ServiceImpl>(DI::Lifetime::Transient);
    auto service1 = container.resolve<IService>();

    container.bind<IService, AnotherServiceImpl>(DI::Lifetime::Transient);
    auto service2 = container.resolve<IService>();

    EXPECT_EQ(service1->doSomething(), 42);
    EXPECT_EQ(service2->doSomething(), 100);
}

TEST(SimpleDITest, ConstructorArgumentsAreForwardedCorrectly)
{
    DIContainer container;
    container.bind<IService, ParamService>(DI::Lifetime::Transient, 123);

    auto service = container.resolve<IService>();
    EXPECT_EQ(service->doSomething(), 123);
}