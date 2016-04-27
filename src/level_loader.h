#ifndef level_loader_h
#define level_loader_h

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "level.h"

class LevelLoader {
public:
	Level* load(std::string level_name);
private:
	const levels_dir = "levels";
};

#endif
