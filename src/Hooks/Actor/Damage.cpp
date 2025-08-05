#include "Hooks/Actor/Damage.hpp"

#include "Config/Config.hpp"

#include "Managers/OverkillManager.hpp"
#include "Managers/Animation/Grab.hpp"
#include "Managers/Animation/HugShrink.hpp"
#include "Managers/Animation/Utils/CooldownManager.hpp"

#include "Utils/DifficultyUtils.hpp"
#include "Utils/ActorBools.hpp"
#include "Hooks/Util/HookUtil.hpp"

namespace {
	constexpr float AddToDamage = 1.75f; // It's needed so there's more room for error when calculating damage that should kill
}

namespace GTS {

	void CameraFOVTask_TP(Actor* actor, PlayerCamera* camera, TempActorData* data, bool AllowEdits) {
		std::string name = std::format("CheatDeath_TP_{}", actor->formID);
		ActorHandle gianthandle = actor->CreateRefHandle();

		if (AllowEdits) {
			camera->worldFOV *= 0.35f;
		}

		float DefaultTP = data->WorldFOVDefault;
		double Start = Time::WorldTimeElapsed();

		TaskManager::Run(name, [=](auto& progressData) {
			if (!gianthandle) {
				return false;
			}
			auto giantref = gianthandle.get().get();
			double Finish = Time::WorldTimeElapsed();

			if (AllowEdits) {
				camera->worldFOV += DefaultTP * 0.003f;
				if (camera->worldFOV >= DefaultTP) {
					camera->worldFOV = DefaultTP;
					return false; // stop it
				}
			} else {
				double timepassed = Finish - Start;
				if (timepassed > 2.6) {
					return false;
				}
			}
			return true;
		});
	}

	void CameraFOVTask_FP(Actor* actor, PlayerCamera* camera, TempActorData* data, bool AllowEdits) {
		std::string name = std::format("CheatDeath_FP_{}", actor->formID);
		ActorHandle gianthandle = actor->CreateRefHandle();

		camera->firstPersonFOV *= 0.35f;
		float DefaultFP = data->FPFOVDefault;

		double Start = Time::WorldTimeElapsed();

		TaskManager::Run(name,[=](auto& progressData) {
			if (!gianthandle) {
				return false;
			}

			auto giantref = gianthandle.get().get();
			double Finish = Time::WorldTimeElapsed();

			if (AllowEdits) {
				camera->firstPersonFOV += DefaultFP * 0.003f;
				if (camera->firstPersonFOV >= DefaultFP) {
					camera->firstPersonFOV = DefaultFP;
					return false; // stop it
				}
			} else {
				double timepassed = Finish - Start;
				if (timepassed > 2.6) {
					return false;
				}
			}
			return true;
		});
	}

	void DamageImmunityTask(Actor* actor, TempActorData* data) {
		std::string name = std::format("CheatDeath_Task_{}", actor->formID);
		ActorHandle gianthandle = actor->CreateRefHandle();

		double Start = Time::WorldTimeElapsed();

		TaskManager::Run(name,[=](auto& progressData) {
			if (!gianthandle) {
				return false;
			}

			auto giantref = gianthandle.get().get();
			double Finish = Time::WorldTimeElapsed();

			double timepassed = Finish - Start;
			if (timepassed > 2.5 || giantref->IsDead()) {
				if (data) {
					data->TemporaryDamageImmunity = false; // Vulnerable again
				}
				return false;
			}
			return true;
		});
	}

	void StartTemporaryDamageImmunity(Actor* actor) {
		if (actor->formID == 0x14) {
			auto camera = PlayerCamera::GetSingleton();
			if (!camera) {
				return;
			}
			auto AllowEdits = Config::GetGeneral().bEnableFOVEdits;

			auto tranData = Transient::GetSingleton().GetData(actor);
			bool TP = camera->IsInThirdPerson();
			bool FP = camera->IsInFirstPerson();
			if (tranData) {
				tranData->WorldFOVDefault = camera->worldFOV;
				tranData->FPFOVDefault = camera->firstPersonFOV;
				tranData->TemporaryDamageImmunity = true; // make actor immune to damage
				if (TP) {
					CameraFOVTask_TP(actor, camera, tranData, AllowEdits);
				} else if (FP) {
					CameraFOVTask_FP(actor, camera, tranData, AllowEdits);
				}
				DamageImmunityTask(actor, tranData);
			}
		}
	}

