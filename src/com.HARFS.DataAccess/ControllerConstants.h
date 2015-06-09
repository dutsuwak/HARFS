/*
 * DiskNodeConstants.h
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATAACCESS_CONTROLLERCONSTANTS_H_
#define COM_HARFS_DATAACCESS_CONTROLLERCONSTANTS_H_

#include <string>
#include <string>
#include <stdlib.h>
#include "XML.h"
#include "lib.tinyxml/tinyxml.h"
#include "../com.HARFS.DataStructures/LinkedList.h"

using namespace std;

class ControllerConstants {
private:
	ControllerConstants();
	virtual ~ControllerConstants();

public:
	static ControllerConstants* _Constants;

	ControllerConstants* getInstance();

	static string DEBUG;
	static string SHARED_SECRET;
	static int LISTENINGPORT;
	static LinkedList<string>* DISK_NODES;

};

#endif /* COM_HARFS_DATAACCESS_CONTROLLERCONSTANTS_H_ */
