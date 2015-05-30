/*
 * DiskNodeConstants.h
 *
 *  Created on: May 30, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATAACCESS_CONSTANTS_H_
#define COM_HARFS_DATAACCESS_CONSTANTS_H_

#include <string>
#include <stdlib.h>
#include "XML.h"
#include "lib.tinyxml/tinyxml.h"

using namespace std;

class Constants {
private:
	Constants();
	virtual ~Constants();

public:
	static Constants* _Constants;

	Constants* getInstance();

	static string DEBUG;
	static string JSONS_PATH;
	static string SHARED_SECRECT;
	static string PATH;
	static int PORT;
	static int DISK_SIZE;

};

#endif /* COM_HARFS_DATAACCESS_CONSTANTS_H_ */
