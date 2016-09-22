#pragma once

#include <stdint.h>
#include <string>

struct lua_State;
struct lua_Debug;

namespace vscode
{
	class  wprotocol;
	enum class var_type {
		none = 0,
		local = 1,
		vararg = 2,
		upvalue = 3,
		global = 4,
		standard = 5,
	};

	class variables
	{
	public:
		variables(wprotocol& res, lua_State* L, lua_Debug* ar);
		~variables();
		bool push(const std::string& name, const std::string& value, int64_t reference);
		void push_table(int idx, int level, int64_t pos, var_type type);
		void push_value(var_type type, int depth, int64_t pos);

	public:
		static bool set_value(lua_State* L, lua_Debug* ar, var_type type, int depth, int64_t pos, const std::string& name, std::string& value);
		static bool find_value(lua_State* L, lua_Debug* ar, var_type type, int depth, int64_t pos);

	private:
		wprotocol& res;
		lua_State* L;
		lua_Debug* ar;
		size_t n;
		int checkstack;
	};
}