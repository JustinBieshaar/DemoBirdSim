#pragma once

namespace Signals
{
    /// <summary>
    /// Interface for signals.
    /// 
    /// Currently the Signal is the prime signal and no other signals are added.
    /// However, if the program evolves it could lead into adding additional signals like; DelayedSignal : ISignal. Or any other custom signal
    /// functionality that may be needed.
    /// </summary>
    class ISignal
    {
    public:
        virtual ~ISignal() = default;
    };
}