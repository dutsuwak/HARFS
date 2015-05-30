/*
 * XML.h
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#ifndef COM_HARFS_DATAACCESS_XML_H_
#define COM_HARFS_DATAACCESS_XML_H_

#include "../com.HARFS.DataAccess/lib.tinyxml/tinyxml.h"

#include <string>

class XMLReader {
private:
	TiXmlDocument documento;
	TiXmlElement* root;
public:
	XMLReader();
	virtual ~XMLReader();
	void loadXMLFile(std::string pData);
	const char* getParameter(const char* pParameter);

};


#endif /* COM_HARFS_DATAACCESS_XML_H_ */
