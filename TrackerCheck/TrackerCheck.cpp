#include "pch.h"
#include "TrackerCheck.h"
#include "PlayerLookup.h"

BAKKESMOD_PLUGIN(TrackerCheck, "Check Trackers", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

/// <summary>
/// Setting up the plugin behavior on startup.
/// </summary>
void TrackerCheck::onLoad()
{
	_globalCvarManager = cvarManager;

	LOG("Loading TrackerCheck plugin.");

	// Register notifier to display the UI
	cvarManager->registerNotifier("ShowPlayerList", [this](std::vector<std::string> args) {
		if (!isWindowOpen_) {
			fetchPlayerList();
			gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) { Render(); });
		}
		}, "Displays the list of current players", PERMISSION_ALL
	);
	// Bind the notifier to the F7 key
	cvarManager->executeCommand("bind F7 ShowPlayerList");
}

/// <summary>
/// Fetch all the players from a game, and assign them a platform and a team color.
/// </summary>
void TrackerCheck::fetchPlayerList() {
	// Check if user is in a game
	if (!gameWrapper->IsInGame() && !gameWrapper->IsInOnlineGame())
	{
		LOG("Not in a game.");
		return;
	}

	auto server = gameWrapper->GetCurrentGameState();
	// Check if server is up
	if (!server) {
		LOG("No game found.");
		return;
	}

	LOG("Connected to game {}.", server.GetMatchGUID());

	blueTeamPlayers.clear();
	orangeTeamPlayers.clear();

	// Get players' data
	auto players = server.GetPRIs();
	for (auto player : players) {
		if (player.IsNull()) {
			LOG("No data found for a user.");
			continue;
		}

		PlayerInfo pl_info;
		pl_info.name = player.GetPlayerName().ToString();
		pl_info.id = player.GetPlayerID();

		// Assign simpler platform name
		switch (player.GetPlatform()) {
		case OnlinePlatform_Steam:
			pl_info.platform = Platform::STEAM;
			break;
		case OnlinePlatform_Epic:
			pl_info.platform = Platform::EPIC_GAMES;
			break;
		case OnlinePlatform_PS4:
		case OnlinePlatform_PS3:
			pl_info.platform = Platform::PLAYSTATION;
			break;
		case OnlinePlatform_Dingo:
			pl_info.platform = Platform::XBOX;
			break;
		case OnlinePlatform_NNX:
		case OnlinePlatform_OldNNX:
			pl_info.platform = Platform::NINTENDO;
			break;
		default:
			pl_info.platform = Platform::OTHER;
			break;
		}

		LOG("Created player with the following data:");
		LOG("ID: {}", pl_info.id);
		LOG("Name: {}", pl_info.name);
		LOG("Platform: {}", ToString(pl_info.platform));

		// Add player to current team color
		if (player.GetTeamNum() == 0) {
			blueTeamPlayers.emplace_back(pl_info);
			LOG("Team: Blue");
		}
		else {
			orangeTeamPlayers.emplace_back(pl_info);
			LOG("Team: Orange");
		}
	}
}

/// <summary>
/// Open default browser with RLTracker page of pl_info.
/// </summary>
/// <param name="pl_info">Information about a player.</param>
void TrackerCheck::handleClick(const PlayerInfo& pl_info) const {
	const std::string open_url = "start https://rocketleague.tracker.network/rocket-league/profile/";

	std::string platform_str;
	switch (pl_info.platform) {
	case Platform::EPIC_GAMES:
		platform_str = "epic";
		system((open_url + platform_str + '/' + pl_info.name).c_str());
		break;
	case Platform::STEAM:
		platform_str = "steam";
		system((open_url + platform_str + '/' + std::to_string(pl_info.id)).c_str());
		break;
	case Platform::PLAYSTATION:
		platform_str = "psn";
		system((open_url + platform_str + '/' + pl_info.name).c_str());
		break;
	case Platform::XBOX:
		platform_str = "xbl";
		system((open_url + platform_str + '/' + pl_info.name).c_str());
		break;
	case Platform::NINTENDO:
		platform_str = "switch";
		system((open_url + platform_str + '/' + pl_info.name).c_str());
		break;
	default:
		LOG("Could not open player profile of {} (ID: {})", pl_info.name, pl_info.id);
		return;
	}

	LOG("Clicked player: " + pl_info.name + " (ID: " + std::to_string(pl_info.id) + ")" + " (" + platform_str + ")");
}
