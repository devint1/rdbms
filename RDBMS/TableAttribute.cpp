#include "TableAttribute.h"


TableAttribute::TableAttribute(string name, string type) : name(name), type(type)
{
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

void TableAttribute::setName(string newName)
{
	name = newName;
}

void TableAttribute::setType(string newType)
{
	type = newType;
}