#pragma once

#include "instruction.h"
#include "var.h"

class process
{
	std::vector<var*> sensitive;
	instruction* begin; //is always noop, and leads to other instructions
public:
	int getSensitiveNum() { return sensitive.size(); }
	var* getSensitive(int n) { return sensitive[n]; }
	instruction* getBegin() { return begin; }
	process();
	~process();
};

