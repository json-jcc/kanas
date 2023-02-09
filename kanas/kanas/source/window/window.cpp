#include "window.h"

enum class EKeyAction
{
	Press = GLFW_PRESS,
	Release = GLFW_RELEASE,
	Repeat = GLFW_REPEAT
};

enum class EKey
{
	Key_Space = GLFW_KEY_SPACE,
	Key_Apostrophe = GLFW_KEY_APOSTROPHE, // '
	Key_Comma = GLFW_KEY_COMMA, // ,
	Key_Minus = GLFW_KEY_MINUS, //   -   
	Key_Period = GLFW_KEY_PERIOD, // .    
	Key_Slash = GLFW_KEY_SLASH, // /      
	Key_0 = GLFW_KEY_0,
	Key_1 = GLFW_KEY_1,
	Key_2 = GLFW_KEY_2,
	Key_3 = GLFW_KEY_3,
	Key_4 = GLFW_KEY_4,
	Key_5 = GLFW_KEY_5,
	Key_6 = GLFW_KEY_6,
	Key_7 = GLFW_KEY_7,
	Key_8 = GLFW_KEY_8,
	Key_9 = GLFW_KEY_9,
	Key_Semicolon = GLFW_KEY_SEMICOLON, // ;
	Equal = GLFW_KEY_EQUAL, // =

	Key_A = GLFW_KEY_A,
	Key_B = GLFW_KEY_B,
	Key_C = GLFW_KEY_C,
	Key_D = GLFW_KEY_D,
	Key_E = GLFW_KEY_E,
	Key_F = GLFW_KEY_F,
	Key_G = GLFW_KEY_G,
	Key_H = GLFW_KEY_H,
	Key_I = GLFW_KEY_I,
	Key_J = GLFW_KEY_J,
	Key_K = GLFW_KEY_K,
	Key_L = GLFW_KEY_L,
	Key_M = GLFW_KEY_M,
	Key_N = GLFW_KEY_N,
	Key_O = GLFW_KEY_O,
	Key_P = GLFW_KEY_P,
	Key_Q = GLFW_KEY_Q,
	Key_R = GLFW_KEY_R,
	Key_S = GLFW_KEY_S,
	Key_T = GLFW_KEY_T,
	Key_U = GLFW_KEY_U,
	Key_V = GLFW_KEY_V,
	Key_W = GLFW_KEY_W,
	Key_X = GLFW_KEY_X,
	Key_Y = GLFW_KEY_Y,
	Key_Z = GLFW_KEY_Z,

	Key_Left_Bracket = GLFW_KEY_LEFT_BRACKET, // [
	Key_Backslash = GLFW_KEY_BACKSLASH, // '\'
	Key_Right_Bracket = GLFW_KEY_RIGHT_BRACKET, // ]
	Key_Grave_Accent = GLFW_KEY_GRAVE_ACCENT, // `
	Key_World_1 = GLFW_KEY_WORLD_1, //         
	Key_World_2 = GLFW_KEY_WORLD_2, //         

	// ------------------------------------------------------
	Key_Escape = GLFW_KEY_ESCAPE, // esc
	Key_Enter = GLFW_KEY_ENTER, // enter
	Key_Tab = GLFW_KEY_TAB, // tab
	Key_Backspace = GLFW_KEY_BACKSPACE, // back space
	Key_Insert = GLFW_KEY_INSERT, //        
	Key_Delete = GLFW_KEY_DELETE,
	Key_Right = GLFW_KEY_RIGHT,
	Key_Left = GLFW_KEY_LEFT,
	Key_Down = GLFW_KEY_DOWN,
	Key_Up = GLFW_KEY_UP,
	Key_Page_Up = GLFW_KEY_PAGE_UP,
	Key_Page_Down = GLFW_KEY_PAGE_DOWN,
	Key_Home = GLFW_KEY_HOME,
	Key_End = GLFW_KEY_END,
	Key_Caps_Lock = GLFW_KEY_CAPS_LOCK,
	Key_Scroll_Lock = GLFW_KEY_SCROLL_LOCK,
	Key_Num_Lock = GLFW_KEY_NUM_LOCK,
	Key_Print_Screen = GLFW_KEY_PRINT_SCREEN,
	Key_Pause = GLFW_KEY_PAUSE,
	Key_F1 = GLFW_KEY_F1,
	Key_F2 = GLFW_KEY_F2,
	Key_F3 = GLFW_KEY_F3,
	Key_F4 = GLFW_KEY_F4,
	Key_F5 = GLFW_KEY_F5,
	Key_F6 = GLFW_KEY_F6,
	Key_F7 = GLFW_KEY_F7,
	Key_F8 = GLFW_KEY_F8,
	Key_F9 = GLFW_KEY_F9,
	Key_F10 = GLFW_KEY_F10,
	Key_F11 = GLFW_KEY_F11,
	Key_F12 = GLFW_KEY_F12,
	Key_F13 = GLFW_KEY_F13,
	Key_F14 = GLFW_KEY_F14,
	Key_F15 = GLFW_KEY_F15,
	Key_F16 = GLFW_KEY_F16,
	Key_F17 = GLFW_KEY_F17,
	Key_F18 = GLFW_KEY_F18,
	Key_F19 = GLFW_KEY_F19,
	Key_F20 = GLFW_KEY_F20,
	Key_F21 = GLFW_KEY_F21,
	Key_F22 = GLFW_KEY_F22,
	Key_F23 = GLFW_KEY_F23,
	Key_F24 = GLFW_KEY_F24,
	Key_F25 = GLFW_KEY_F25,

