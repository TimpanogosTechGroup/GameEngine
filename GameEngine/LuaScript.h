#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <iostream>
#include <stdarg.h>

extern "C" {
#include <lua\lua.hpp>
#include <lua\lua.h>
#include <lua\lauxlib.h>
#include <lua\lualib.h>
}

class LuaScript {
public:
	LuaScript() { this->file = ""; }
	LuaScript(std::string f) {
		this->L = luaL_newstate();
		this->file = f;
	}
	~LuaScript() {
		lua_close(L);
	}
	int RunScript() {
		lua_pcall(L, 0, 0, 0);
		lua_pcall(L, 0, 0, 0);
	}
	int RunScript(std::string function, int argc) {
		luaL_openlibs(L);
		luaL_loadfile(L, file.c_str());
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, function.c_str());
		lua_pcall(L, 0, argc, 0);
		 return static_cast<int>(lua_tonumber(L, -1));
	}
	void CloseScript() { lua_close(L); }


	void test(const char *szTypes, ...) {
		va_list ap;
		va_start(ap, szTypes);

		for (int i = 0; szTypes[i] != '\0'; ++i) {
			union Printable_t {
				int     i;
				float   f;
				char    c;
				char   *s;
			} Printable;
			switch (szTypes[i]) {   // Type to expect.  
			case 'i':
				Printable.i = va_arg(ap, int);
				printf_s("%i\n", Printable.i);
				break;

			case 'f':
				Printable.f = va_arg(ap, double);
				printf_s("%f\n", Printable.f);
				break;

			case 'c':
				Printable.c = va_arg(ap, char);
				printf_s("%c\n", Printable.c);
				break;

			case 's':
				Printable.s = va_arg(ap, char *);
				printf_s("%s\n", Printable.s);
				break;

			default:
				break;
			}
		}
		va_end(ap);
		return;
	}

private:
	lua_State * L;
	std::string file;
};

#endif