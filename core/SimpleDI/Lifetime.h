#pragma once

namespace SimpleDI
{
	enum class Lifetime
	{
		/// <summary>
		/// A single shared instance is created and reused. 
		/// Created on first resolve, then cached and reused.
		/// Useful for the likes of managing services to control data in the current container state.
		/// </summary>
		Singleton,

		/// <summary>
		/// A new independent instance is created on every resolve call.
		/// The container does not retain ownership, so you must manage the lifetime via shared_ptr.
		/// Useful for temporary and/or stateless services or services which are unique to each instance which requires one (per-operation logic).
		/// 
		/// [EXAMPLES]
		/// Temporary/stateless service example;
		/// Per-operation example; a progressService. So each instance could hold it's own progressService.
		/// </summary>
		Transient,

		/// <summary>
		/// An existing, pre-constructed instance is bound and reused.
		/// Useful for testing, externally managed services or a service that's already created outside of the
		/// DI pipeline.
		/// </summary>
		Instance

		// additionally Scoped could also be added.
	};
}