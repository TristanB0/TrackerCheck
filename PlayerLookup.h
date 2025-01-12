#pragma once

enum class Platform
{
	STEAM,
	EPIC_GAMES,
	PLAYSTATION,
	XBOX,
	NINTENDO,
	OTHER,
};

struct PlayerInfo {
	std::string name;
	Platform platform;
};
