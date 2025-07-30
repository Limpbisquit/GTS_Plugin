#pragma once

#include "UI/ImGui/Lib/imgui.h"

namespace GTS {

    #define IM_VK_KEYPAD_ENTER (VK_RETURN + 256)

	static ImGuiKey VirtualKeyToImGuiKey(WPARAM wParam) {

		switch (wParam) {
		case VK_TAB:
			return ImGuiKey_Tab;
		case VK_LEFT:
			return ImGuiKey_LeftArrow;
		case VK_RIGHT:
			return ImGuiKey_RightArrow;
		case VK_UP:
			return ImGuiKey_UpArrow;
		case VK_DOWN:
			return ImGuiKey_DownArrow;
		case VK_PRIOR:
			return ImGuiKey_PageUp;
		case VK_NEXT:
			return ImGuiKey_PageDown;
		case VK_HOME:
			return ImGuiKey_Home;
		case VK_END:
			return ImGuiKey_End;
		case VK_INSERT:
			return ImGuiKey_Insert;
		case VK_DELETE:
			return ImGuiKey_Delete;
		case VK_BACK:
			return ImGuiKey_Backspace;
		case VK_SPACE:
			return ImGuiKey_Space;
		case VK_RETURN:
			return ImGuiKey_Enter;
		case VK_ESCAPE:
			return ImGuiKey_Escape;
		case VK_OEM_7:
			return ImGuiKey_Apostrophe;
		case VK_OEM_COMMA:
			return ImGuiKey_Comma;
		case VK_OEM_MINUS:
			return ImGuiKey_Minus;
		case VK_OEM_PERIOD:
			return ImGuiKey_Period;
		case VK_OEM_2:
			return ImGuiKey_Slash;
		case VK_OEM_1:
			return ImGuiKey_Semicolon;
		case VK_OEM_PLUS:
			return ImGuiKey_Equal;
		case VK_OEM_4:
			return ImGuiKey_LeftBracket;
		case VK_OEM_5:
			return ImGuiKey_Backslash;
		case VK_OEM_6:
			return ImGuiKey_RightBracket;
		case VK_OEM_3:
			return ImGuiKey_GraveAccent;
		case VK_CAPITAL:
			return ImGuiKey_CapsLock;
		case VK_SCROLL:
			return ImGuiKey_ScrollLock;
		case VK_NUMLOCK:
			return ImGuiKey_NumLock;
		case VK_SNAPSHOT:
			return ImGuiKey_PrintScreen;
		case VK_PAUSE:
			return ImGuiKey_Pause;
		case VK_NUMPAD0:
			return ImGuiKey_Keypad0;
		case VK_NUMPAD1:
			return ImGuiKey_Keypad1;
		case VK_NUMPAD2:
			return ImGuiKey_Keypad2;
		case VK_NUMPAD3:
			return ImGuiKey_Keypad3;
		case VK_NUMPAD4:
			return ImGuiKey_Keypad4;
		case VK_NUMPAD5:
			return ImGuiKey_Keypad5;
		case VK_NUMPAD6:
			return ImGuiKey_Keypad6;
		case VK_NUMPAD7:
			return ImGuiKey_Keypad7;
		case VK_NUMPAD8:
			return ImGuiKey_Keypad8;
		case VK_NUMPAD9:
			return ImGuiKey_Keypad9;
		case VK_DECIMAL:
			return ImGuiKey_KeypadDecimal;
		case VK_DIVIDE:
			return ImGuiKey_KeypadDivide;
		case VK_MULTIPLY:
			return ImGuiKey_KeypadMultiply;
		case VK_SUBTRACT:
			return ImGuiKey_KeypadSubtract;
		case VK_ADD:
			return ImGuiKey_KeypadAdd;
		case IM_VK_KEYPAD_ENTER:
			return ImGuiKey_KeypadEnter;
		case VK_LSHIFT:
			return ImGuiKey_LeftShift;
		case VK_LCONTROL:
			return ImGuiKey_LeftCtrl;
		case VK_LMENU:
			return ImGuiKey_LeftAlt;
		case VK_LWIN:
			return ImGuiKey_LeftSuper;
		case VK_RSHIFT:
			return ImGuiKey_RightShift;
		case VK_RCONTROL:
			return ImGuiKey_RightCtrl;
		case VK_RMENU:
			return ImGuiKey_RightAlt;
		case VK_RWIN:
			return ImGuiKey_RightSuper;
		case VK_APPS:
			return ImGuiKey_Menu;
		case '0':
			return ImGuiKey_0;
		case '1':
			return ImGuiKey_1;
		case '2':
			return ImGuiKey_2;
		case '3':
			return ImGuiKey_3;
		case '4':
			return ImGuiKey_4;
		case '5':
			return ImGuiKey_5;
		case '6':
			return ImGuiKey_6;
		case '7':
			return ImGuiKey_7;
		case '8':
			return ImGuiKey_8;
		case '9':
			return ImGuiKey_9;
		case 'A':
			return ImGuiKey_A;
		case 'B':
			return ImGuiKey_B;
		case 'C':
			return ImGuiKey_C;
		case 'D':
			return ImGuiKey_D;
		case 'E':
			return ImGuiKey_E;
		case 'F':
			return ImGuiKey_F;
		case 'G':
			return ImGuiKey_G;
		case 'H':
			return ImGuiKey_H;
		case 'I':
			return ImGuiKey_I;
		case 'J':
			return ImGuiKey_J;
		case 'K':
			return ImGuiKey_K;
		case 'L':
			return ImGuiKey_L;
		case 'M':
			return ImGuiKey_M;
		case 'N':
			return ImGuiKey_N;
		case 'O':
			return ImGuiKey_O;
		case 'P':
			return ImGuiKey_P;
		case 'Q':
			return ImGuiKey_Q;
		case 'R':
			return ImGuiKey_R;
		case 'S':
			return ImGuiKey_S;
		case 'T':
			return ImGuiKey_T;
		case 'U':
			return ImGuiKey_U;
		case 'V':
			return ImGuiKey_V;
		case 'W':
			return ImGuiKey_W;
		case 'X':
			return ImGuiKey_X;
		case 'Y':
			return ImGuiKey_Y;
		case 'Z':
			return ImGuiKey_Z;
		case VK_F1:
			return ImGuiKey_F1;
		case VK_F2:
			return ImGuiKey_F2;
		case VK_F3:
			return ImGuiKey_F3;
		case VK_F4:
			return ImGuiKey_F4;
		case VK_F5:
			return ImGuiKey_F5;
		case VK_F6:
			return ImGuiKey_F6;
		case VK_F7:
			return ImGuiKey_F7;
		case VK_F8:
			return ImGuiKey_F8;
		case VK_F9:
			return ImGuiKey_F9;
		case VK_F10:
			return ImGuiKey_F10;
		case VK_F11:
			return ImGuiKey_F11;
		case VK_F12:
			return ImGuiKey_F12;
        case VK_F13:
			return ImGuiKey_F13;
		case VK_F14:
			return ImGuiKey_F14;
		case VK_F15:
			return ImGuiKey_F15;
		case VK_F16:
			return ImGuiKey_F16;
		case VK_F17:
			return ImGuiKey_F17;
		case VK_F18:
			return ImGuiKey_F18;
		case VK_F19:
			return ImGuiKey_F19;
		case VK_F20:
			return ImGuiKey_F20;
		case VK_F21:
			return ImGuiKey_F21;
		case VK_F22:
			return ImGuiKey_F22;
		case VK_F23:
			return ImGuiKey_F23;
		case VK_F24:
			return ImGuiKey_F24;
		default:
			return ImGuiKey_None;
		}
	}

