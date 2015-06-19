/*
 * user.h
 *
 *  Created on: Jun 18, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_NETWORKACCESS_USER_H_
#define COM_HARFS_NETWORKACCESS_USER_H_

#include <string>

using namespace std;

class user {
private:
	string _Name;
	string _Password;

public:
	user(string pName, string pPassword);
	virtual ~user();

	bool SoyEste(string pName, string pPassword);
};

#endif /* COM_HARFS_NETWORKACCESS_USER_H_ */
