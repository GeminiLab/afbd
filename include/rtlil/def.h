#pragma once

#include <memory>
#include <vector>
#include <map>

class Var;
class Process;
class Instruction;
class Module;

typedef std::vector<std::shared_ptr<Var>> VarContainer;
typedef std::vector<std::shared_ptr<Process>> ProcContainer;
typedef std::vector<std::shared_ptr<Instruction>> InstrContainer;
typedef std::pair<std::shared_ptr<Instruction>, int> InstrEdge;
typedef std::vector<InstrEdge> InstrEdgeContainer;
typedef std::multimap<std::shared_ptr<Var>, std::shared_ptr<Process>> SensitiveMap;
