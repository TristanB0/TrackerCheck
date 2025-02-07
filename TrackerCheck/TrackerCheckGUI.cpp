#include "pch.h"
#include "TrackerCheck.h"

/// <summary>
/// Used to render own plugin window.
/// < / summary>
void TrackerCheck::RenderWindow() {
	ImGui::Text("Refresh players manually:");
	if (ImGui::Button("Refresh")) {
		LOG("Refreshing players.");
		TrackerCheck::fetch_players();
	}

	ImGui::Separator();

	ImGui::Text("Blue Team:");
	if (!blue_team_players.empty()) {
		render_teams(blue_team_players);
	}
	else {
		ImGui::Text("No players found.");
	}

	ImGui::Separator();

	ImGui::Text("Orange Team:");
	if (!orange_team_players.empty()) {
		render_teams(orange_team_players);
	}
	else {
		ImGui::Text("No players found.");
	}

	ImGui::Separator();

	ImGui::Text("Bots and Spectators:");
	if (!spectators.empty()) {
		render_teams(spectators);
	}
	else {
		ImGui::Text("No players found.");
	}
}

/// <summary>
/// Render players of a team.
/// </summary>
/// <param name="players"></param>
void TrackerCheck::render_teams(const std::vector<PlayerInfo>& players) const {
	for (const auto& player : players) {
		if (player.id == 0) {
			ImGui::Text("%s (Bot)", utf8_encode(player.name));
			continue;
		}
		if (ImGui::Button(utf8_encode(player.name).c_str())) {
			open_rl_tracker(player);
			LOG(L"Player: {}", player.name);
		}
		if (player.platform == Platform::STEAM) {
			ImGui::SameLine();
			if (ImGui::Button("Open Steam profile")) {
				open_steam_profile(player.steam_id);
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

	ImGui::Text("Developed by Tristan Bony");

	if (ImGui::Button("Visit my website")) {
		ShellExecute(NULL, NULL, personal_website_url, NULL, NULL, SW_SHOWNORMAL);
	}

	if (ImGui::Button("Open GitHub repository")) {
		ShellExecute(NULL, NULL, github_repo_url, NULL, NULL, SW_SHOWNORMAL);
	}

	ImGui::Text("Plugin Version: %s", plugin_version);
}
