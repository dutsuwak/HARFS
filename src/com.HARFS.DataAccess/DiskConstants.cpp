/*
 * DiskConstants.cpp
 *
 *  Created on: May 31, 2015
 *      Author: abrahamon
 */

#include "DiskConstants.h"

DiskConstants* DiskConstants::_DiskConstants;
string DiskConstants::DEBUG;
string DiskConstants::SHARED_SECRET;
string DiskConstants::PATH;
string DiskConstants::JSONS_PATH;
int DiskConstants::PORT = 0;
int DiskConstants::DISK_SIZE = 0;

DiskConstants::DiskConstants() {
	//XML Reader
	srand(time(0));
	XMLReader* reader = new XMLReader();
	reader->loadXMLFile("src/DiskConfigs.xml");

	DEBUG = reader->getParameter("DEBUG");
	SHARED_SECRET = reader->getParameter("SHARED_SECRET");
	PATH = reader->getParameter("PATH");
	PORT = atoi(reader->getParameter("PORT"));
	DISK_SIZE = atoi(reader->getParameter("DISK_SIZE"));
	JSONS_PATH = reader->getParameter("JSONS_PATH");
}

DiskConstants::~DiskConstants() {}

DiskConstants* DiskConstants::getInstance(){
	if(_DiskConstants== 0){
		_DiskConstants= new DiskConstants();
	}
	return _DiskConstants;
}
