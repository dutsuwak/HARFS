/*
 * DiskNodeConstants.h
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATAACCESS_CONTROLLERCONSTANTS_H_
#define COM_HARFS_DATAACCESS_CONTROLLERCONSTANTS_H_

#include <string>
#include <stdlib.h>
#include "XML.h"
#include "lib.tinyxml/tinyxml.h"

using namespace std;

class ControllerConstants {
private:
	ControllerConstants();
	virtual ~ControllerConstants();

public:
	static ControllerConstants* _Constants;

	ControllerConstants* getInstance();

	static string DEBUG;
	static string JSONS_PATH;
	static string SHARED_SECRET;
	static string PATH;
	static int PORT;
	static int DISK_SIZE;

};

#endif /* COM_HARFS_DATAACCESS_CONTROLLERCONSTANTS_H_ */
