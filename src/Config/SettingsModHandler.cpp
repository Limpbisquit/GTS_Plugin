#include "Config/SettingsModHandler.hpp"
#include "UI/ImGui/ImStyleManager.hpp"
#include "spdlog/spdlog.h"

namespace GTS {

	void HandleCameraTrackingReset() {

		if (!Config::GetGeneral().bTrackBonesDuringAnim) {
			auto actors = find_actors();
			for (auto actor : actors) {
				if (actor) {
					ResetCameraTracking(actor);
				}
			}
		}
	}

	void HandleHHReset() {

		if (!Config::GetGeneral().bHighheelsFurniture) {

			auto actors = find_actors();

			for (auto actor : actors) {
				if (!actor) {
					return;
				}

				for (bool person : {false, true}) {
					auto npc_root_node = find_node(actor, "NPC", person);
					if (npc_root_node && actor->GetOccupiedFurniture()) {
						npc_root_node->local.translate.z = 0.0f;
						update_node(npc_root_node);
					}
				}
			}
		}
	}

	void HandleSettingsReset() {

		Config::GetSingleton().ResetToDefaults();
		//Keybinds::GetSingleton().ResetKeybinds();
		ImStyleManager::GetSingleton().LoadStyle();

		spdlog::set_level(spdlog::level::from_str(Config::GetAdvanced().sLogLevel));

		// ----- If You need to do something when settings reset add it here.

		HandleHHReset();
		HandleCameraTrackingReset();

		Notify("Mod settings have been reset");
		logger::info("Mod Settings Reset");

	}

	void HandleSettingsRefresh() {
		ImStyleManager::GetSingleton().LoadStyle();
		spdlog::set_level(spdlog::level::from_str(Config::GetAdvanced().sLogLevel));
		HandleHHReset();
		HandleCameraTrackingReset();
		logger::trace("Settings Refreshed");
	}
}