    // This lookup table converts ImGui keys to the string representation of DirectInput keys,
    // with the "DIK_" prefix removed.
    //This is intended to be used with the existing way Inputmanager parses keys.
    //Which uses a dinput LUT from the wine project.
    //I mean we could just use dinput directly at this point...
    //But if it ain't broke don't fix it. Even if its a roundabout way of doing it...
    static std::string ImGuiKeyToDIKString(ImGuiKey key) {
        switch (key) {
            // Basic editing / navigation keys
            case ImGuiKey_Escape:      return "ESCAPE";
            case ImGuiKey_Tab:         return "TAB";
            case ImGuiKey_Backspace:   return "BACK";
            case ImGuiKey_Space:       return "SPACE";
            case ImGuiKey_Enter:       return "RETURN";
            case ImGuiKey_LeftArrow:   return "LEFT";
            case ImGuiKey_RightArrow:  return "RIGHT";
            case ImGuiKey_UpArrow:     return "UP";
            case ImGuiKey_DownArrow:   return "DOWN";
            case ImGuiKey_PageUp:      return "PAGEUP";
            case ImGuiKey_PageDown:    return "PAGEDOWN";
            case ImGuiKey_Home:        return "HOME";
            case ImGuiKey_End:         return "END";
            case ImGuiKey_Insert:      return "INSERT";
            case ImGuiKey_Delete:      return "DELETE";

            // Letters (A-Z)
            case ImGuiKey_A:           return "A";
            case ImGuiKey_B:           return "B";
            case ImGuiKey_C:           return "C";
            case ImGuiKey_D:           return "D";
            case ImGuiKey_E:           return "E";
            case ImGuiKey_F:           return "F";
            case ImGuiKey_G:           return "G";
            case ImGuiKey_H:           return "H";
            case ImGuiKey_I:           return "I";
            case ImGuiKey_J:           return "J";
            case ImGuiKey_K:           return "K";
            case ImGuiKey_L:           return "L";
            case ImGuiKey_M:           return "M";
            case ImGuiKey_N:           return "N";
            case ImGuiKey_O:           return "O";
            case ImGuiKey_P:           return "P";
            case ImGuiKey_Q:           return "Q";
            case ImGuiKey_R:           return "R";
            case ImGuiKey_S:           return "S";
            case ImGuiKey_T:           return "T";
            case ImGuiKey_U:           return "U";
            case ImGuiKey_V:           return "V";
            case ImGuiKey_W:           return "W";
            case ImGuiKey_X:           return "X";
            case ImGuiKey_Y:           return "Y";
            case ImGuiKey_Z:           return "Z";

            // Digits (0-9)
            case ImGuiKey_0:           return "0";
            case ImGuiKey_1:           return "1";
            case ImGuiKey_2:           return "2";
            case ImGuiKey_3:           return "3";
            case ImGuiKey_4:           return "4";
            case ImGuiKey_5:           return "5";
            case ImGuiKey_6:           return "6";
            case ImGuiKey_7:           return "7";
            case ImGuiKey_8:           return "8";
            case ImGuiKey_9:           return "9";

            // Function keys (F1-F24)
            case ImGuiKey_F1:          return "F1";
            case ImGuiKey_F2:          return "F2";
            case ImGuiKey_F3:          return "F3";
            case ImGuiKey_F4:          return "F4";
            case ImGuiKey_F5:          return "F5";
            case ImGuiKey_F6:          return "F6";
            case ImGuiKey_F7:          return "F7";
            case ImGuiKey_F8:          return "F8";
            case ImGuiKey_F9:          return "F9";
            case ImGuiKey_F10:         return "F10";
            case ImGuiKey_F11:         return "F11";
            case ImGuiKey_F12:         return "F12";
            case ImGuiKey_F13:         return "F13";
            case ImGuiKey_F14:         return "F14";
            case ImGuiKey_F15:         return "F15";
            case ImGuiKey_F16:         return "F16";
            case ImGuiKey_F17:         return "F17";
            case ImGuiKey_F18:         return "F18";
            case ImGuiKey_F19:         return "F19";
            case ImGuiKey_F20:         return "F20";
            case ImGuiKey_F21:         return "F21";
            case ImGuiKey_F22:         return "F22";
            case ImGuiKey_F23:         return "F23";
            case ImGuiKey_F24:         return "F24";

            // Keypad keys
            case ImGuiKey_Keypad0:         return "NUMPAD0";
            case ImGuiKey_Keypad1:         return "NUMPAD1";
            case ImGuiKey_Keypad2:         return "NUMPAD2";
            case ImGuiKey_Keypad3:         return "NUMPAD3";
            case ImGuiKey_Keypad4:         return "NUMPAD4";
            case ImGuiKey_Keypad5:         return "NUMPAD5";
            case ImGuiKey_Keypad6:         return "NUMPAD6";
            case ImGuiKey_Keypad7:         return "NUMPAD7";
            case ImGuiKey_Keypad8:         return "NUMPAD8";
            case ImGuiKey_Keypad9:         return "NUMPAD9";
            case ImGuiKey_KeypadDecimal:   return "NUMPAD_DECIMAL";
            case ImGuiKey_KeypadDivide:    return "NUMPAD_DIVIDE";
            case ImGuiKey_KeypadMultiply:  return "NUMPAD_MULTIPLY";
            case ImGuiKey_KeypadSubtract:  return "NUMPAD_SUBTRACT";
            case ImGuiKey_KeypadAdd:       return "NUMPAD_ADD";

            // Modifier keys
            case ImGuiKey_LeftShift:   return "LSHIFT";
            case ImGuiKey_LeftCtrl:    return "LCONTROL";
            case ImGuiKey_LeftAlt:     return "LALT";
            //case ImGuiKey_LeftSuper:   return "LWIN";
            case ImGuiKey_RightShift:  return "RSHIFT";
            case ImGuiKey_RightCtrl:   return "RCONTROL";
            case ImGuiKey_RightAlt:    return "RALT";
            //case ImGuiKey_RightSuper:  return "RWIN";

            // Application keys
            //case ImGuiKey_AppBack:     return "BROWSER_BACK";
            //case ImGuiKey_AppForward:  return "BROWSER_FORWARD";

            case ImGuiKey_MouseLeft:    return "LMB";  // DIK_ convention: Left Mouse Button
            case ImGuiKey_MouseRight:   return "RMB";  // Right Mouse Button
            case ImGuiKey_MouseMiddle:  return "MOUSE3";  // Middle Mouse Button (Scroll Wheel Click)
            case ImGuiKey_MouseX1:      return "MOUSE4";  // Extra Mouse Button 1 (Backward)
            case ImGuiKey_MouseX2:      return "MOUSE5";  // Extra Mouse Button 2 (Forward)

            default: return "INVALID";
        }
    }