	void DoOverkill(Actor* attacker, Actor* receiver, float damage) {
		if (damage > GetMaxAV(receiver, ActorValue::kHealth)) { // Overkill effect
			float size_difference = GetSizeDifference(attacker, receiver, SizeType::VisualScale, true, false);
			if (size_difference >= 12.0f) {
				OverkillManager::GetSingleton().Overkill(attacker, receiver);
			}
		}
	}

	float TinyAsShield(Actor* receiver) {
		float protection = 1.0f;
		if (receiver->formID == 0x14) {
			auto grabbedActor = Grab::GetHeldActor(receiver);
			if (grabbedActor) {
				protection = 0.75f; // 25% damage reduction
			}
		}
		return protection;
	}

	bool HealthGateProtection(Actor* receiver, Actor* attacker, float a_damage) {
		bool NullifyDamage = false;
		if (receiver->formID == 0x14) {

			a_damage *= GetDifficultyMultiplier(attacker, receiver); // Take difficulty into account

			if (a_damage > GetAV(receiver, ActorValue::kHealth)) {
				if (Runtime::HasPerk(receiver, "GTSPerkHealthGate")) {
					if (!IsActionOnCooldown(receiver, CooldownSource::Action_HealthGate)) {
						ApplyActionCooldown(receiver, CooldownSource::Action_HealthGate);
						float maxhp = GetMaxAV(receiver, ActorValue::kHealth);
						float target = get_target_scale(receiver);
						float natural = get_natural_scale(receiver, true);

						float scale = get_visual_scale(receiver);

						update_target_scale(receiver, -0.35f * scale, SizeEffectType::kShrink);
						if ((target <= natural) || (target - 0.35f * scale <= natural)) {
							set_target_scale(receiver, natural); // to prevent becoming < natural scale
						}
						Runtime::PlaySound("GTSSoundTriggerHG", receiver, 2.0f, 0.5f);
						shake_camera(receiver, 1.7f, 1.5f);
						
						auto node = find_node(receiver, "NPC Root [Root]");
						if (node) {
							NiPoint3 position = node->world.translate;
							SpawnParticle(receiver, 6.00f, "GTS/Effects/TinyCalamity.nif", NiMatrix3(), position, scale * 5.0f, 7, nullptr); 
							SpawnParticle(receiver, 6.00f, "GTS/Effects/TinyCalamity.nif", NiMatrix3(), position, scale * 4.0f, 7, nullptr); 
							SpawnParticle(receiver, 6.00f, "GTS/Effects/TinyCalamity.nif", NiMatrix3(), position, scale * 3.0f, 7, nullptr); 
						}

						StaggerActor(receiver, attacker, 1.0f);
						StaggerActor(attacker, receiver, 1.0f);
						// stagger each-other

						StartTemporaryDamageImmunity(receiver); // Secondary source of damage immunity for all following hits for about 1.5 sec

						Cprint("Health Gate triggered, death avoided");
						Cprint("Damage: {:.2f}, Lost Size: {:.2f}", a_damage, -0.35f * scale);
						Notify("Health Gate triggered, death avoided");
						Notify("Damage: {:.2f}, Lost Size: {:.2f}", a_damage, -0.35f * scale);
						NullifyDamage = true; // First source of damage immunity for initial hit
					}
				}
			}
		}
		if (Runtime::HasPerk(receiver, "GTSPerkDarkArtsAug4") && GetHealthPercentage(receiver) <= 0.40f) {
			bool OnCooldown = IsActionOnCooldown(receiver, CooldownSource::Misc_ShrinkOutburst_Forced);
			if (!OnCooldown) {
				ApplyActionCooldown(receiver, CooldownSource::Misc_ShrinkOutburst_Forced);
				ShrinkOutburstExplosion(receiver, true);
			}
		}
		//log::info("Health Gate Activated: {}", NullifyDamage);
		return NullifyDamage;
	}

	float GetGrowthDamageResistance(Actor* receiver) {
		// Applies extra layer of damage reduction when Growth Animations are triggered
		// Growth animations = the ones that trigger randomly through Random Growth
		float reduction = 1.0f;
		if (IsGrowing(receiver)) {
			int growthtype = 0;
			receiver->GetGraphVariableInt("GTS_Growth_Roll", growthtype);
			if (growthtype > 0) {
				if (Runtime::HasPerk(receiver, "GTSPerkRandomGrowthAug")) {
					reduction -= 0.6f;
				}
				if (Runtime::HasPerk(receiver, "GTSPerkRandomGrowthTerror")) {
					reduction -= 0.25f;
				}
			}
		}
		return reduction;
	}

