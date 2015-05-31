/*
 * DiskNode.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "DiskNode.h"

DiskNode::DiskNode() {
	this->_DiskSize = DiskConstants::DISK_SIZE;
	this->_Port = DiskConstants::PORT;
	this->_Path = DiskConstants::PATH;
	this->_SharedSecret = DiskConstants::SHARED_SECRET;
}

DiskNode::~DiskNode() {
	// TODO Auto-generated destructor stub
}