	static uint32_t DIKToVK(uint32_t DIK) {
		switch (DIK) {
			case DIK_LEFTARROW:
				return VK_LEFT;
			case DIK_RIGHTARROW:
				return VK_RIGHT;
			case DIK_UPARROW:
				return VK_UP;
			case DIK_DOWNARROW:
				return VK_DOWN;
			case DIK_DELETE:
				return VK_DELETE;
			case DIK_END:
				return VK_END;
			case DIK_HOME:
				return VK_HOME;  // pos1
			case DIK_PRIOR:
				return VK_PRIOR;  // page up
			case DIK_NEXT:
				return VK_NEXT;  // page down
			case DIK_INSERT:
				return VK_INSERT;
			case DIK_NUMPAD0:
				return VK_NUMPAD0;
			case DIK_NUMPAD1:
				return VK_NUMPAD1;
			case DIK_NUMPAD2:
				return VK_NUMPAD2;
			case DIK_NUMPAD3:
				return VK_NUMPAD3;
			case DIK_NUMPAD4:
				return VK_NUMPAD4;
			case DIK_NUMPAD5:
				return VK_NUMPAD5;
			case DIK_NUMPAD6:
				return VK_NUMPAD6;
			case DIK_NUMPAD7:
				return VK_NUMPAD7;
			case DIK_NUMPAD8:
				return VK_NUMPAD8;
			case DIK_NUMPAD9:
				return VK_NUMPAD9;
			case DIK_DECIMAL:
				return VK_DECIMAL;
			case DIK_NUMPADENTER:
				return IM_VK_KEYPAD_ENTER;
			case DIK_RMENU:
				return VK_RMENU;  // right alt
			case DIK_RCONTROL:
				return VK_RCONTROL;  // right control
			case DIK_LWIN:
				return VK_LWIN;  // left win
			case DIK_RWIN:
				return VK_RWIN;  // right win
			case DIK_APPS:
				return VK_APPS;
			default:
				return DIK;
		}
	}

