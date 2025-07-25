#pragma once

namespace SimpleDI
{
	enum class Lifetime
	{
		/// <summary>
		/// A single shared instance is created and reused. 
		/// Created on first resolve, then cached and reused.
		/// </summary>
		Singleton,

		/// <summary>
		/// A new independent instance is created on every resolve call.
		/// The container does not retain ownership, so you must manage the lifetime via shared_ptr.
		/// </summary>
		Transient,

		/// <summary>
		/// An existing, pre-constructed instance is bound and reused.
		/// Useful for testing or externally managed services.
		/// </summary>
		Instance
	};
}