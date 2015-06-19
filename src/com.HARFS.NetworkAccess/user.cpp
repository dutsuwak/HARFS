/*
 * user.cpp
 *
 *  Created on: Jun 18, 2015
 *      Author: abrahamon
 */

#include "user.h"

user::user(string pName, string pPassword){
	this->_Name = pName;
	this->_Password = pPassword;
}

user::~user(){}


bool user::SoyEste(string pName, string pPassword){
	if(_Name == pName && _Password==pPassword)
		return true;
	else
		return false;
}
