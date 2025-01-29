#pragma once

/// <summary>
/// Simpler platform enum than BakkesMod OnlinePlatform one.
/// </summary>
enum class Platform
{
	STEAM,
	EPIC_GAMES,
	PLAYSTATION,
	XBOX,
	NINTENDO,
	OTHER,
};

/// <summary>
/// Player data.
/// </summary>
struct PlayerInfo {
	int id;
	unsigned long long steam_id;
	std::wstring name;
	Platform platform;
};

/// <summary>
/// Convert Platform enum to C String.
/// </summary>
/// <param name="p">Platform enum value</param>
/// <returns></returns>
inline const char* ToString(Platform p) {
	switch (p)
	{
	case Platform::STEAM:		return "Steam";
	case Platform::EPIC_GAMES:  return "Epic Games";
	case Platform::PLAYSTATION: return "PlayStation";
	case Platform::XBOX:		return "Xbox";
	case Platform::NINTENDO:	return "Nintendo";
	default:					return "Other";
	}
}
