#pragma once

#include <memory>
#include <vector>

class Var;
class Process;
class Instruction;
class Module;

typedef std::vector<std::shared_ptr<Var>> VarContainer;
typedef std::vector<std::shared_ptr<Process>> ProcContainer;
typedef std::vector<std::shared_ptr<Instruction>> InstrContainer;
typedef std::pair<std::shared_ptr<Instruction>, int> InstrEdge;
typedef std::vector<InstrEdge> InstrEdgeContainer;