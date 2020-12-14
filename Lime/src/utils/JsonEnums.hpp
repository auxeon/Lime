#ifndef JSONENUMS_HPP
#define JSONENUMS_HPP
#include "Pch.hpp"


#define REGISTER_STRING(x) {x,#x},

// GAMESTATES
NLOHMANN_JSON_SERIALIZE_ENUM(GameStates, {
	REGISTER_STRING(GS_START)
	REGISTER_STRING(GS_MENU)
	REGISTER_STRING(GS_LEVEL)
	REGISTER_STRING(GS_END)
});

// SHAPEID
NLOHMANN_JSON_SERIALIZE_ENUM(ShapeID, {
	REGISTER_STRING(SH_AABB)
	REGISTER_STRING(SH_CIRCLE)
	REGISTER_STRING(SH_OBB)
	REGISTER_STRING(SH_POLYGON)
	REGISTER_STRING(SH_TOTAL)
});

// PLAYERSTATES
NLOHMANN_JSON_SERIALIZE_ENUM(PlayerStates, {
	REGISTER_STRING(PS_IDLE)
	REGISTER_STRING(PS_RUN)
	REGISTER_STRING(PS_JUMP)
	REGISTER_STRING(PS_GLIDE)
	REGISTER_STRING(PS_GROUND)
	REGISTER_STRING(PS_TOTAL)
});

// MOUSEBUTTONS
NLOHMANN_JSON_SERIALIZE_ENUM(mouseButtons, {
	REGISTER_STRING(LB)
	REGISTER_STRING(MB)
	REGISTER_STRING(RB)
	REGISTER_STRING(TOTAL)
});

// CAMERAMOVEMENTS
NLOHMANN_JSON_SERIALIZE_ENUM(CameraMovements, {
	REGISTER_STRING(CM_FORWARD)
	REGISTER_STRING(CM_BACKWARD)
	REGISTER_STRING(CM_LEFT)
	REGISTER_STRING(CM_RIGHT)
	REGISTER_STRING(CM_UP)
	REGISTER_STRING(CM_DOWN)
	REGISTER_STRING(CM_TOTAL)
});

// EVENTID
NLOHMANN_JSON_SERIALIZE_ENUM(EventID,{
	// WINDOW
	REGISTER_STRING(E_WINDOW_QUIT)
	REGISTER_STRING(E_WINDOW_RESIZED)
		REGISTER_STRING(P_WINDOW_RESIZED_WIDTH)
		REGISTER_STRING(P_WINDOW_RESIZED_HEIGHT)
	// KEYBOARD
	REGISTER_STRING(E_WINDOW_KEY_PRESSED)
		REGISTER_STRING(P_WINDOW_KEY_PRESSED_KEYCODE)
	REGISTER_STRING(E_WINDOW_KEY_RELEASED)
		REGISTER_STRING(P_WINDOW_KEY_RELEASED_KEYCODE)
	REGISTER_STRING(E_WINDOW_KEY_TRIGGERED)
		REGISTER_STRING(P_WINDOW_KEY_TRIGGERED_KEYCODE)
	// MOUSE
	REGISTER_STRING(E_WINDOW_MOUSE_MOVE)
		REGISTER_STRING(P_WINDOW_MOUSE_MOVE_X)
		REGISTER_STRING(P_WINDOW_MOUSE_MOVE_Y)
	REGISTER_STRING(E_WINDOW_MOUSE_DOWN)
		REGISTER_STRING(P_WINDOW_MOUSE_DOWN_BUTTON)
		REGISTER_STRING(P_WINDOW_MOUSE_DOWN_X)
		REGISTER_STRING(P_WINDOW_MOUSE_DOWN_Y)
	REGISTER_STRING(E_WINDOW_MOUSE_UP)
		REGISTER_STRING(P_WINDOW_MOUSE_UP_BUTTON)
		REGISTER_STRING(P_WINDOW_MOUSE_UP_X)
		REGISTER_STRING(P_WINDOW_MOUSE_UP_Y)
	// GRAPHICS
	REGISTER_STRING(E_GRAPHICS_DEBUG_TOGGLE)
	// CAMERA
	REGISTER_STRING(E_GRAPHICS_CAMERA_UPDATED)
		REGISTER_STRING(P_GRAPHICS_CAMERA_UPDATED_ENTITYID)
	// BROADCAST EVENT
	REGISTER_STRING(E_BROADCAST_EVENT)
		REGISTER_STRING(P_BROADCAST_EVENT_DATA)
	// TIMED EVENTS
	REGISTER_STRING(E_TIMED_EVENT)
		REGISTER_STRING(P_TIMED_EVENT_TIME_START)
		REGISTER_STRING(P_TIMED_EVENT_TIME_EXEC)
		REGISTER_STRING(P_TIMED_EVENT_DATA)
	// DIRECTMESSAGE EVENTS
	REGISTER_STRING(E_DM_EVENT)
		REGISTER_STRING(P_DM_EVENT_ENTITYID)
		REGISTER_STRING(P_DM_EVENT_DATA)
	// GAMESTATE EVENTS
	REGISTER_STRING(E_GS_LEVEL)
		REGISTER_STRING(P_GS_LEVEL_NAME)
	// FIRE BULLET
	REGISTER_STRING(E_BULLET_FIRED)
		REGISTER_STRING(P_BULLET_FIRED_ORIGIN_ID)
	REGISTER_STRING(EP_TOTAL)
});


