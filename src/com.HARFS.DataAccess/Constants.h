/*
 * Constants.h
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATAACCESS_CONSTANTS_H_
#define COM_HARFS_DATAACCESS_CONSTANTS_H_

#include <string>
#include <stdlib.h>

using namespace std;

class Constants {
public:
	static Constants* _Constants;
	Constants* getInstance();

	static string DEBUG;
	static string JSONS_PATH;
private:
	Constants();
};

#endif /* COM_HARFS_DATAACCESS_CONSTANTS_H_ */
