#pragma once

/// <summary>
/// Simpler platform enum than BakkesMod OnlinePlatform one.
/// </summary>
enum class Platform {
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
/// Convert Platform enum to a wide string literal.
/// </summary>
/// <param name="p">Platform enum value</param>
/// <returns></returns>
inline const wchar_t* platform_to_wstring(Platform p) {
	switch (p)
	{
	case Platform::STEAM:		return L"Steam";
	case Platform::EPIC_GAMES:  return L"Epic Games";
	case Platform::PLAYSTATION: return L"PlayStation";
	case Platform::XBOX:		return L"Xbox";
	case Platform::NINTENDO:	return L"Nintendo";
	default:					return L"Other";
	}
}

/// <summary>
/// Convert Platform enum to wide string literal corresponding to Rocket League Tracker notation.
/// </summary>
/// <param name="p">Platform enum value</param>
/// <returns></returns>
inline const wchar_t* platform_to_RL_tracker_wstring(Platform p) {
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
