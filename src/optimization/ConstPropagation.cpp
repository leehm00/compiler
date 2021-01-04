#include "ConstPropagation.hpp"
#include "logging.hpp"

// 给出了返回整形值的常数折叠实现，大家可以参考，在此基础上拓展
// 当然如果同学们有更好的方式，不强求使用下面这种方式
ConstantInt *ConstFolder::compute(
    Instruction::OpID op,
    ConstantInt *value1,
    ConstantInt *value2)
{

    int c_value1 = value1->get_value();
    int c_value2 = value2->get_value();
    switch (op)
    {
    case Instruction::add:
        return ConstantInt::get(c_value1 + c_value2, module_);

        break;
    case Instruction::sub:
        return ConstantInt::get(c_value1 - c_value2, module_);
        break;
    case Instruction::mul:
        return ConstantInt::get(c_value1 * c_value2, module_);
        break;
    case Instruction::sdiv:
        return ConstantInt::get((int)(c_value1 / c_value2), module_);
        break;
    default:
        return nullptr;
        break;
    }
}
//TODO:修改float实现
ConstantFP *ConstFolder::computefp(
    Instruction::OpID op,
    ConstantFP *value1,
    ConstantFP *value2)
{

    int c_value1 = value1->get_value();
    int c_value2 = value2->get_value();
    switch (op)
    {
    case Instruction::fadd:
        return ConstantFP::get(c_value1 + c_value2, module_);

        break;
    case Instruction::fsub:
        return ConstantFP::get(c_value1 - c_value2, module_);
        break;
    case Instruction::fmul:
        return ConstantFP::get(c_value1 * c_value2, module_);
        break;
    case Instruction::fdiv:
        return ConstantFP::get((c_value1 / c_value2), module_);
        break;
    default:
        return nullptr;
        break;
    }
}
ConstantInt *ConstFolder::compute(CmpInst::CmpOp op, ConstantInt *v1,
                                ConstantInt *v2) {
  int lhs = v1->get_value();
  int rhs = v2->get_value();
  int ret;
  switch (op) {
  case CmpInst::EQ:
    ret = lhs == rhs;
    break;
  case CmpInst::NE:
    ret = lhs != rhs;
    break;
  case CmpInst::GT:
    ret = lhs > rhs;
    break;
  case CmpInst::GE:
    ret = lhs >= rhs;
    break;
  case CmpInst::LE:
    ret = lhs <= rhs;
    break;
  case CmpInst::LT:
    ret = lhs < rhs;
    break;
  default:
    return nullptr;
    break;
  }
  return ConstantInt::get(ret, module_);
}

// 用来判断value是否为ConstantFP，如果不是则会返回nullptr
ConstantFP *cast_constantfp(Value *value)
{
    auto constant_fp_ptr = dynamic_cast<ConstantFP *>(value);
    if (constant_fp_ptr)
    {
        return constant_fp_ptr;
    }
    else
    {
        return nullptr;
    }
}
ConstantInt *cast_constantint(Value *value)
{
    auto constant_int_ptr = dynamic_cast<ConstantInt *>(value);
    if (constant_int_ptr)
    {
        return constant_int_ptr;
    }
    else
    {
        return nullptr;
    }
}


void ConstPropagation::run()
{
    auto func_list = m_->get_functions();
    for (auto func : func_list) {
        for (auto bb : func->get_basic_blocks()) {
                for (auto instr : bb->get_instructions()) {
                    if (instr->is_add() || instr->is_sub() || instr->is_mul() || instr->is_div() || instr->is_fadd() || instr->is_fsub() || instr->is_fmul() || instr->is_fdiv()) { 
                        if (instr->is_add() || instr->is_sub() || instr->is_mul() || instr->is_div()) {
                            auto l = cast_constantint(instr->get_operand(0));
                            auto r = cast_constantint(instr->get_operand(1));
                            if (l && r) {
                                instr->replace_all_use_with(ConstFolder(m_).compute(instr->get_instr_type(), l, r));
                            }
                        }
                        else {
                            auto l = cast_constantfp(instr->get_operand(0));
                            auto r = cast_constantfp(instr->get_operand(1));
                            if (l && r) {
                                instr->replace_all_use_with(ConstFolder(m_).computefp(instr->get_instr_type(), l, r));
                            }
                        }
                    }
            }
        }
    }
}