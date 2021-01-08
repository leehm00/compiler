#ifndef ACTIVEVARS_HPP
#define ACTIVEVARS_HPP
#include "PassManager.hpp"
#include "Constant.h"
#include "Instruction.h"
#include "Module.h"

#include "Value.h"
#include "IRBuilder.h"
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <queue>
#include <fstream>
#include <algorithm>

class ActiveVars : public Pass
{
public:
    ActiveVars(Module *m) : Pass(m) {}
    void run();
    std::string print();
private:
    Function *func_;
    std::map<BasicBlock *, std::set<Value *>> live_in, live_out,def, use,tempin,tempout,map_def,map_use;
    std::set<Value *>alldef,alluse;
    bool need_iterate;
    std::map<BasicBlock *, std::map<Value *, BasicBlock *>> big_phi;
};

#endif