	Key_KP_0 = GLFW_KEY_KP_0,
	Key_KP_1 = GLFW_KEY_KP_1,
	Key_KP_2 = GLFW_KEY_KP_2,
	Key_KP_3 = GLFW_KEY_KP_3,
	Key_KP_4 = GLFW_KEY_KP_4,
	Key_KP_5 = GLFW_KEY_KP_5,
	Key_KP_6 = GLFW_KEY_KP_6,
	Key_KP_7 = GLFW_KEY_KP_7,
	Key_KP_8 = GLFW_KEY_KP_8,
	Key_KP_9 = GLFW_KEY_KP_9,
	Key_KP_Decimal = GLFW_KEY_KP_DECIMAL,
	Key_KP_Divide = GLFW_KEY_KP_DIVIDE,
	Key_KP_Multiply = GLFW_KEY_KP_MULTIPLY,
	Key_KP_Subtract = GLFW_KEY_KP_SUBTRACT,
	Key_KP_Add = GLFW_KEY_KP_ADD,
	Key_KP_ENTER = GLFW_KEY_KP_ENTER,
	Key_KP_Eequal = GLFW_KEY_KP_EQUAL,

	Key_Left_Shift = GLFW_KEY_LEFT_SHIFT,
	Key_Left_Control = GLFW_KEY_LEFT_CONTROL,
	Key_Left_Alt = GLFW_KEY_LEFT_ALT,
	Key_Left_Super = GLFW_KEY_LEFT_SUPER,
	Key_Right_Shift = GLFW_KEY_RIGHT_SHIFT,
	Key_Right_Control = GLFW_KEY_RIGHT_CONTROL,
	Key_Right_Alt = GLFW_KEY_RIGHT_ALT,
	Key_Right_Super = GLFW_KEY_RIGHT_SUPER,
	Key_Menu = GLFW_KEY_MENU,
	Key_Last = GLFW_KEY_LAST,
};

void window_close_callback(GLFWwindow* window)
{
	//glfwSetWindowShouldClose(window, GLFW_FALSE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
{
	//set_interface_scale(xscale, yscale);
}

void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q )
	{
		if (action == GLFW_PRESS) {}
		
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_U && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_O && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_P&& action == GLFW_PRESS) {}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_G && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_H && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_K && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {}


	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {}


	if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F3 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F4 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F6 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F7 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F9 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F10 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {}

}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	/*if (button == glfw_mouse_button_right && action == glfw_press)
		popup_menu();*/
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void joystick_callback(int jid, int event)
{
	if (event == GLFW_CONNECTED)
	{
		// The joystick was connected
	}
	else if (event == GLFW_DISCONNECTED)
	{
		// The joystick was disconnected
	}
}

