#include "pch.h"
#include "TrackerCheck.h"
#include "PlayerLookup.h"
#include <format>

BAKKESMOD_PLUGIN(TrackerCheck, "Check Trackers", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

/// <summary>
/// Setting up the plugin behavior on startup.
/// </summary>
void TrackerCheck::onLoad() {
	_globalCvarManager = cvarManager;

	LOG("Loading TrackerCheck plugin.");

	gameWrapper->HookEvent(
		"Function TAGame.Team_TA.PostBeginPlay",
		//std::bind(&TrackerCheck::fetch_players, this)
		[this](std::string eventName) {
			LOG("Event triggered: {}", eventName);
			// Delay for 1 second (1000 milliseconds)
			gameWrapper->SetTimeout([this](GameWrapper* gw) { fetch_players(); }, 10.0f);
		}
	);

	// Register notifier to display the UI
	cvarManager->registerNotifier(
		"open_trackercheck_ui",
		[this](std::vector<std::string> args) {
			if (!isWindowOpen_) {
				Render();
			}
		}, "Displays the list of current players", PERMISSION_ALL
	);

	// Bind the notifier to the F7 key
	cvarManager->setBind(bind_key, "open_trackercheck_ui");
}

/// <summary>
/// Fetch all the players from a game, and assign them a platform and a team color.
/// </summary>
void TrackerCheck::fetch_players() {
	// Check if user is in a game
	if (!gameWrapper->IsInGame() && !gameWrapper->IsInOnlineGame()) {
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

	blue_team_players.clear();
	orange_team_players.clear();
	spectators.clear();

	// Get players' data
	auto players = server.GetPRIs();
	for (auto player : players) {
		if (player.IsNull()) {
			LOG("No data found for a user.");
			continue;
		}

		PlayerInfo pl_info;
		pl_info.name = player.GetPlayerName().ToWideString();
		pl_info.id = player.GetPlayerID();

		LOG("Created player with the following data:");

		// Assign simpler platform name
		switch (player.GetPlatform()) {
		case OnlinePlatform_Steam:
			pl_info.platform = Platform::STEAM;
			pl_info.steam_id = player.GetUniqueIdWrapper().GetUID();
			LOG("Steam ID: {}", pl_info.steam_id);
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

		LOG("ID: {}", pl_info.id);
		LOG(L"Name: {}", pl_info.name);
		LOG(L"Platform: {}", platform_to_wstring(pl_info.platform));

		// Add player to current team color
		switch (player.GetTeamNum()) {
		case 0:
			blue_team_players.emplace_back(pl_info);
			LOG("Team: Blue");
			break;
		case 1:
			orange_team_players.emplace_back(pl_info);
			LOG("Team: Orange");
			break;
		default:
			spectators.emplace_back(pl_info);
			LOG("Team: Spectators");
			break;
		}
	}
}

/// <summary>
/// Open default browser with RLTracker page of pl_info.
/// </summary>
/// <param name="pl_info">Information about a player.</param>
void TrackerCheck::open_rl_tracker(const PlayerInfo& pl_info) const {
	const std::wstring source_url = L"https://rocketleague.tracker.network/rocket-league/profile/";
	const std::wstring platform_str = platform_to_RL_tracker_wstring(pl_info.platform);
	std::wstring url_data;

	switch (pl_info.platform) {
	case Platform::EPIC_GAMES:
	case Platform::PLAYSTATION:
	case Platform::XBOX:
	case Platform::NINTENDO:
		url_data = std::format(L"{}/{}", platform_str, pl_info.name);
		break;
	case Platform::STEAM:
		url_data = std::format(L"{}/{}", platform_str, pl_info.steam_id);
		break;
	default:
		LOG(L"Could not open player profile of {} (ID: {})", pl_info.name, pl_info.id);
		return;
	}

	ShellExecute(NULL, NULL, (source_url + url_data).c_str(), NULL, NULL, SW_SHOWNORMAL);

	LOG(L"Clicked player: {} (ID: {}) (Platform: {})", pl_info.name, pl_info.id, platform_to_wstring(pl_info.platform));
}

/// <summary>
/// Open Steam profile of a player.
/// </summary>
/// <param name="steamId">Account ID of a Steam player</param>
void TrackerCheck::open_steam_profile(const unsigned long long steamId) const {
	const std::wstring steam_base_url = L"https://steamcommunity.com/profiles/";
	ShellExecute(NULL, NULL, (steam_base_url + std::to_wstring(steamId)).c_str(), NULL, NULL, SW_SHOWNORMAL);
}
