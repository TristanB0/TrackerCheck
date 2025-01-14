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
	int id;
	std::string name;
	Platform platform;
};