void glfw_window::load_context()
{
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); //大小可调整
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE); // 创建时是否显示
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE); //是否有边框装饰
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE); // 创建时是否获得输入焦点
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE); //切换桌面是否自动图标化
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // 创建时是否浮于最前
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // 创建时是否最大化
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE); //创建时鼠标是否居中
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // 帧缓冲区是否启用alpha通道
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE); //
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE); //

	_windowed_width = 0;
	_windowed_width = 0;

	// fetch all monitors and their video modes
	int count;
	GLFWmonitor** monitors =  glfwGetMonitors(&count);
	if (count > 0)
	{
		PrimaryMonitorMode.first = monitors[0];
		PrimaryMonitorMode.second = glfwGetVideoMode(PrimaryMonitorMode.first);

		for (size_t i = 1; i < count; i++)
			OtherMonitorModes.push_back(MonitorMode(monitors[i], glfwGetVideoMode(monitors[i])));
	}
	auto PrimaryMonitor = PrimaryMonitorMode.first;
	auto PrimaryVideoMode = PrimaryMonitorMode.second;

	// set window hint and create primary window
	if (PrimaryMonitor) {
		glfwWindowHint(GLFW_RED_BITS, PrimaryVideoMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, PrimaryVideoMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, PrimaryVideoMode->blueBits);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_DEPTH_BITS, 24); //32
		glfwWindowHint(GLFW_STENCIL_BITS, 8);
		glfwWindowHint(GLFW_ACCUM_RED_BITS, 0);//
		glfwWindowHint(GLFW_ACCUM_GREEN_BITS, 0);
		glfwWindowHint(GLFW_ACCUM_BLUE_BITS, 0);
		glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, 0);
		glfwWindowHint(GLFW_AUX_BUFFERS, 0); //
		glfwWindowHint(GLFW_SAMPLES, 0);
		glfwWindowHint(GLFW_REFRESH_RATE, PrimaryVideoMode->refreshRate); //
		glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
		glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
		glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_ANY_RELEASE_BEHAVIOR);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
		glfwWindowHintString(GLFW_COCOA_FRAME_NAME, "");
		glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_FALSE);
		glfwWindowHintString(GLFW_X11_CLASS_NAME, "");
		glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "");

		is_full_screen = true;
		_window = glfwCreateWindow(PrimaryVideoMode->width, PrimaryVideoMode->height, "default glfw window", NULL, NULL); // default init by full screen
	}

	if (_window == NULL) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(_window);
	glfwGetFramebufferSize(_window, &_framebuffer_width, &_framebuffer_height);

	set_callback();
	set_input_mode();
}

void glfw_window::tick(float DeltaTime)
{
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void glfw_window::switch_windowed(int UpperLeftX, int UpperLeftY, int Width, int Height)
{
	auto PrimaryVideoMode = PrimaryMonitorMode.second;
	if (is_full_screen && _window && PrimaryVideoMode) {
		
		_windowed_width = Width;
		_windowed_height = Height;
		glfwSetWindowMonitor(_window, NULL, UpperLeftX, UpperLeftY, _windowed_width, _windowed_height, PrimaryVideoMode->refreshRate);
		is_full_screen = false;
	}
}

void glfw_window::SwitchFullScreen()
{
	auto PrimaryMonitor = PrimaryMonitorMode.first;
	auto PrimaryVideoMode = PrimaryMonitorMode.second;
	if (!is_full_screen && _window && PrimaryMonitor && PrimaryVideoMode) {
		glfwSetWindowMonitor(_window, PrimaryMonitor, 0, 0, PrimaryVideoMode->width, PrimaryVideoMode->height, PrimaryVideoMode->refreshRate);
		is_full_screen = true;
	}
}

void glfw_window::maximize()
{
	if (glfwGetWindowAttrib(_window, GLFW_MAXIMIZED) == GLFW_FALSE) {
		glfwMaximizeWindow(_window);
	}
}

void glfw_window::minimize()
{
}

void glfw_window::restore()
{
	if (glfwGetWindowAttrib(_window, GLFW_MAXIMIZED) == GLFW_TRUE) {
		glfwRestoreWindow(_window);
	}
}

bool glfw_window::IsFullScreen()
{
	return false;
}

std::pair<size_t, size_t> glfw_window::GetPrimaryMonitorPhysicalSize()
{
	int width, height;
	glfwGetMonitorPhysicalSize(PrimaryMonitorMode.first, &width, &height);
	return std::pair<size_t, size_t>(width, height);
}

void glfw_window::show()
{
	if (glfwGetWindowAttrib(_window, GLFW_VISIBLE) == GLFW_FALSE) {
		glfwShowWindow(_window);
	}
}

void glfw_window::hide()
{
	if (glfwGetWindowAttrib(_window, GLFW_VISIBLE) == GLFW_TRUE) {
		glfwHideWindow(_window);
	}
}

void glfw_window::set_callback()
{
	glfwSetWindowSizeCallback(_window, window_size_callback); // when window size change
	glfwSetWindowContentScaleCallback(_window, window_content_scale_callback); // when content scale change
	glfwSetWindowPosCallback(_window, window_pos_callback); // when window position change
	glfwSetWindowCloseCallback(_window, window_close_callback); // before window close

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback); // when frame buffers change

	glfwSetCharCallback(_window, character_callback); // when char input
	
	glfwSetKeyCallback(_window, key_callback); // when key input

	glfwSetCursorPosCallback(_window, cursor_position_callback); // when cursor move
	glfwSetMouseButtonCallback(_window, mouse_button_callback); // when click mouse button
	glfwSetScrollCallback(_window, scroll_callback); // when roll mouse scroll
}

void glfw_window::set_input_mode()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //GLFW_CURSOR_HIDDEN, GLFW_CURSOR_DISABLED
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_TRUE); // GLFW_FALSE
	glfwSetInputMode(_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_CURSOR_DISABLED); //
	glfwSetInputMode(_window, GLFW_LOCK_KEY_MODS, GLFW_CURSOR_DISABLED); //
	glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_CURSOR_DISABLED); //
}
