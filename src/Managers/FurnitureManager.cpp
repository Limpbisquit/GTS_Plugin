#include "Managers/Animation/Utils/AnimationUtils.hpp"
#include "Managers/Animation/Utils/CrawlUtils.hpp"
#include "Managers/Damage/LaunchActor.hpp"
#include "Managers/FurnitureManager.hpp"
#include "Utils/ButtCrushUtils.hpp"
#include "Managers/Rumble.hpp"
#include "Data/Transient.hpp"

#include "Data/Tasks.hpp"

using namespace GTS;

namespace GTS_Markers {
    void GetFurnitureMarkerAnimations(RE::TESObjectREFR* ref) {
        if (!ref) {
            return;
        }

        auto root = ref->Get3D();
        if (!root) {
            return;
        }

        static constexpr std::array<const char*, 3> names = { "FURN", "FRN", "FurnitureMarker" };

        for (auto name : names) {
            VisitExtraData<RE::BSFurnitureMarkerNode>(root, name, [](NiAVObject& node, RE::BSFurnitureMarkerNode& data) {
                for (auto& marker : data.markers) {
                    auto animType = marker.animationType.get();
                    switch (animType) {
                    case RE::BSFurnitureMarker::AnimationType::kSit:
                        log::info("Marker: Sit");
                        break;
                    case RE::BSFurnitureMarker::AnimationType::kSleep:
                        log::info("Marker: Sleep");
                        break;
                    case RE::BSFurnitureMarker::AnimationType::kLean:
                        log::info("Marker: Lean");
                        break;
                    default:
                        log::info("Marker: Unknown ({})", static_cast<int>(animType));
                        break;
                    }
                }
                return true;
            });
        }
    }
}

namespace GTS_Hitboxes {
    void ApplySitDamage_Loop(Actor* giant) {
        float damage = GetButtCrushDamage(giant);
        for (auto Nodes: Butt_Zones) {
            auto Butt = find_node(giant, Nodes);
            if (Butt) {
                DoDamageAtPoint(giant, Radius_ButtCrush_Sit, Damage_ButtCrush_Idle * damage, Butt, 1000, 0.05f, 3.0f, DamageSource::Booty);
            }
        }
    } 

    void ApplySitDamage_Once(Actor* giant) {
        float damage = GetButtCrushDamage(giant);
        float perk = GetPerkBonus_Basics(giant);
        bool SMT = HasSMT(giant);

		float dust = SMT ? 1.25f : 1.0f;
		float smt = SMT ? 1.5f : 1.0f;

        float shake_power = Rumble_ButtCrush_Sit/2.0f * dust * damage;
        for (auto Nodes: Butt_Zones) {
            auto Butt = find_node(giant, Nodes);
            if (Butt) {
                DoDamageAtPoint(giant, Radius_ButtCrush_Sit, Damage_ButtCrush_Sit * damage, Butt, 4, 0.70f, 0.8f, DamageSource::Booty);
                Rumbling::Once("Butt_L", giant, shake_power * smt, 0.075f, "NPC R Butt", 0.0f);
                LaunchActor::GetSingleton().LaunchAtNode(giant, 1.3f * perk, 2.0f, Butt);
            }
        }
    } 

    void StartLoopDamage(Actor* actor) {

        std::string taskname = std::format("SitLoop_{}", actor->formID);
        ActorHandle giantHandle = actor->CreateRefHandle();

        TaskManager::Run(taskname, [=](auto& progressData){
            if (!giantHandle) {
                return false;
            }

            auto giant = giantHandle.get().get();

            ApplySitDamage_Loop(giant);

            return true;
        });
    }
}

namespace GTS {
    FurnitureManager& FurnitureManager::GetSingleton() {
		static FurnitureManager instance;
		return instance;
	}

	std::string FurnitureManager::DebugName() {
		return "::FurnitureManager";
	}

    void FurnitureManager::FurnitureEvent(RE::Actor* activator, TESObjectREFR* object, bool enter) {
        if (activator && object) {
            GTS_Markers::GetFurnitureMarkerAnimations(object);
        }
    }

    void FurnitureManager::Furniture_RecordTransientData(RE::Actor* activator, TESObjectREFR* object, bool enter) {
        // Purpose of this function was following:
        // - Offset characters forward when sitting on the furniture
        // - So Characters won't be sitting inside chairs for example
        // - Problem: player is fixed, but NPC's shift forward instead (ty Todd)
        // - Unused atm.
        // [ Search for these data-> stuff and uncommend them if you want to experiment with it ]
        auto data = Transient::GetSingleton().GetActorData(activator);
        if (data) {
            data->FurnitureScale = object->GetScale() / get_natural_scale(activator, true);
            data->UsingFurniture = enter;
        }
    }

    void FurnitureManager::Furniture_EnableButtHitboxes(RE::Actor* activator, FurnitureDamageSwitch type) {
        GTS_Hitboxes::ApplySitDamage_Once(activator);
        GTS_Hitboxes::StartLoopDamage(activator);

        if (type == FurnitureDamageSwitch::DisableDamage) {
            std::string taskname = std::format("SitLoop_{}", activator->formID);
            TaskManager::Cancel(taskname);
        }
    }
}