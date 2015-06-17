#include "loader.h"
#include "group.h"
#include "pixel.h"

unique_ptr<Model> Loader::loadJSON(string filename)
{
  unique_ptr<Model> m(new Model);
  ifstream in(filename.c_str());
  Json::Value model_json;
  in >> model_json;
  in.close();
  if (model_json.isMember("type") && model_json["type"].asString() != string("File"))
  {
        cout << "Loader::loadJSON: invalid model file";
        return m;
  }

  for (Json::Value::iterator it = model_json["points"].begin(); it != model_json["points"].end(); ++it) {
        m->pixels.push_back(Pixel((*it)["x"].asDouble(), (*it)["y"].asDouble(), (*it)["z"].asDouble()));
  }
  return m;
}
