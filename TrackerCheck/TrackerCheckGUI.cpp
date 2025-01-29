#include "pch.h"
#include "TrackerCheck.h"
//#include <codecvt>

/// <summary>
/// Used to render own plugin window.
/// < / summary>
void TrackerCheck::RenderWindow() {
	//ImGui::Text("Blue Team:");
	//for (const auto& player : blueTeamPlayers) {
	//	if (ImGui::Button(player.name.c_str())) {
	//		handleClick(player);
	//		LOG(L"Blue team player: " + player.name);
	//	}
	//}

	//ImGui::Separator(); // Separate Allied and Opponent players

	//ImGui::Text("Orange Team:");
	//for (const auto& player : orangeTeamPlayers) {
	//	if (ImGui::Button(player.name.c_str())) {
	//		handleClick(player);
	//		LOG(L"Orange team player: " + player.name);
	//	}
	//}
}

/// <summary>
/// Use to render own tab in the settings menu.
/// </summary>
void TrackerCheck::RenderSettings() {
	ImGui::Text("Developed by Tristan Bony.");
	ImGui::Text("GitHub: https://github.com/TristanB0");
	ImGui::Text("Version: %s", plugin_version);

	// Debug separator
	ImGui::Separator();
	ImGui::Text("Characters test");
	if (ImGui::Button("DEBUG ONLY")) {
		PlayerInfo player;
		player.id = 123456789;
		player.name = L"PNDH \u30C3";
		player.platform = Platform::EPIC_GAMES;
		handleClick(player);
		//LOG(L"Orange team player: " + player.name);
	}
}
