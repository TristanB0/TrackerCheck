#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "PlayerLookup.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class TrackerCheck : public BakkesMod::Plugin::BakkesModPlugin
	//, public SettingsWindowBase // Uncomment if you wanna render your own tab in the settings menu
	, public PluginWindowBase // Uncomment if you want to render your own plugin window
{

	std::shared_ptr<bool> enabled;
	bool isInterfaceVisible;

	void onLoad() override;
	//void onUnload() override; // Uncomment and implement if you need a unload method

	// Teams data
	std::vector<PlayerInfo> blueTeamPlayers;
	std::vector<PlayerInfo> orangeTeamPlayers;

	void fetchPlayerList();
	void handleClick(const PlayerInfo& p_info) const;

public:
	//void RenderSettings() override; // Uncomment if you wanna render your own tab in the settings menu
	void RenderWindow() override; // Uncomment if you want to render your own plugin window
};
