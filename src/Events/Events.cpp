#include "Events/Events.hpp"

namespace GTS {

	// Called on Live (non paused) gameplay
	void EventListener::Update() {}

	void EventListener::BoneUpdate() {}

	// Called on Papyrus OnUpdate
	void EventListener::PapyrusUpdate() {}

	// Called on Havok update (when processing hitjobs)
	void EventListener::HavokUpdate() {}

	// Called when the camera update event is fired (in the TESCameraState)
	void EventListener::CameraUpdate() {}

	// Called on game load started (not yet finished)
	// and when new game is selected
	void EventListener::Reset() {}

	// Called when game is enabled (while not paused)
	void EventListener::Enabled() {}

	// Called when game is disabled (while not paused)
	void EventListener::Disabled() {}

	// Called when a game is started after a load/newgame
	void EventListener::Start() {}

	// Called when all forms are loaded (during game load before mainmenu)
	void EventListener::DataReady() {}

	// Called when all forms are loaded (during game load before mainmenu)
	void EventListener::ResetActor(Actor* actor) {}

	// Called when an actor has an item equipped
	void EventListener::ActorEquip(Actor* actor) {}

	// Called when Player absorbs dragon soul
	void EventListener::DragonSoulAbsorption() {}

	// Called when an actor has is fully loaded
	void EventListener::ActorLoaded(Actor* actor) {}

	// Called when a papyrus hit event is fired
	void EventListener::HitEvent(const TESHitEvent* evt) {}

	// Called when an actor is squashed underfoot
	void EventListener::UnderFootEvent(const UnderFoot& evt) {}

	// Fired when a foot lands
	void EventListener::OnImpact(const Impact& impact) {}

	// Fired when a highheel is (un)equiped or when an actor is loaded with HH
	void EventListener::OnHighheelEquip(const HighheelEquip& evt) {}

	// Fired when a perk is added
	void EventListener::OnAddPerk(const AddPerkEvent& evt) {}

	// Fired when a perk about to be removed
	void EventListener::OnRemovePerk(const RemovePerkEvent& evt) {}

	// Fired when a skyrim menu event occurs
	void EventListener::MenuChange(const MenuOpenCloseEvent* menu_event) {}

	// Fired when a actor animation event occurs
	void EventListener::ActorAnimEvent(Actor* actor, const std::string_view& tag, const std::string_view& payload) {}

	// Fired when actor uses furniture
	void EventListener::FurnitureEvent(RE::Actor* user, TESObjectREFR* object, bool enter) {}

	void EventDispatcher::AddListener(EventListener* listener) {
		if (listener) {
			EventDispatcher::GetSingleton().listeners.push_back(listener);
		}
	}

	void EventDispatcher::DoUpdate() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->Update();
		}
	}

	void EventDispatcher::DoBoneUpdate() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->BoneUpdate();
			log::info("BoneUpdateRunning");
		}
	}

	void EventDispatcher::DoPapyrusUpdate() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->PapyrusUpdate();
		}
	}

	void EventDispatcher::DoHavokUpdate() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->HavokUpdate();
		}
	}

	void EventDispatcher::DoCameraUpdate() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->CameraUpdate();
		}
	}

	void EventDispatcher::DoReset() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->Reset();
		}
	}

	void EventDispatcher::DoEnabled() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->Enabled();
		}
	}
	void EventDispatcher::DoDisabled() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->Disabled();
		}
	}
	void EventDispatcher::DoStart() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->Start();
		}
	}

	void EventDispatcher::DoDataReady() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->DataReady();
		}
	}

	void EventDispatcher::DoResetActor(Actor* actor) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->ResetActor(actor);
		}
	}

	void EventDispatcher::DoActorEquip(Actor* actor) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->ActorEquip(actor);
		}
	}

	void EventDispatcher::DoDragonSoulAbsorption() {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->DragonSoulAbsorption();
		}
	}

	void EventDispatcher::DoActorLoaded(Actor* actor) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->ActorLoaded(actor);
		}
	}

	void EventDispatcher::DoHitEvent(const TESHitEvent* evt) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->HitEvent(evt);
		}
	}

	void EventDispatcher::DoUnderFootEvent(const UnderFoot& evt) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->UnderFootEvent(evt);
		}
	}

	void EventDispatcher::DoOnImpact(const Impact& impact) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->OnImpact(impact);
		}
	}

	void EventDispatcher::DoHighheelEquip(const HighheelEquip& evt) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->OnHighheelEquip(evt);
		}
	}

	void EventDispatcher::DoAddPerk(const AddPerkEvent& evt)  {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->OnAddPerk(evt);
		}
	}

	void EventDispatcher::DoRemovePerk(const RemovePerkEvent& evt)  {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->OnRemovePerk(evt);
		}
	}

	void EventDispatcher::DoMenuChange(const MenuOpenCloseEvent* menu_event) {
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->MenuChange(menu_event);
		}
	}

	void EventDispatcher::DoActorAnimEvent(Actor* actor, const BSFixedString& a_tag, const BSFixedString& a_payload) {
		std::string tag = a_tag.c_str();
		std::string payload = a_payload.c_str();
		for (auto listener: EventDispatcher::GetSingleton().listeners) {
			GTS_PROFILE_SCOPE(listener->DebugName());
			listener->ActorAnimEvent(actor, tag, payload);
		}
	}

	void EventDispatcher::DoFurnitureEvent(const TESFurnitureEvent* a_event) {
		Actor* actor = skyrim_cast<Actor*>(a_event->actor.get());
		TESObjectREFR* object = a_event->targetFurniture.get();
		log::info("Furniture Event Seen");
		log::info("Actor: {}", static_cast<bool>(actor != nullptr));
		log::info("Object: {}", static_cast<bool>(object != nullptr));
		if (actor && object) {
			log::info("Both are true");
			for (auto listener: EventDispatcher::GetSingleton().listeners) {
				GTS_PROFILE_SCOPE(listener->DebugName());
				listener->FurnitureEvent(actor, object, a_event->type == RE::TESFurnitureEvent::FurnitureEventType::kEnter);
			}
		}
	}

	EventDispatcher& EventDispatcher::GetSingleton() {
		static EventDispatcher instance;
		return instance;
	}
}
