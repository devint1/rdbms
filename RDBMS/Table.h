#pragma once
class Table
{
public:
	Table();
	~Table();

	Table select(string attributesToInclude, string condition);
};

