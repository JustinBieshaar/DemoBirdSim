#pragma once

/// <summary>
/// Interface to render imGui
/// </summary>
struct IInspectable
{
public:
	IInspectable() = default;
	IInspectable(bool valuesChangableByDebug) : m_valuesChangableByDebug(valuesChangableByDebug){}

	virtual void renderInspectorImGui() = 0;

protected:
	bool m_valuesChangableByDebug = true;
};