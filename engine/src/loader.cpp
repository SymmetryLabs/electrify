#include "loader.h"

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
        Json::Value p = *it;
        Pixel *pixel = new Pixel(p["x"].asDouble(), p["y"].asDouble(), p["z"].asDouble());
        m->pixels.push_back(pixel);
  }

  m->root = parseGroup(model_json["root"], &(m->pixels), nullptr);

  return m;
}

Group* Loader::parseGroup(Json::Value val, vector<Pixel*> *pixels , Group *parent)
{
        Group *g = new Group();
	g->parent = parent;
	g->name = val["group"].asString();
	for (Json::Value::iterator it = val["members"].begin(); it != val["members"].end(); ++it) {
		Json::Value member = (*it);
		if(member["type"] == string("Group"))
		{
                        g->members->push_back(parseGroup(member, pixels, g));
		}else if(member["type"] == string("Reference")){
                        g->pixels->push_back(parsePixelReference(member, pixels, g));
		}
	}
	return g;
}

Pixel* Loader::parsePixelReference(Json::Value val, vector<Pixel*> *pixels, Group *parent)
{
    Pixel *pix = (*pixels)[val["index"].asInt()];
	pix->parent = parent;
	return pix;
}
