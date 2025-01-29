#include "pch.h"
#include "TrackerCheck.h"

/// <summary>
/// Used to render own plugin window.
/// < / summary>
void TrackerCheck::RenderWindow() {
	ImGui::Text("Blue Team:");
	for (const auto& player : blueTeamPlayers) {
		if (ImGui::Button(utf8_encode(player.name).c_str())) {
			handleClick(player);
			LOG(L"Blue team player: " + player.name);
		}
		if (player.platform == Platform::STEAM) {
			ImGui::SameLine();
			if (ImGui::Button("Open Steam profile")) {
				openSteamProfile(player.steam_id);
			}
		}
	}

	ImGui::Separator(); // Separate Allied and Opponent players

	ImGui::Text("Orange Team:");
	for (const auto& player : orangeTeamPlayers) {
		if (ImGui::Button(utf8_encode(player.name).c_str())) {
			handleClick(player);
			LOG(L"Orange team player: " + player.name);
		}
		if (player.platform == Platform::STEAM) {
			ImGui::SameLine();
			if (ImGui::Button("Open Steam profile")) {
				openSteamProfile(player.steam_id);
			}
		}
	}
}

/// <summary>
/// Use to render own tab in the settings menu.
/// </summary>
void TrackerCheck::RenderSettings() {
	const wchar_t* personal_website_url = L"https://www.tristanbony.me";
	const wchar_t* github_repo_url = L"https://github.com/TristanB0/TrackerCheck";

	ImGui::Text("Developed by Tristan Bony:");
	ImGui::SameLine();
	if (ImGui::Button("Visit my website")) {
		ShellExecute(NULL, NULL, personal_website_url, NULL, NULL, SW_SHOWNORMAL);
	}

	if (ImGui::Button("Open GitHub repository")) {
		ShellExecute(NULL, NULL, github_repo_url, NULL, NULL, SW_SHOWNORMAL);
	}

	ImGui::Text("Plugin Version: %s", plugin_version);
}
