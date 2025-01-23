#include "pch.h"
#include "TrackerCheck.h"

/// <summary>
/// Used to render own plugin window.
/// < / summary>
void TrackerCheck::RenderWindow() {
	ImGui::Text("Blue Team:");
	for (const auto& player : blueTeamPlayers) {
		if (ImGui::Button(player.name.c_str())) {
			handleClick(player);
			LOG("Blue team player: " + player.name);
		}
	}

	ImGui::Separator(); // Separate Allied and Opponent players

	ImGui::Text("Orange Team:");
	for (const auto& player : orangeTeamPlayers) {
		if (ImGui::Button(player.name.c_str())) {
			handleClick(player);
			LOG("Orange team player: " + player.name);
		}
	}
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
	ImGui::Text(reinterpret_cast<const char*>(u8"Characters \U0001F60D \u03A9"));
	if (ImGui::Button("DEBUG ONLY")) {
		PlayerInfo player;
		player.id = 123456789;
		player.name = reinterpret_cast<const char*>(u8"Characters \U0001F60D \u03A9");
		player.platform = Platform::EPIC_GAMES;
		handleClick(player);
		LOG("Orange team player: " + player.name);
	}
	//std::u8string test = u8"\U0001F60D \u03A9";
	//const char* literal = reinterpret_cast<const char*>(u8"I \U0001F60D \u03A9");
}
