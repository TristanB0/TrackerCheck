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
			showPlayerListUI();
			});
		}, "Displays the list of current players", PERMISSION_ALL);
	// Bind the notifier to the F6 key
	gameWrapper->RegisterDrawable([this](CanvasWrapper canvas) {});
	cvarManager->executeCommand("bind F6 ShowPlayerList");

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

void TrackerCheck::showPlayerListUI() const {
	ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);

	// Start a new ImGui window
	ImGui::Begin("Player List", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("Blue Team:");
	for (const auto& player : blueTeamPlayers) {
		if (ImGui::Button(player.name.c_str())) {
			// TODO: Handle player click - determine further action here
			cvarManager->log("Blue team player: " + player.name);
		}
	}

	ImGui::Separator(); // Separate Allied and Opponent players

	ImGui::Text("Orange Team:");
	for (const auto& player : orangeTeamPlayers) {
		if (ImGui::Button(player.name.c_str())) {
			// TODO: Handle player click - determine further action here
			cvarManager->log("Orange team player: " + player.name);
		}
	}

	// End the ImGui window
	ImGui::End();
}

void TrackerCheck::handleClick(const std::string& playerName, const Platform& platform) const {
	std::string platform_str;
	switch (platform) {
		case Platform::EPIC_GAMES:
			platform_str = "epic";
			break;
		case Platform::STEAM:
			platform_str = "steam";
			break;
		case Platform::PLAYSTATION:
			platform_str = "psn";
			break;
		case Platform::XBOX:
			platform_str = "xbl";
			break;
		case Platform::NINTENDO:
			platform_str = "switch";
			break;
		default:
			return;
	}

	// TODO: Open RLTracker

	cvarManager->log("Player clicked: " + playerName + " (" + platform_str + ")");
}
