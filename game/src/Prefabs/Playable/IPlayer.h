#pragma once

/// <summary>
/// Interface purely for dependency injection purpose.
/// Hence why it's empty (for now)
/// </summary>
class IPlayer
{
public:
    IPlayer() = default;
    virtual ~IPlayer() = default;
};