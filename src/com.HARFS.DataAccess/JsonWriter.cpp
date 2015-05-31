#include "JsonWriter.h"

using namespace std;

JsonWriter::JsonWriter() {
	Path_to_Json = ControllerConstants::JSONS_PATH;
}

void JsonWriter::resetVillageArmy(std::string pPueblo){
	Jzon::Writer writer;
	Jzon::Node node = Jzon::object();
	node.add("War","Not Started");
	writer.writeFile(node, Path_to_Json+pPueblo+".json");
}





