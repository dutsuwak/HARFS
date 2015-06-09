/*
 * DiskNodeConstants.cpp
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#include "ControllerConstants.h"

ControllerConstants* ControllerConstants::_Constants;
string ControllerConstants::DEBUG;
string ControllerConstants::SHARED_SECRET;
int ControllerConstants::LISTENINGPORT = 0;
LinkedList<string>* ControllerConstants::DISK_NODES;

ControllerConstants::ControllerConstants() {
	//XML Reader
	srand(time(0));
	XMLReader* reader = new XMLReader();
	reader->loadXMLFile("src/ControllerConfigs.xml");

	//General Constants
	//atoi(reader->getParameter("INTEGER"));
	DEBUG= reader->getParameter("DEBUG");
	SHARED_SECRET = reader->getParameter("SHARED_SECRET");
	LISTENINGPORT = atoi(reader->getParameter("LISTENINGPORT"));

	DISK_NODES = new LinkedList<string>();

	string TmpIPS = reader->getParameter("DISK_NODES");
	char sep = '#';
	for(size_t p=0, q=0; p!=TmpIPS.npos; p=q){
	  DISK_NODES->insertTail(TmpIPS.substr(p+(p!=0), (q=TmpIPS.find(sep, p+1))-p-(p!=0)));
	}

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
