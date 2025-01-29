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

/// <summary>
/// Convert Platform enum to std::wstring corresponding to Rocket League Tracker notation.
/// </summary>
/// <param name="p">Platform enum value</param>
/// <returns></returns>
inline std::wstring ToRLTrackerString(Platform p) {
	switch (p)
	{
	case Platform::STEAM:		return L"steam";
	case Platform::EPIC_GAMES:  return L"epic";
	case Platform::PLAYSTATION: return L"psn";
	case Platform::XBOX:		return L"xbl";
	case Platform::NINTENDO:	return L"switch";
	default:					return L"other";
	}
}
