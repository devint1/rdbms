#include "TableAttribute.h"


TableAttribute::TableAttribute(string name, string type)
{
	name = name;
	type  = type;
}


TableAttribute::~TableAttribute()
{
}


string TableAttribute::getName()
{
	return name;
}

string TableAttribute::getType()
{
	return type;
}