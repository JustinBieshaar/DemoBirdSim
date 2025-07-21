#pragma once

#include <memory>
#include <SignalHandler.h>

class IView
{
public:
	IView(std::shared_ptr<SignalHandler> signalHander) : m_signalHandler(signalHander) {}

	virtual void init() = 0;
	virtual void render() = 0;

protected:
	std::shared_ptr<SignalHandler> m_signalHandler;
};