// SDLSCANCODES
NLOHMANN_JSON_SERIALIZE_ENUM(SDL_Scancode, {
	REGISTER_STRING(SDL_SCANCODE_UNKNOWN)
	REGISTER_STRING(SDL_SCANCODE_A)
	REGISTER_STRING(SDL_SCANCODE_B)
	REGISTER_STRING(SDL_SCANCODE_C)
	REGISTER_STRING(SDL_SCANCODE_D)
	REGISTER_STRING(SDL_SCANCODE_E)
	REGISTER_STRING(SDL_SCANCODE_F)
	REGISTER_STRING(SDL_SCANCODE_G)
	REGISTER_STRING(SDL_SCANCODE_H)
	REGISTER_STRING(SDL_SCANCODE_I)
	REGISTER_STRING(SDL_SCANCODE_J)
	REGISTER_STRING(SDL_SCANCODE_K)
	REGISTER_STRING(SDL_SCANCODE_L)
	REGISTER_STRING(SDL_SCANCODE_M)
	REGISTER_STRING(SDL_SCANCODE_N)
	REGISTER_STRING(SDL_SCANCODE_O)
	REGISTER_STRING(SDL_SCANCODE_P)
	REGISTER_STRING(SDL_SCANCODE_Q)
	REGISTER_STRING(SDL_SCANCODE_R)
	REGISTER_STRING(SDL_SCANCODE_S)
	REGISTER_STRING(SDL_SCANCODE_T)
	REGISTER_STRING(SDL_SCANCODE_U)
	REGISTER_STRING(SDL_SCANCODE_V)
	REGISTER_STRING(SDL_SCANCODE_W)
	REGISTER_STRING(SDL_SCANCODE_X)
	REGISTER_STRING(SDL_SCANCODE_Y)
	REGISTER_STRING(SDL_SCANCODE_Z)
	REGISTER_STRING(SDL_SCANCODE_1)
	REGISTER_STRING(SDL_SCANCODE_2)
	REGISTER_STRING(SDL_SCANCODE_3)
	REGISTER_STRING(SDL_SCANCODE_4)
	REGISTER_STRING(SDL_SCANCODE_5)
	REGISTER_STRING(SDL_SCANCODE_6)
	REGISTER_STRING(SDL_SCANCODE_7)
	REGISTER_STRING(SDL_SCANCODE_8)
	REGISTER_STRING(SDL_SCANCODE_9)
	REGISTER_STRING(SDL_SCANCODE_0)
	REGISTER_STRING(SDL_SCANCODE_RETURN)
	REGISTER_STRING(SDL_SCANCODE_ESCAPE)
	REGISTER_STRING(SDL_SCANCODE_BACKSPACE)
	REGISTER_STRING(SDL_SCANCODE_TAB)
	REGISTER_STRING(SDL_SCANCODE_SPACE)
	REGISTER_STRING(SDL_SCANCODE_MINUS)
	REGISTER_STRING(SDL_SCANCODE_EQUALS)
	REGISTER_STRING(SDL_SCANCODE_LEFTBRACKET)
	REGISTER_STRING(SDL_SCANCODE_RIGHTBRACKET)
	REGISTER_STRING(SDL_SCANCODE_BACKSLASH)
	REGISTER_STRING(SDL_SCANCODE_NONUSHASH)
	REGISTER_STRING(SDL_SCANCODE_SEMICOLON)
	REGISTER_STRING(SDL_SCANCODE_APOSTROPHE)
	REGISTER_STRING(SDL_SCANCODE_GRAVE)
	REGISTER_STRING(SDL_SCANCODE_COMMA)
	REGISTER_STRING(SDL_SCANCODE_PERIOD)
	REGISTER_STRING(SDL_SCANCODE_SLASH)
	REGISTER_STRING(SDL_SCANCODE_CAPSLOCK)
	REGISTER_STRING(SDL_SCANCODE_F1)
	REGISTER_STRING(SDL_SCANCODE_F2)
	REGISTER_STRING(SDL_SCANCODE_F3)
	REGISTER_STRING(SDL_SCANCODE_F4)
	REGISTER_STRING(SDL_SCANCODE_F5)
	REGISTER_STRING(SDL_SCANCODE_F6)
	REGISTER_STRING(SDL_SCANCODE_F7)
	REGISTER_STRING(SDL_SCANCODE_F8)
	REGISTER_STRING(SDL_SCANCODE_F9)
	REGISTER_STRING(SDL_SCANCODE_F10)
	REGISTER_STRING(SDL_SCANCODE_F11)
	REGISTER_STRING(SDL_SCANCODE_F12)
	REGISTER_STRING(SDL_SCANCODE_PRINTSCREEN)
	REGISTER_STRING(SDL_SCANCODE_SCROLLLOCK)
	REGISTER_STRING(SDL_SCANCODE_PAUSE)
	REGISTER_STRING(SDL_SCANCODE_INSERT)
	REGISTER_STRING(SDL_SCANCODE_HOME)
	REGISTER_STRING(SDL_SCANCODE_PAGEUP)
	REGISTER_STRING(SDL_SCANCODE_DELETE)
	REGISTER_STRING(SDL_SCANCODE_END)
	REGISTER_STRING(SDL_SCANCODE_PAGEDOWN)
	REGISTER_STRING(SDL_SCANCODE_RIGHT)
	REGISTER_STRING(SDL_SCANCODE_LEFT)
	REGISTER_STRING(SDL_SCANCODE_DOWN)
	REGISTER_STRING(SDL_SCANCODE_UP)
	REGISTER_STRING(SDL_SCANCODE_NUMLOCKCLEAR)
	REGISTER_STRING(SDL_SCANCODE_KP_DIVIDE)
	REGISTER_STRING(SDL_SCANCODE_KP_MULTIPLY)
	REGISTER_STRING(SDL_SCANCODE_KP_MINUS)
	REGISTER_STRING(SDL_SCANCODE_KP_PLUS)
	REGISTER_STRING(SDL_SCANCODE_KP_ENTER)
	REGISTER_STRING(SDL_SCANCODE_KP_1)
	REGISTER_STRING(SDL_SCANCODE_KP_2)
	REGISTER_STRING(SDL_SCANCODE_KP_3)
	REGISTER_STRING(SDL_SCANCODE_KP_4)
	REGISTER_STRING(SDL_SCANCODE_KP_5)
	REGISTER_STRING(SDL_SCANCODE_KP_6)
	REGISTER_STRING(SDL_SCANCODE_KP_7)
	REGISTER_STRING(SDL_SCANCODE_KP_8)
	REGISTER_STRING(SDL_SCANCODE_KP_9)
	REGISTER_STRING(SDL_SCANCODE_KP_0)
	REGISTER_STRING(SDL_SCANCODE_KP_PERIOD)
	REGISTER_STRING(SDL_SCANCODE_NONUSBACKSLASH)
	REGISTER_STRING(SDL_SCANCODE_APPLICATION)
	REGISTER_STRING(SDL_SCANCODE_POWER)
	REGISTER_STRING(SDL_SCANCODE_KP_EQUALS)
	REGISTER_STRING(SDL_SCANCODE_F13)
	REGISTER_STRING(SDL_SCANCODE_F14)
	REGISTER_STRING(SDL_SCANCODE_F15)
	REGISTER_STRING(SDL_SCANCODE_F16)
	REGISTER_STRING(SDL_SCANCODE_F17)
	REGISTER_STRING(SDL_SCANCODE_F18)
	REGISTER_STRING(SDL_SCANCODE_F19)
	REGISTER_STRING(SDL_SCANCODE_F20)
	REGISTER_STRING(SDL_SCANCODE_F21)
	REGISTER_STRING(SDL_SCANCODE_F22)
	REGISTER_STRING(SDL_SCANCODE_F23)
	REGISTER_STRING(SDL_SCANCODE_F24)
	REGISTER_STRING(SDL_SCANCODE_EXECUTE)
	REGISTER_STRING(SDL_SCANCODE_HELP)
	REGISTER_STRING(SDL_SCANCODE_MENU)
	REGISTER_STRING(SDL_SCANCODE_SELECT)
	REGISTER_STRING(SDL_SCANCODE_STOP)
	REGISTER_STRING(SDL_SCANCODE_AGAIN)
	REGISTER_STRING(SDL_SCANCODE_UNDO)
	REGISTER_STRING(SDL_SCANCODE_CUT)
	REGISTER_STRING(SDL_SCANCODE_COPY)
	REGISTER_STRING(SDL_SCANCODE_PASTE)
	REGISTER_STRING(SDL_SCANCODE_FIND)
	REGISTER_STRING(SDL_SCANCODE_MUTE)
	REGISTER_STRING(SDL_SCANCODE_VOLUMEUP)
	REGISTER_STRING(SDL_SCANCODE_VOLUMEDOWN)
	REGISTER_STRING(SDL_SCANCODE_KP_COMMA)
	REGISTER_STRING(SDL_SCANCODE_KP_EQUALSAS400)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL1)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL2)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL3)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL4)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL5)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL6)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL7)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL8)
	REGISTER_STRING(SDL_SCANCODE_INTERNATIONAL9)
	REGISTER_STRING(SDL_SCANCODE_LANG1)
	REGISTER_STRING(SDL_SCANCODE_LANG2)
	REGISTER_STRING(SDL_SCANCODE_LANG3)
	REGISTER_STRING(SDL_SCANCODE_LANG4)
	REGISTER_STRING(SDL_SCANCODE_LANG5)
	REGISTER_STRING(SDL_SCANCODE_LANG6)
	REGISTER_STRING(SDL_SCANCODE_LANG7)
	REGISTER_STRING(SDL_SCANCODE_LANG8)
	REGISTER_STRING(SDL_SCANCODE_LANG9)
	REGISTER_STRING(SDL_SCANCODE_ALTERASE)
	REGISTER_STRING(SDL_SCANCODE_SYSREQ)
	REGISTER_STRING(SDL_SCANCODE_CANCEL)
	REGISTER_STRING(SDL_SCANCODE_CLEAR)
	REGISTER_STRING(SDL_SCANCODE_PRIOR)
	REGISTER_STRING(SDL_SCANCODE_RETURN2)
	REGISTER_STRING(SDL_SCANCODE_SEPARATOR)
	REGISTER_STRING(SDL_SCANCODE_OUT)
	REGISTER_STRING(SDL_SCANCODE_OPER)
	REGISTER_STRING(SDL_SCANCODE_CLEARAGAIN)
	REGISTER_STRING(SDL_SCANCODE_CRSEL)
	REGISTER_STRING(SDL_SCANCODE_EXSEL)
	REGISTER_STRING(SDL_SCANCODE_KP_00)
	REGISTER_STRING(SDL_SCANCODE_KP_000)
	REGISTER_STRING(SDL_SCANCODE_THOUSANDSSEPARATOR)
	REGISTER_STRING(SDL_SCANCODE_DECIMALSEPARATOR)
	REGISTER_STRING(SDL_SCANCODE_CURRENCYUNIT)
	REGISTER_STRING(SDL_SCANCODE_CURRENCYSUBUNIT)
	REGISTER_STRING(SDL_SCANCODE_KP_LEFTPAREN)
	REGISTER_STRING(SDL_SCANCODE_KP_RIGHTPAREN)
	REGISTER_STRING(SDL_SCANCODE_KP_LEFTBRACE)
	REGISTER_STRING(SDL_SCANCODE_KP_RIGHTBRACE)
	REGISTER_STRING(SDL_SCANCODE_KP_TAB)
	REGISTER_STRING(SDL_SCANCODE_KP_BACKSPACE)
	REGISTER_STRING(SDL_SCANCODE_KP_A)
	REGISTER_STRING(SDL_SCANCODE_KP_B)
	REGISTER_STRING(SDL_SCANCODE_KP_C)
	REGISTER_STRING(SDL_SCANCODE_KP_D)
	REGISTER_STRING(SDL_SCANCODE_KP_E)
	REGISTER_STRING(SDL_SCANCODE_KP_F)
	REGISTER_STRING(SDL_SCANCODE_KP_XOR)
	REGISTER_STRING(SDL_SCANCODE_KP_POWER)
	REGISTER_STRING(SDL_SCANCODE_KP_PERCENT)
	REGISTER_STRING(SDL_SCANCODE_KP_LESS)
	REGISTER_STRING(SDL_SCANCODE_KP_GREATER)
	REGISTER_STRING(SDL_SCANCODE_KP_AMPERSAND)
	REGISTER_STRING(SDL_SCANCODE_KP_DBLAMPERSAND)
	REGISTER_STRING(SDL_SCANCODE_KP_VERTICALBAR)
	REGISTER_STRING(SDL_SCANCODE_KP_DBLVERTICALBAR)
	REGISTER_STRING(SDL_SCANCODE_KP_COLON)
	REGISTER_STRING(SDL_SCANCODE_KP_HASH)
	REGISTER_STRING(SDL_SCANCODE_KP_SPACE)
	REGISTER_STRING(SDL_SCANCODE_KP_AT)
	REGISTER_STRING(SDL_SCANCODE_KP_EXCLAM)
	REGISTER_STRING(SDL_SCANCODE_KP_MEMSTORE)
	REGISTER_STRING(SDL_SCANCODE_KP_MEMRECALL)
	REGISTER_STRING(SDL_SCANCODE_KP_MEMCLEAR)
	REGISTER_STRING(SDL_SCANCODE_KP_MEMADD)
	REGISTER_STRING(SDL_SCANCODE_KP_MEMSUBTRACT)
	REGISTER_STRING(SDL_SCANCODE_KP_MEMMULTIPLY)
	REGISTER_STRING(SDL_SCANCODE_KP_MEMDIVIDE)
	REGISTER_STRING(SDL_SCANCODE_KP_PLUSMINUS)
	REGISTER_STRING(SDL_SCANCODE_KP_CLEAR)
	REGISTER_STRING(SDL_SCANCODE_KP_CLEARENTRY)
	REGISTER_STRING(SDL_SCANCODE_KP_BINARY)
	REGISTER_STRING(SDL_SCANCODE_KP_OCTAL)
	REGISTER_STRING(SDL_SCANCODE_KP_DECIMAL)
	REGISTER_STRING(SDL_SCANCODE_KP_HEXADECIMAL)
	REGISTER_STRING(SDL_SCANCODE_LCTRL)
	REGISTER_STRING(SDL_SCANCODE_LSHIFT)
	REGISTER_STRING(SDL_SCANCODE_LALT)
	REGISTER_STRING(SDL_SCANCODE_LGUI)
	REGISTER_STRING(SDL_SCANCODE_RCTRL)
	REGISTER_STRING(SDL_SCANCODE_RSHIFT)
	REGISTER_STRING(SDL_SCANCODE_RALT)
	REGISTER_STRING(SDL_SCANCODE_RGUI)
	REGISTER_STRING(SDL_SCANCODE_MODE)
	REGISTER_STRING(SDL_SCANCODE_AUDIONEXT)
	REGISTER_STRING(SDL_SCANCODE_AUDIOPREV)
	REGISTER_STRING(SDL_SCANCODE_AUDIOSTOP)
	REGISTER_STRING(SDL_SCANCODE_AUDIOPLAY)
	REGISTER_STRING(SDL_SCANCODE_AUDIOMUTE)
	REGISTER_STRING(SDL_SCANCODE_MEDIASELECT)
	REGISTER_STRING(SDL_SCANCODE_WWW)
	REGISTER_STRING(SDL_SCANCODE_MAIL)
	REGISTER_STRING(SDL_SCANCODE_CALCULATOR)
	REGISTER_STRING(SDL_SCANCODE_COMPUTER)
	REGISTER_STRING(SDL_SCANCODE_AC_SEARCH)
	REGISTER_STRING(SDL_SCANCODE_AC_HOME)
	REGISTER_STRING(SDL_SCANCODE_AC_BACK)
	REGISTER_STRING(SDL_SCANCODE_AC_FORWARD)
	REGISTER_STRING(SDL_SCANCODE_AC_STOP)
	REGISTER_STRING(SDL_SCANCODE_AC_REFRESH)
	REGISTER_STRING(SDL_SCANCODE_AC_BOOKMARKS)
	REGISTER_STRING(SDL_SCANCODE_BRIGHTNESSDOWN)
	REGISTER_STRING(SDL_SCANCODE_BRIGHTNESSUP)
	REGISTER_STRING(SDL_SCANCODE_DISPLAYSWITCH)
	REGISTER_STRING(SDL_SCANCODE_KBDILLUMTOGGLE)
	REGISTER_STRING(SDL_SCANCODE_KBDILLUMDOWN)
	REGISTER_STRING(SDL_SCANCODE_KBDILLUMUP)
	REGISTER_STRING(SDL_SCANCODE_EJECT)
	REGISTER_STRING(SDL_SCANCODE_SLEEP)
	REGISTER_STRING(SDL_SCANCODE_APP1)
	REGISTER_STRING(SDL_SCANCODE_APP2)
	REGISTER_STRING(SDL_SCANCODE_AUDIOREWIND)
	REGISTER_STRING(SDL_SCANCODE_AUDIOFASTFORWARD)
	REGISTER_STRING(SDL_NUM_SCANCODES)	
});
	
	
#endif // !JSONENUMS_HPP
	