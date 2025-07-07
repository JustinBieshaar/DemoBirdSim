#pragma once

namespace DI
{
	enum class Lifetime
	{
		/// <summary>
		/// Single object is available of this instance.
		/// </summary>
		Singleton,
		/// <summary>
		/// Instance is temporary.
		/// </summary>
		Transient,
		/// <summary>
		/// Instance is pre-generated.
		/// </summary>
		Instance
	};
}