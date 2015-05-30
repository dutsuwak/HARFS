/*
 * Constants.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "Constants.h"

Constants* Constants::_Constants;
string Constants::DEBUG;
string Constants::JSONS_PATH;

Constants::Constants() {

}

Constants* Constants::getInstance(){
	if(_Constants == 0){
		_Constants = new Constants();
	}
	return _Constants;
}


