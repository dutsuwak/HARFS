/*
 * JsonWriter.h
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATAACCESS_JSONWRITER_H_
#define COM_HARFS_DATAACCESS_JSONWRITER_H_

#include <string>
#include "Jzon.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <time.h>
#include <boost/lexical_cast.hpp>
#include "../com.HARFS.DataStructures/LinkedList.h"
#include "Constants.h"

using boost::lexical_cast;
using namespace std;

class JsonWriter{
private:
	string Path_to_Json;
public:
	JsonWriter();

	void resetVillageArmy(std::string pPueblo);
};

#endif /* COM_HARFS_DATAACCESS_JSONWRITER_H_ */
