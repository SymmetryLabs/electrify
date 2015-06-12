#pragma once
#include "constants.h"

#include <fstream>
#include <json/json-forwards.h>
#include <json/json.h>

class Loader {
public:
	void loadJSON(string filename);
};
