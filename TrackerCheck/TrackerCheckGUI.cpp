#include "pch.h"
#include "TrackerCheck.h"

/// <summary>
/// Used to render own plugin window.
/// < / summary>
void TrackerCheck::RenderWindow() {
	ImGui::Text("Refresh players manually:");
	ImGui::SameLine();
	if (ImGui::Button("Refresh")) {
		LOG("Refreshing list of player.");
		TrackerCheck::fetch_players();
	}

	ImGui::Separator();

	ImGui::Text("Blue Team:");
	if (!blue_team_players_.empty()) {
		render_teams(blue_team_players_);
	}
	else {
		ImGui::Text("No players found.");
	}

	ImGui::Separator();

	ImGui::Text("Orange Team:");
	if (!orange_team_players_.empty()) {
		render_teams(orange_team_players_);
	}
	else {
		ImGui::Text("No players found.");
	}

	if (!is_spectator_visible_) {
		return;
	}

	ImGui::Separator();

	ImGui::Text("Spectators:");
	if (!spectators_.empty()) {
		render_teams(spectators_);
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
		if (player.in_game_id == 0) {
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
				open_steam_profile(player.platform_id);
			}
		}
	}
}

/// <summary>
/// Use to render own tab in the settings menu.
/// </summary>
void TrackerCheck::RenderSettings() {
	ImGui::Checkbox("Show spectators in pop-up window", &is_spectator_visible_);

	static char input_buffer[16] = "F7";
	ImGui::Text("Current binding: %s", bind_key_);
	ImGui::InputText("##bind_key_", input_buffer, IM_ARRAYSIZE(input_buffer));
	ImGui::SameLine();
	if (ImGui::Button("Set bind")) {
		cvarManager->removeBind(bind_key_);
		cvarManager->setBind(input_buffer, "open_trackercheck_ui");
		bind_key_ = input_buffer;
		LOG("Key bind changed to: {}", input_buffer);
	}

	if (ImGui::Button("Reset key bind")) {
		cvarManager->removeBind(bind_key_);
		bind_key_ = DEFAULT_BIND_KEY;
		cvarManager->setBind(bind_key_, "open_trackercheck_ui");
		LOG("Key bind reset.");
	}

	ImGui::Separator();

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
