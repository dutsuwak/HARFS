/*
 * DiskNodeConstants.cpp
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#include "Constants.h"

Constants* Constants::_Constants;
string Constants::JSONS_PATH;
string Constants::DEBUG;
string Constants::PATH;
string Constants::SHARED_SECRET;
int Constants::DISK_SIZE = 0;
int Constants::PORT = 0;

Constants::Constants() {
	//XML Reader
	srand(time(0));
	XMLReader* reader = new XMLReader();
	reader->loadXMLFile("src/configs.xml");

	//General Constants
	//atoi(reader->getParameter("INTEGER"));
	DEBUG= reader->getParameter("DEBUG");
	JSONS_PATH = reader->getParameter("JSONS_PATH");
	PATH = reader->getParameter("PATH");
	SHARED_SECRET = reader->getParameter("SHARED_SECRET");
	DISK_SIZE = atoi(reader->getParameter("DISK_SIZE"));
	PORT = atoi(reader->getParameter("PORT"));

}

Constants::~Constants() {
	// TODO Auto-generated destructor stub
}

Constants* Constants::getInstance(){
	if(_Constants== 0){
		_Constants= new Constants();
	}
	return _Constants;
}
