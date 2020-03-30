#pragma once

#include <memory>
#include <vector>
#include <map>

namespace afbd {

class Var;
class Constant;
class Process;
class Instruction;
class Module;
class Expr;
class Constant;

typedef std::vector<std::shared_ptr<Var>> VarContainer;
typedef std::vector<std::shared_ptr<Process>> ProcContainer;
typedef std::vector<std::shared_ptr<Instruction>> InstrContainer;
typedef std::pair<std::shared_ptr<Instruction>, std::shared_ptr<Expr>> InstrEdge;
typedef std::vector<InstrEdge> InstrEdgeContainer;

}
