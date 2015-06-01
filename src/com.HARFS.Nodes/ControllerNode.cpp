/*
 * ControllerNode.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "ControllerNode.h"

ControllerNode::ControllerNode() {
	_SharedSecret = ControllerConstants::SHARED_SECRET;
	_Port = ControllerConstants::PORT;
	_DiskNodes = new LinkedList<string>();
	cout<<"CREANDO controller node en: "<<_Port<<endl;
	_Server = new Server(_Port);
}

ControllerNode::~ControllerNode() {}

