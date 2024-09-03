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

class PlayerLookup
{
	std::vector<PlayerInfo> playerInfo;

public:
	std::string getName();

	void retrieveName();
	void retrievePlatform();

	void openTracker(PlayerInfo&);
};
