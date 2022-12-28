#pragma once
#ifndef _IATTRIBUTE_H_
#define _IATTRIBUTE_H_

#include "config.h"


	class IAttribute
	{
	public:
		std::string name = "iname";
		std::string type = "iattribute";
		virtual ~IAttribute(){}
	};

#endif