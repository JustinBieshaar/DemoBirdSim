/*
* Just a global file holding values which can be included anywhere.
*
* THIS SHOULD NOT BE EXPLOITED!
*/
#pragma once

// My dear aplogies for not making it resizable. I just wanted to keep it simple ;)
const float Window_Width = 1280;
const float Window_Height = 720;

/// <summary>
/// How many quads
/// </summary>
const float Terrain_Size = 800;

/// <summary>
/// Vertex count per quad
/// </summary>
const int Terrain_VertexCount = 128;

/// <summary>
/// Texture repeat for the entire terrain.
/// The higher the value, the more detailed.
/// </summary>
const int Terrain_Texture_Repeat = 40;

/// <summary>
/// Enabled wire frame rendering mode.
/// Can be useful for debugging.
/// </summary>
extern bool EnableWireframeMode;