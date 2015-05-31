/*
 * ControllerNode.cpp
 *
 *  Created on: May 29, 2015
 *      Author: abrahamon
 */

#include "ControllerNode.h"

ControllerNode::ControllerNode() {
	_Server = new Server(ControllerConstants::PORT);
	_SharedSecret = ControllerConstants::SHARED_SECRET;
	_Port = ControllerConstants::PORT;

}

ControllerNode::~ControllerNode() {}

