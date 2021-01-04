#include "ActiveVars.hpp"

void ActiveVars::run()
{
    std::ofstream output_active_vars;
    output_active_vars.open("active_vars.json", std::ios::out);
    output_active_vars << "[";
    for (auto &func : this->m_->get_functions()) {
            func_ = func;  

            func_->set_instr_name();
            live_in.clear();
            live_out.clear();
            
            //在此分析 func_ 的每个bb块的活跃变量，并存储在 live_in live_out 结构内
            std::map<BasicBlock *, std::set<Value *>> use;
            std::map<BasicBlock *, std::set<Value *>> def;
            for (auto bb : func->get_basic_blocks()) {
                std::set<Value *> u;
                std::set<Value *> d;
                for (auto instr : bb->get_instructions()) {
                    //TODO:求出每个bb的use和def
                }
                use[bb] = u;
                def[bb] = d;
            }
            //书上算法
            bool any_in_changed = true;
            while(any_in_changed) {
                any_in_changed = false;
                for (auto B : func->get_basic_blocks()) {
                    if (bb != ) {  //TODO: 除EXIT外的每个块B
                        if () {  //TODO: S是B的后继
                            //live_out[B] U live_in[S];
                        }
                        auto temp = live_out[B];  //TODO: live_out[B]-def[B]
                        auto org_in = live_in[B];
                        res.clear();
                        //TODO: use[B] U temp;
                        //TODO: auto res = org_in - live_in[B];
                        if () { //如果in没变
                            any_in_changed = true;
                        }
                    }
                }
            } 
            output_active_vars << print();
            output_active_vars << ",";
    }
    output_active_vars << "]";
    output_active_vars.close();
    return ;
}

std::string ActiveVars::print()
{
    std::string active_vars;
    active_vars +=  "{\n";
    active_vars +=  "\"function\": \"";
    active_vars +=  func_->get_name();
    active_vars +=  "\",\n";

    active_vars +=  "\"live_in\": {\n";
    for (auto &p : live_in) {
        if (p.second.size() == 0) {
            continue;
        } else {
            active_vars +=  "  \"";
            active_vars +=  p.first->get_name();
            active_vars +=  "\": [" ;
            for (auto &v : p.second) {
                active_vars +=  "\"%";
                active_vars +=  v->get_name();
                active_vars +=  "\",";
            }
            active_vars += "]" ;
            active_vars += ",\n";   
        }
    }
    active_vars += "\n";
    active_vars +=  "    },\n";
    
    active_vars +=  "\"live_out\": {\n";
    for (auto &p : live_out) {
        if (p.second.size() == 0) {
            continue;
        } else {
            active_vars +=  "  \"";
            active_vars +=  p.first->get_name();
            active_vars +=  "\": [" ;
            for (auto &v : p.second) {
                active_vars +=  "\"%";
                active_vars +=  v->get_name();
                active_vars +=  "\",";
            }
            active_vars += "]";
            active_vars += ",\n";
        }
    }
    active_vars += "\n";
    active_vars += "    }\n";

    active_vars += "}\n";
    active_vars += "\n";
    return active_vars;
}