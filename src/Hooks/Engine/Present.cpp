#include "Hooks/Engine/Present.hpp"
#include "UI/UIManager.hpp"
#include "Hooks/Util/HookUtil.hpp"

namespace Hooks {

	//Win32 Window Message Handler
	struct WndProcHandler {

		static LRESULT thunk(HWND a_hwnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam) {

			GTS_PROFILE_ENTRYPOINT("EnginePresent::WndProcHandler");

			//On focus loss/gain
			if (a_msg == WM_ACTIVATEAPP) {

				auto& UIMgr = UIManager::GetSingleton();

				if (UIMgr.Ready()) {

					UIMgr.OnFocusLost();

					//IO can only be retrieved if a valid imgui context exists.
					auto& io = ImGui::GetIO();
					io.ClearInputCharacters();
					io.ClearInputKeys();

				}
			}

			return func(a_hwnd, a_msg, a_wParam, a_lParam);
		}

		FUNCTYPE_CALL func;

	};

	//DXGI Swapchain Create
	struct CreateD3DAndSwapChain {

		static void thunk() {

			GTS_PROFILE_ENTRYPOINT("EnginePresent::CreateD3DAndSwapChain");

			func();
			UIManager::GetSingleton().Init();
		}

		FUNCTYPE_CALL func;

	};

	//Win32 RegisterClassA
	struct RegisterClassA {

		static uint16_t thunk(WNDCLASSA* a_wndClass) {

			GTS_PROFILE_ENTRYPOINT("EnginePresent::RegisterClassA");

			WndProcHandler::func = reinterpret_cast<uintptr_t>(a_wndClass->lpfnWndProc);
			a_wndClass->lpfnWndProc = &WndProcHandler::thunk;
			return func(a_wndClass);
		}

		FUNCTYPE_CALL func;

	};

	//DXGISwapchain Present
	struct DXGISwapchainPresent {

		static void thunk(uint32_t unk_01) {

			GTS_PROFILE_ENTRYPOINT("EnginePresent::DXGISwapchainPresent");

			func(unk_01);

			if (UIManager::ShouldDrawOverTop) {
				UIManager::GetSingleton().Update();
			}

		}

		FUNCTYPE_CALL func;

	};


	//HudMenu Present
	struct HUDMenuPostDisplay {

		//Without the ShouldDrawOverTop check and both present hooks Settings must either draw over the hud or over everything
		//while only over the hud is fine for 99% of the time sometimes something will draw over the it and thus over the settings.
		//I don't know how to register a "HUD" element that could draw over all other hud elements so we'll do it this way.
		//The proper way to do this would be to have 2 imgui contexts for each "layer" but managing 2 of them needs a semi rewrite of all the custom helper functions

		//Updating earlier in the render pass allows us to auto hide everything when skyrim is doing its fade to black

		static constexpr std::size_t funcIndex = 0x06;

		static void thunk (RE::IMenu* a_menu) {

			GTS_PROFILE_ENTRYPOINT("EnginePresent::HUDMenuPostDisplay");

			func(a_menu);

			if (!UIManager::ShouldDrawOverTop) {
				UIManager::GetSingleton().Update();
			}
		}

		FUNCTYPE_VFUNC func;

	};

	void Hook_Present::Install() {

		logger::info("Installing Present Hooks...");

		stl::write_call<RegisterClassA, 6>(REL::RelocationID(75591, 77226, NULL), REL::VariantOffset(0x8E, 0x15C, NULL));
		stl::write_call<CreateD3DAndSwapChain>(REL::RelocationID(75595, 77226, NULL), REL::VariantOffset(0x9, 0x275, NULL));
		stl::write_call<DXGISwapchainPresent>(REL::RelocationID(75461, 77246, NULL), REL::VariantOffset(0x9, 0x9, NULL));
		stl::write_vfunc<HUDMenuPostDisplay>(VTABLE_HUDMenu[0]);

	}

}
