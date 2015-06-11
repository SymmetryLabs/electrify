#include "loader.h"

void Loader::loadJSON(string filename)
{
	ifstream in(filename.c_str());
	Json::Value model_json;
	in >> model_json;
	in.close();
	for (Json::Value::iterator it = model_json["members"].begin(); it != model_json["members"].end(); ++it) {
    cout << (*it)["group"].asString() << endl;
    cout << "Tower x: " << (*it)["x"].asDouble() << endl;
  }
}