/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2016  Mark Samman <mark.samman@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "otpch.h"

#include "script.h"
#include <boost/filesystem.hpp>

extern LuaEnvironment g_luaEnvironment;

Scripts::Scripts() :
	scriptInterface("Scripts Interface")
{
	scriptInterface.initState();
}

Scripts::~Scripts()
{
	scriptInterface.reInitState();
}

bool Scripts::loadScripts(std::string folderName)
{
	const auto dir = boost::filesystem::current_path() / "/data/" / folderName / "/";
	if(!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir)) {
		std::cout << "[Warning - Scripts::loadScripts] Can not load folder 'scripts'." << std::endl;
		return false;
	}

	boost::filesystem::recursive_directory_iterator endit;
	for(boost::filesystem::recursive_directory_iterator it(dir); it != endit; ++it) {
		if(boost::filesystem::is_regular_file(*it) && it->path().extension() == ".lua") {
			const std::string scriptFile = it->path().string();

			if(scriptInterface.loadFile(scriptFile) == -1) {
				std::cout << "[Warning - Scripts::loadScripts] Can not load script. " << scriptFile << std::endl;
				std::cout << scriptInterface.getLastLuaError() << std::endl;
				return false;
			}

			std::cout << "[Scripts::loadScripts] " << scriptFile << " successfully loaded." << std::endl;
		}
	}

	return true;
}
