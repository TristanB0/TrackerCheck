#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "PlayerLookup.h"
#include "version.h"

#include "Windows.h"
#include "shellapi.h"

constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);
constexpr auto DEFAULT_BIND_KEY = "F7";

class TrackerCheck : public BakkesMod::Plugin::BakkesModPlugin
	, public SettingsWindowBase // Uncomment if you wanna render your own tab in the settings menu
	, public PluginWindowBase // Uncomment if you want to render your own plugin window
{
	//std::shared_ptr<bool> enabled;

	void onLoad() override;
	//void onUnload() override; // Uncomment and implement if you need a unload method

	bool is_spectator_visible_ = false;
	std::string bind_key_;

	// Teams data
	std::vector<PlayerInfo> blue_team_players_;
	std::vector<PlayerInfo> orange_team_players_;
	std::vector<PlayerInfo> spectators_;

	void fetch_players();
	void open_rl_tracker(const PlayerInfo& p_info) const;
	void open_steam_profile(const std::string steam_id) const;
	void render_teams(const std::vector<PlayerInfo>& players) const;

public:
	void RenderSettings() override; // Uncomment if you wanna render your own tab in the settings menu
	void RenderWindow() override; // Uncomment if you want to render your own plugin window
};

/// <summary>
/// Convert a wide string to a UTF-8 string.
/// Code by tfinniga: https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte
/// </summary>
/// <param name="wstr"></param>
/// <returns></returns>
inline std::string utf8_encode(const std::wstring& wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}
