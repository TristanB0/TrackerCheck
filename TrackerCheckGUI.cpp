#include "pch.h"
#include "TrackerCheck.h"

/// <summary>
/// Used to render own plugin window.
/// < / summary>
void TrackerCheck::RenderWindow() {
	isInterfaceVisible = false;

	// Start a new ImGui window
	if (!ImGui::Begin("Player List", &isInterfaceVisible, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::End();
		return;
	}

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

	// End the ImGui window
	ImGui::End();
}

void TrackerCheck::RenderSettings() {
	// TODO
	if (!ImGui::Begin("Player List", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::End();
		return;
	}

	ImGui::Text(reinterpret_cast<const char*>(u8"I \U0001F60D \u03A9"));
	//std::u8string test = u8"\U0001F60D \u03A9";
	//const char* literal = reinterpret_cast<const char*>(u8"I \U0001F60D \u03A9");

	ImGui::End();
}
