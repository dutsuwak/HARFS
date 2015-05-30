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
string Constants::SHARED_SECRECT;
int Constants::DISK_SIZE = 0;
int Constants::PORT = 0;

Constants::Constants() {
	//XML Reader
	srand(time(0));
	XMLReader* reader = new XMLReader();
	reader->loadXMLFile("src/com.HARFS.DataAccess/Config.xml");

	//General Constants
	//atoi(reader->getParameter("INTEGER"));
	DEBUG= reader->getParameter("DEBUG");

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
