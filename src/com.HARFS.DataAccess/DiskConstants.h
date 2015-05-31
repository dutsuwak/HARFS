/*
 * DiskConstants.h
 *
 *  Created on: May 31, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATAACCESS_DISKCONSTANTS_H_
#define COM_HARFS_DATAACCESS_DISKCONSTANTS_H_

#include <string>
#include <stdlib.h>
#include "XML.h"
#include "lib.tinyxml/tinyxml.h"

using namespace std;

class DiskConstants {

private:
	DiskConstants();

public:
	virtual ~DiskConstants();

	static DiskConstants* _DiskConstants;

	DiskConstants* getInstance();

	static string DEBUG;
	static string SHARED_SECRET;
	static string PATH;
	static int PORT;
	static int DISK_SIZE;

};

#endif /* COM_HARFS_DATAACCESS_DISKCONSTANTS_H_ */
