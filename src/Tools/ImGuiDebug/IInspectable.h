#pragma once

/// <summary>
/// Interface to render imGui
/// </summary>
struct IInspectable
{
public:
	virtual void RenderImGui() = 0;

protected:
	bool m_valuesChangableByDebug = true;
};