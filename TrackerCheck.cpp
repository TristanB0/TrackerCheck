#include "pch.h"
#include "TrackerCheck.h"
#include "PlayerLookup.h"

BAKKESMOD_PLUGIN(TrackerCheck, "Check Trackers", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void TrackerCheck::onLoad()
{
	_globalCvarManager = cvarManager;

	// Register notifier to display the UI
	cvarManager->registerNotifier("ShowPlayerList", [this](std::vector<std::string> args) {
		fetchPlayerList();
		gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {
			RenderWindow();
			});
		}, "Displays the list of current players", PERMISSION_ALL);
	// Bind the notifier to the F7 key
	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {});
	cvarManager->executeCommand("bind F7 ShowPlayerList");

	cvarManager->log("Setting plugin window information.");
	windowPos = ImVec2(100, 100);
	windowSize = ImVec2(300, 400);
}

void TrackerCheck::fetchPlayerList() {
	if (!gameWrapper->IsInGame())
	{
		cvarManager->log("Not in a game.");
		return;
	}

	auto server = gameWrapper->GetCurrentGameState();
	if (server.IsNull()) {
		cvarManager->log("No game found.");
		return;
	}

	blueTeamPlayers.clear();
	orangeTeamPlayers.clear();

	auto players = server.GetPRIs();
	for (auto player : players) {
		if (player.IsNull()) continue;

		PlayerInfo p_info;
		p_info.name = player.GetPlayerName().ToString();
		p_info.id = player.GetPlayerID();

		switch (player.GetPlatform()) {
		case OnlinePlatform_Steam:
			p_info.platform = Platform::STEAM;
			break;
		case OnlinePlatform_Epic:
			p_info.platform = Platform::EPIC_GAMES;
			break;
		case OnlinePlatform_PS4:
		case OnlinePlatform_PS3:
			p_info.platform = Platform::PLAYSTATION;
			break;
		case OnlinePlatform_Dingo:
			p_info.platform = Platform::XBOX;
			break;
		case OnlinePlatform_NNX:
		case OnlinePlatform_OldNNX:
			p_info.platform = Platform::NINTENDO;
			break;
		default:
			p_info.platform = Platform::OTHER;
			break;
		}

		if (player.GetTeamNum() == 0) {
			blueTeamPlayers.emplace_back(p_info);
		}
		else {
			orangeTeamPlayers.emplace_back(p_info);
		}
	}
}

void TrackerCheck::RenderWindow() {
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);

	// Start a new ImGui window
	ImGui::Begin("Player List", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("Blue Team:");
	for (const auto& player : blueTeamPlayers) {
		if (ImGui::Button(player.name.c_str())) {
			handleClick(player);
			cvarManager->log("Blue team player: " + player.name);
		}
	}

	ImGui::Separator(); // Separate Allied and Opponent players

	ImGui::Text("Orange Team:");
	for (const auto& player : orangeTeamPlayers) {
		if (ImGui::Button(player.name.c_str())) {
			handleClick(player);
			cvarManager->log("Orange team player: " + player.name);
		}
	}

	// End the ImGui window
	ImGui::End();
}

void TrackerCheck::handleClick(const PlayerInfo& p_info) const {
	const std::string open_url = "start https://rocketleague.tracker.network/rocket-league/profile/";

	std::string platform_str;
	switch (p_info.platform) {
	case Platform::EPIC_GAMES:
		platform_str = "epic";
		system((open_url + platform_str + '/' + p_info.name).c_str());
		break;
	case Platform::STEAM:
		platform_str = "steam";
		system((open_url + platform_str + '/' + std::to_string(p_info.id)).c_str());
		break;
	case Platform::PLAYSTATION:
		platform_str = "psn";
		system((open_url + platform_str + '/' + p_info.name).c_str());
		break;
	case Platform::XBOX:
		platform_str = "xbl";
		system((open_url + platform_str + '/' + p_info.name).c_str());
		break;
	case Platform::NINTENDO:
		platform_str = "switch";
		system((open_url + platform_str + '/' + p_info.name).c_str());
		break;
	default:
		return;
	}

	cvarManager->log("Player clicked: " + p_info.name + " (ID: " + std::to_string(p_info.id) + ")" + " (" + platform_str + ")");
}
