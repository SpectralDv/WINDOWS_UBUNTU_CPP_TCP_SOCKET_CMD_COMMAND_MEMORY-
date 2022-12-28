#pragma once
#ifndef _ICONTROLLER_H_
#define _ICONTROLLER_H_

#include "config.h"
#include "ModelData.h"


//namespace SpaceIController
//{
	class IController
	{
	public:
		std::string name = "IController";
	public:
		virtual void UpdateController(ModelString mString) {}
	};
//}
#endif