#pragma once

namespace Kaleidoscope
{

	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
		
	} Key;


	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define KLD_KEY_SPACE           ::Kaleidoscope::Key::Space
#define KLD_KEY_APOSTROPHE      ::Kaleidoscope::Key::Apostrophe    /* ' */
#define KLD_KEY_COMMA           ::Kaleidoscope::Key::Comma         /* , */
#define KLD_KEY_MINUS           ::Kaleidoscope::Key::Minus         /* - */
#define KLD_KEY_PERIOD          ::Kaleidoscope::Key::Period        /* . */
#define KLD_KEY_SLASH           ::Kaleidoscope::Key::Slash         /* / */
#define KLD_KEY_0               ::Kaleidoscope::Key::D0
#define KLD_KEY_1               ::Kaleidoscope::Key::D1
#define KLD_KEY_2               ::Kaleidoscope::Key::D2
#define KLD_KEY_3               ::Kaleidoscope::Key::D3
#define KLD_KEY_4               ::Kaleidoscope::Key::D4
#define KLD_KEY_5               ::Kaleidoscope::Key::D5
#define KLD_KEY_6               ::Kaleidoscope::Key::D6
#define KLD_KEY_7               ::Kaleidoscope::Key::D7
#define KLD_KEY_8               ::Kaleidoscope::Key::D8
#define KLD_KEY_9               ::Kaleidoscope::Key::D9
#define KLD_KEY_SEMICOLON       ::Kaleidoscope::Key::Semicolon     /* ; */
#define KLD_KEY_EQUAL           ::Kaleidoscope::Key::Equal         /* = */
#define KLD_KEY_A               ::Kaleidoscope::Key::A
#define KLD_KEY_B               ::Kaleidoscope::Key::B
#define KLD_KEY_C               ::Kaleidoscope::Key::C
#define KLD_KEY_D               ::Kaleidoscope::Key::D
#define KLD_KEY_E               ::Kaleidoscope::Key::E
#define KLD_KEY_F               ::Kaleidoscope::Key::F
#define KLD_KEY_G               ::Kaleidoscope::Key::G
#define KLD_KEY_H               ::Kaleidoscope::Key::H
#define KLD_KEY_I               ::Kaleidoscope::Key::I
#define KLD_KEY_J               ::Kaleidoscope::Key::J
#define KLD_KEY_K               ::Kaleidoscope::Key::K
#define KLD_KEY_L               ::Kaleidoscope::Key::L
#define KLD_KEY_M               ::Kaleidoscope::Key::M
#define KLD_KEY_N               ::Kaleidoscope::Key::N
#define KLD_KEY_O               ::Kaleidoscope::Key::O
#define KLD_KEY_P               ::Kaleidoscope::Key::P
#define KLD_KEY_Q               ::Kaleidoscope::Key::Q
#define KLD_KEY_R               ::Kaleidoscope::Key::R
#define KLD_KEY_S               ::Kaleidoscope::Key::S
#define KLD_KEY_T               ::Kaleidoscope::Key::T
#define KLD_KEY_U               ::Kaleidoscope::Key::U
#define KLD_KEY_V               ::Kaleidoscope::Key::V
#define KLD_KEY_W               ::Kaleidoscope::Key::W
#define KLD_KEY_X               ::Kaleidoscope::Key::X
#define KLD_KEY_Y               ::Kaleidoscope::Key::Y
#define KLD_KEY_Z               ::Kaleidoscope::Key::Z
#define KLD_KEY_LEFT_BRACKET    ::Kaleidoscope::Key::LeftBracket   /* [ */
#define KLD_KEY_BACKSLASH       ::Kaleidoscope::Key::Backslash     /* \ */
#define KLD_KEY_RIGHT_BRACKET   ::Kaleidoscope::Key::RightBracket  /* ] */
#define KLD_KEY_GRAVE_ACCENT    ::Kaleidoscope::Key::GraveAccent   /* ` */
#define KLD_KEY_WORLD_1         ::Kaleidoscope::Key::World1        /* non-US #1 */
#define KLD_KEY_WORLD_2         ::Kaleidoscope::Key::World2        /* non-US #2 */

