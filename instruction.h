#pragma once

#include <utility>
#include <vector>

#include "var.h"

#define MAX_OPERANDS 5 //enough?

enum instruction_type
{
	ADD, SUB, AND, OR, NOT, NOOP //and so on
};

class process;
class instruction;

typedef std::pair<instruction*, int> interior_edge;
typedef std::pair<process*, int> exterior_edge;

class instruction
{
	var* dst;
	var* src[MAX_OPERANDS];
	instruction_type type;
	std::vector<interior_edge> successors;
	std::vector<exterior_edge> triggers;
public:
	instruction();
	~instruction();
};

