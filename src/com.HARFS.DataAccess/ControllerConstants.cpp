/*
 * DiskNodeConstants.cpp
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#include "ControllerConstants.h"

ControllerConstants* ControllerConstants::_Constants;
string ControllerConstants::JSONS_PATH;
string ControllerConstants::DEBUG;
string ControllerConstants::PATH;
string ControllerConstants::SHARED_SECRET;
int ControllerConstants::DISK_SIZE = 0;
int ControllerConstants::PORT = 0;

ControllerConstants::ControllerConstants() {
	//XML Reader
	srand(time(0));
	XMLReader* reader = new XMLReader();
	reader->loadXMLFile("src/ControllerConfigs.xml");

	//General Constants
	//atoi(reader->getParameter("INTEGER"));
	DEBUG= reader->getParameter("DEBUG");
	JSONS_PATH = reader->getParameter("JSONS_PATH");
	PATH = reader->getParameter("PATH");
	SHARED_SECRET = reader->getParameter("SHARED_SECRET");
	DISK_SIZE = atoi(reader->getParameter("DISK_SIZE"));
	PORT = atoi(reader->getParameter("PORT"));

}

ControllerConstants::~ControllerConstants() {
	// TODO Auto-generated destructor stub
}

ControllerConstants* ControllerConstants::getInstance(){
	if(_Constants== 0){
		_Constants= new ControllerConstants();
	}
	return _Constants;
}