	float GetHugDamageResistance(Actor* receiver) {
		float reduction = 1.0f;
		// Applies extra layer of damage reduction when hugging someone
		if (HugShrink::GetHuggiesActor(receiver)) {
			if (Runtime::HasPerk(receiver, "GTSPerkHugsToughGrip")) {
				reduction -= 0.25f; // 25% resistance
			}
			if (Runtime::HasPerk(receiver, "GTSPerkHugsOfDeath")) {
				reduction -= 0.35f; // 35% additional resistance
			}
		}
		return reduction;
	}

	float GetTotalDamageResistance(Actor* receiver, Actor* aggressor) {
		float receiver_resistance = GetDamageResistance(receiver) * GetHugDamageResistance(receiver) * GetGrowthDamageResistance(receiver);
		float attacker_multiplier = GetDamageMultiplier(aggressor) / game_getactorscale(aggressor); // take GetScale into account since it boosts damage as well
		auto transient = Transient::GetSingleton().GetData(receiver);
		float tiny_resistance = 1.0f; // Tiny in hands takes portion of damage (25%) instead of GTS
		bool DamageImmunity = false;
		
		float TakenDamageMult = 1.0f; // 1.0 = take 100% damage

		if (transient) {
			if (receiver->formID == 0x14) {
				DamageImmunity = transient->TemporaryDamageImmunity;
				tiny_resistance = TinyAsShield(receiver);
			}
		}

		TakenDamageMult *= (attacker_multiplier * receiver_resistance * tiny_resistance);
		if (DamageImmunity) {
			TakenDamageMult *= 0.0f; // Fully immune to damage for 2.5 sec after triggering health gate
		}
		//log::info("DamageImmunity: {}", DamageImmunity);
		//log::info("Total DR: {}", TakenDamageMult);
		return TakenDamageMult;
	}

	void RecordPushForce(Actor* giant, Actor* tiny) {
		// Damage itself is called earlier than the push so we can just record that
		auto tranData = Transient::GetSingleton().GetData(giant);

        if (tranData) {
			float tiny_scale = get_visual_scale(tiny);
			float giant_scale = get_visual_scale(giant);
			
			if (HasSMT(giant)) {
			    giant_scale *= 2.5f;
		    }

			float difference = giant_scale/tiny_scale;
			float pushResult = 1.0f / (difference*difference*difference);
			float result = std::clamp(pushResult, 0.01f, 1.0f);

            tranData->PushForce = result;
        } 
	}

}

namespace Hooks {

	struct TakeDamage {

		static void thunk(Actor* a_this, float a_dmg, Actor* a_aggressor, uintptr_t a_hitdata, TESObjectREFR* a_damageSrc) {

			GTS_PROFILE_ENTRYPOINT("ActorDamage::TakeDamage");

			if (a_aggressor && a_aggressor != a_this) { // apply to hits only, we don't want to decrease fall damage for example

				const bool ShouldBeKilled = DontAlterDamage(a_this, a_dmg, AddToDamage);
				// ^ Attempt to fix being unkillable below 5% hp, the bug seems to be player exclusive
				/*if (a_this->formID == 0x14) {
					log::info("Damage Pre: {}", a_dmg);
					log::info("Should be killed: {}", ShouldBeKilled);
				}*/
				if (!ShouldBeKilled) {
					a_dmg *= GetTotalDamageResistance(a_this, a_aggressor);
					// ^ This function applies damage resistance from being large
					// Also makes receiver immune to all (?) damage for ~2.5 sec if health gate was triggered
				}

				if (HealthGateProtection(a_this, a_aggressor, a_dmg)) { // When Health Gate is true, initial hit full damage immunity is applied here 
					a_dmg *= 0.0f;
				}

				DoOverkill(a_aggressor, a_this, a_dmg);
				RecordPushForce(a_this, a_aggressor);
				
			}

			// This hook has a 'small' downside:
			// - Seems like if NPC is about to deal 250 damage and player has 5 health left: 
			//    - the game will cut excessive damage, so damage is now 5
			//    - then we further affect said 5 damage by damage resistance
			//    - which in some cases may make player unkillable since health never reaches 0...

			/*if (a_this->formID == 0x14) {
				log::info("Damage Post: {}", a_dmg);
			}*/

			func(a_this, a_dmg, a_aggressor, a_hitdata, a_damageSrc);

		}
		FUNCTYPE_DETOUR func;
	};

	
	void Hook_Damage::Install() {
		logger::info("Installing Character::TakeDamage Detour Hook...");
		stl::write_detour<TakeDamage>(REL::RelocationID(36345, 37335, NULL));
	}
}