	class ImInput {

		private:

		class CharEvent final : public RE::InputEvent {
			public:
			uint32_t keyCode;
		};

		struct KeyEvent {

			explicit KeyEvent(const RE::ButtonEvent* a_event) :
				keyCode(a_event->GetIDCode()),
				device(a_event->GetDevice()),
				eventType(a_event->GetEventType()),
				value(a_event->Value()),
				heldDownSecs(a_event->HeldDuration()) {}

			explicit KeyEvent(const CharEvent* a_event) :
				keyCode(a_event->keyCode),
				device(a_event->GetDevice()),
				eventType(a_event->GetEventType()) {}

			[[nodiscard]] constexpr bool IsPressed() const noexcept {
				return value > 0.0F;
			}
			[[nodiscard]] constexpr bool IsRepeating() const noexcept {
				return heldDownSecs > 0.0F;
			}
			[[nodiscard]] constexpr bool IsDown() const noexcept {
				return IsPressed() && (heldDownSecs == 0.0F);
			}
			[[nodiscard]] constexpr bool IsHeld() const noexcept {
				return IsPressed() && IsRepeating();
			}
			[[nodiscard]] constexpr bool IsUp() const noexcept {
				return (value == 0.0F) && IsRepeating();
			}

			uint32_t keyCode;
			RE::INPUT_DEVICE device;
			RE::INPUT_EVENT_TYPE eventType;
			float value = 0;
			float heldDownSecs = 0;
		};

		std::shared_mutex InputMutex;
		std::vector<KeyEvent> KeyEventQueue {};

		public:

		void ProcessInputEventQueue();

		void OnFocusLost() {
			std::unique_lock<std::shared_mutex> mutex(InputMutex);
			KeyEventQueue.clear();
		}

		void ProcessInputEvents(RE::InputEvent* const* a_events) {

			for (auto it = *a_events; it; it = it->next) {
				if (it->GetEventType() != RE::INPUT_EVENT_TYPE::kButton && it->GetEventType() != RE::INPUT_EVENT_TYPE::kChar)  // we do not care about non button or char events
					continue;

				auto event = it->GetEventType() == RE::INPUT_EVENT_TYPE::kButton ? KeyEvent(static_cast<RE::ButtonEvent*>(it)) : KeyEvent(static_cast<CharEvent*>(it));

				{
					std::unique_lock<std::shared_mutex> mutex(InputMutex);
					KeyEventQueue.emplace_back(event);
				}
			}
		}
	};
}