#include "level_loader.h"

/*
Level* LevelLoader::load(std::string level_name)
{
	std::stringstream sstream;
	std::string path;
	std::string line;
	std::ifstream file;
	Level* level = new Level();

	sstream << levels_dir << "/" << level_name << ".dat";
    path = sstream.str();	

	file.open(path);
	assert(file.is_open());

	while(getline(file, line))
	{
		if(line == "MAP")
		{
			while(getline(file, line) != "MAP END")
			{
				
			}
		}
	}

	file.close();	

	return level;
}
*/