/* Function keys */
#define KLD_KEY_ESCAPE          ::Kaleidoscope::Key::Escape
#define KLD_KEY_ENTER           ::Kaleidoscope::Key::Enter
#define KLD_KEY_TAB             ::Kaleidoscope::Key::Tab
#define KLD_KEY_BACKSPACE       ::Kaleidoscope::Key::Backspace
#define KLD_KEY_INSERT          ::Kaleidoscope::Key::Insert
#define KLD_KEY_DELETE          ::Kaleidoscope::Key::Delete
#define KLD_KEY_RIGHT           ::Kaleidoscope::Key::Right
#define KLD_KEY_LEFT            ::Kaleidoscope::Key::Left
#define KLD_KEY_DOWN            ::Kaleidoscope::Key::Down
#define KLD_KEY_UP              ::Kaleidoscope::Key::Up
#define KLD_KEY_PAGE_UP         ::Kaleidoscope::Key::PageUp
#define KLD_KEY_PAGE_DOWN       ::Kaleidoscope::Key::PageDown
#define KLD_KEY_HOME            ::Kaleidoscope::Key::Home
#define KLD_KEY_END             ::Kaleidoscope::Key::End
#define KLD_KEY_CAPS_LOCK       ::Kaleidoscope::Key::CapsLock
#define KLD_KEY_SCROLL_LOCK     ::Kaleidoscope::Key::ScrollLock
#define KLD_KEY_NUM_LOCK        ::Kaleidoscope::Key::NumLock
#define KLD_KEY_PRINT_SCREEN    ::Kaleidoscope::Key::PrintScreen
#define KLD_KEY_PAUSE           ::Kaleidoscope::Key::Pause
#define KLD_KEY_F1              ::Kaleidoscope::Key::F1
#define KLD_KEY_F2              ::Kaleidoscope::Key::F2
#define KLD_KEY_F3              ::Kaleidoscope::Key::F3
#define KLD_KEY_F4              ::Kaleidoscope::Key::F4
#define KLD_KEY_F5              ::Kaleidoscope::Key::F5
#define KLD_KEY_F6              ::Kaleidoscope::Key::F6
#define KLD_KEY_F7              ::Kaleidoscope::Key::F7
#define KLD_KEY_F8              ::Kaleidoscope::Key::F8
#define KLD_KEY_F9              ::Kaleidoscope::Key::F9
#define KLD_KEY_F10             ::Kaleidoscope::Key::F10
#define KLD_KEY_F11             ::Kaleidoscope::Key::F11
#define KLD_KEY_F12             ::Kaleidoscope::Key::F12
#define KLD_KEY_F13             ::Kaleidoscope::Key::F13
#define KLD_KEY_F14             ::Kaleidoscope::Key::F14
#define KLD_KEY_F15             ::Kaleidoscope::Key::F15
#define KLD_KEY_F16             ::Kaleidoscope::Key::F16
#define KLD_KEY_F17             ::Kaleidoscope::Key::F17
#define KLD_KEY_F18             ::Kaleidoscope::Key::F18
#define KLD_KEY_F19             ::Kaleidoscope::Key::F19
#define KLD_KEY_F20             ::Kaleidoscope::Key::F20
#define KLD_KEY_F21             ::Kaleidoscope::Key::F21
#define KLD_KEY_F22             ::Kaleidoscope::Key::F22
#define KLD_KEY_F23             ::Kaleidoscope::Key::F23
#define KLD_KEY_F24             ::Kaleidoscope::Key::F24
#define KLD_KEY_F25             ::Kaleidoscope::Key::F25

/* Keypad */
#define KLD_KEY_KP_0            ::Kaleidoscope::Key::KP0
#define KLD_KEY_KP_1            ::Kaleidoscope::Key::KP1
#define KLD_KEY_KP_2            ::Kaleidoscope::Key::KP2
#define KLD_KEY_KP_3            ::Kaleidoscope::Key::KP3
#define KLD_KEY_KP_4            ::Kaleidoscope::Key::KP4
#define KLD_KEY_KP_5            ::Kaleidoscope::Key::KP5
#define KLD_KEY_KP_6            ::Kaleidoscope::Key::KP6
#define KLD_KEY_KP_7            ::Kaleidoscope::Key::KP7
#define KLD_KEY_KP_8            ::Kaleidoscope::Key::KP8
#define KLD_KEY_KP_9            ::Kaleidoscope::Key::KP9
#define KLD_KEY_KP_DECIMAL      ::Kaleidoscope::Key::KPDecimal
#define KLD_KEY_KP_DIVIDE       ::Kaleidoscope::Key::KPDivide
#define KLD_KEY_KP_MULTIPLY     ::Kaleidoscope::Key::KPMultiply
#define KLD_KEY_KP_SUBTRACT     ::Kaleidoscope::Key::KPSubtract
#define KLD_KEY_KP_ADD          ::Kaleidoscope::Key::KPAdd
#define KLD_KEY_KP_ENTER        ::Kaleidoscope::Key::KPEnter
#define KLD_KEY_KP_EQUAL        ::Kaleidoscope::Key::KPEqual

#define KLD_KEY_LEFT_SHIFT      ::Kaleidoscope::Key::LeftShift
#define KLD_KEY_LEFT_CONTROL    ::Kaleidoscope::Key::LeftControl
#define KLD_KEY_LEFT_ALT        ::Kaleidoscope::Key::LeftAlt
#define KLD_KEY_LEFT_SUPER      ::Kaleidoscope::Key::LeftSuper
#define KLD_KEY_RIGHT_SHIFT     ::Kaleidoscope::Key::RightShift
#define KLD_KEY_RIGHT_CONTROL   ::Kaleidoscope::Key::RightControl
#define KLD_KEY_RIGHT_ALT       ::Kaleidoscope::Key::RightAlt
#define KLD_KEY_RIGHT_SUPER     ::Kaleidoscope::Key::RightSuper
#define KLD_KEY_MENU            ::Kaleidoscope::Key::Menu