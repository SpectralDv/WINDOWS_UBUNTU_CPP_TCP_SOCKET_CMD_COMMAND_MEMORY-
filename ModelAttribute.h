#pragma once
#ifndef _MODELATTRIBUTE_H_
#define _MODELATTRIBUTE_H_

#include "IAttribute.h"


	class ModelAttribute
	{
	public:
        std::string name;
		std::string type;
		bool event;
		int value;
		std::string text;
    public:
        ModelAttribute(){}
        ~ModelAttribute(){}
    };

    class ModelChar : public ModelAttribute //IAttribute
	{
	public:
		std::string text;
	public:
		ModelChar(){}
		~ModelChar(){}
	};
	class ModelInt : public IAttribute
	{
	public:
		int value = 0;
	public:
		ModelInt(){}
		~ModelInt(){}
	};
	class ModelBool : public IAttribute
	{
	public:
		bool event = false;
	public:
		ModelBool(){}
		~ModelBool(){}
	};

#endif