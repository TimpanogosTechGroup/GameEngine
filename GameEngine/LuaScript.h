/**
	File:
    Purpose: 

    @author 
    @version 1.0

	Copyright (c) 2018 All Rights Reserved
*/
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

	template<typename T>
	T RunFunction(const char *function, int argc, const char *szTypes, ...) {
		va_list ap;
		va_start(ap, szTypes);

		luaL_openlibs(L);
		luaL_loadfile(L, file.c_str());
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, function);

		for (int i = 0; szTypes[i] != '\0'; ++i) {
			union data_t {
				bool	b;
				int     i;
				double  d;
				char    c;
				char   *s;
			} data;
			switch (szTypes[i]) {   // Type to expect.
				case 'b':
					data.b = va_arg(ap, bool);
					lua_pushboolean(L, data.b);
					break;

				case 'i':
					data.i = va_arg(ap, int);
					lua_pushnumber(L, data.i);
					break;

				case 'd':
					data.d = va_arg(ap, double);
					lua_pushnumber(L, data.d);
					break;

				case 'c':
					data.c = va_arg(ap, char);
					lua_pushstring(L, data.s);
					break;

				case 's':
					data.s = va_arg(ap, char *);
					lua_pushstring(L, data.s);
					break;

				default:
					break;
			}
		}
		va_end(ap);

		lua_pcall(L, argc, 2, 0);

		std::string s = static_cast<std::string>(lua_tostring(L, -2));
		return s;
	}
	template<>int
	RunFunction<int>(const char *function, int argc, const char *szTypes, ...) {
		va_list ap;
		va_start(ap, szTypes);

		luaL_openlibs(L);
		luaL_loadfile(L, file.c_str());
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, function);

		for (int i = 0; szTypes[i] != '\0'; ++i) {
			union data_t {
				bool	b;
				int     i;
				double  d;
				char    c;
				char   *s;
			} data;
			switch (szTypes[i]) {   // Type to expect.
			case 'b':
				data.b = va_arg(ap, bool);
				lua_pushboolean(L, data.b);
				break;

			case 'i':
				data.i = va_arg(ap, int);
				lua_pushnumber(L, data.i);
				break;

			case 'd':
				data.d = va_arg(ap, double);
				lua_pushnumber(L, data.d);
				break;

			case 'c':
				data.c = va_arg(ap, char);
				lua_pushstring(L, data.s);
				break;

			case 's':
				data.s = va_arg(ap, char *);
				lua_pushstring(L, data.s);
				break;

			default:
				break;
			}
		}
		va_end(ap);

		lua_pcall(L, argc, 2, 0);

		int i = static_cast<int>(lua_tonumber(L, -2));
		return i;
	}
	template<>double
	RunFunction<double>(const char *function, int argc, const char *szTypes, ...) {
		va_list ap;
		va_start(ap, szTypes);

		luaL_openlibs(L);
		luaL_loadfile(L, file.c_str());
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, function);

		for (int i = 0; szTypes[i] != '\0'; ++i) {
			union data_t {
				bool	b;
				int     i;
				double  d;
				char    c;
				char   *s;
			} data;
			switch (szTypes[i]) {   // Type to expect.
			case 'b':
				data.b = va_arg(ap, bool);
				lua_pushboolean(L, data.b);
				break;

			case 'i':
				data.i = va_arg(ap, int);
				lua_pushnumber(L, data.i);
				break;

			case 'd':
				data.d = va_arg(ap, double);
				lua_pushnumber(L, data.d);
				break;

			case 'c':
				data.c = va_arg(ap, char);
				lua_pushstring(L, data.s);
				break;

			case 's':
				data.s = va_arg(ap, char *);
				lua_pushstring(L, data.s);
				break;

			default:
				break;
			}
		}
		va_end(ap);

		lua_pcall(L, argc, 2, 0);

		double d = static_cast<double>(lua_tonumber(L, -2));
		return d;
	}
	template<>bool
	RunFunction<bool>(const char *function, int argc, const char *szTypes, ...) {
		va_list ap;
		va_start(ap, szTypes);

		luaL_openlibs(L);
		luaL_loadfile(L, file.c_str());
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, function);

		for (int i = 0; szTypes[i] != '\0'; ++i) {
			union data_t {
				bool	b;
				int     i;
				double  d;
				char    c;
				char   *s;
			} data;
			switch (szTypes[i]) {   // Type to expect.
			case 'b':
				data.b = va_arg(ap, bool);
				lua_pushboolean(L, data.b);
				break;

			case 'i':
				data.i = va_arg(ap, int);
				lua_pushnumber(L, data.i);
				break;

			case 'd':
				data.d = va_arg(ap, double);
				lua_pushnumber(L, data.d);
				break;

			case 'c':
				data.c = va_arg(ap, char);
				lua_pushstring(L, data.s);
				break;

			case 's':
				data.s = va_arg(ap, char *);
				lua_pushstring(L, data.s);
				break;

			default:
				break;
			}
		}
		va_end(ap);

		lua_pcall(L, argc, 2, 0);

		bool b = static_cast<bool>(lua_toboolean(L, -2));
		return b;
	}

private:
	lua_State * L;
	std::string file;
};

#endif