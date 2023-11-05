#include "hw01/sim.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

using namespace llvm;

LLVMContext context;
Module *module = new Module("", context);
IRBuilder<> builder(context);

// Type *charTy = builder.getInt8Ty();
Type *intTy = builder.getInt32Ty();
Type *ptrTy = builder.getPtrTy();
Type *voidTy = builder.getVoidTy();

Constant *getInt(uint64_t val) { return ConstantInt::get(intTy, val, true); }

constexpr uint64_t layerSize = SIM_X_SIZE * SIM_Y_SIZE;
Type *boardTy = ArrayType::get(intTy, layerSize);
Type *varBUFTy = ArrayType::get(boardTy, 2);
GlobalVariable *varBUF = new GlobalVariable(
    *module, varBUFTy, false, GlobalVariable::PrivateLinkage, ConstantAggregateZero::get(intTy), "BUF");

GlobalVariable *varBoardSrc
    = new GlobalVariable(*module, ptrTy, false, GlobalVariable::PrivateLinkage, varBUF, "board");
GlobalVariable *varBoardDst = new GlobalVariable(*module,
                                                 ptrTy,
                                                 false,
                                                 GlobalVariable::InternalLinkage,
                                                 ConstantExpr::getInBoundsGetElementPtr(varBUFTy, varBUF, getInt(1)),
                                                 "boardNext");

FunctionType *fnMainTy = FunctionType::get(intTy, {intTy, ptrTy}, false);
Function *fnMain = Function::Create(fnMainTy, Function::ExternalLinkage, "main", module);

FunctionType *voidFnTy = FunctionType::get(voidTy, false);
FunctionCallee fnSimBegin = module->getOrInsertFunction("simBegin", voidFnTy);
FunctionCallee fnSimFlush = module->getOrInsertFunction("simFlush", voidFnTy);
FunctionCallee fnSimEnd = module->getOrInsertFunction("simEnd", voidFnTy);

FunctionType *fnSimShouldContinueTy = FunctionType::get(intTy, false);
FunctionCallee fnSimShouldContinue = module->getOrInsertFunction("simShouldContinue", fnSimShouldContinueTy);
// FunctionCallee fnSimSetPixel = module->getOrInsertFunction("simSetPixel");

void defineMain() {
    BasicBlock *bbEntry = BasicBlock::Create(context, "", fnMain);
    builder.SetInsertPoint(bbEntry);
    builder.CreateCall(fnSimBegin)->setTailCall();

    BasicBlock *bb11 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb128 = BasicBlock::Create(context, "", fnMain);

    // initBoard
    Value *val3 = builder.CreateAlignedLoad(ptrTy, varBoardSrc, {});
    Value *val4 = builder.CreateInBoundsGEP(intTy, val3, {getInt(1)});
    builder.CreateStore(getInt(1), val4);
    Value *val5 = builder.CreateInBoundsGEP(intTy, val3, {getInt(SIM_X_SIZE + 2)});
    builder.CreateStore(getInt(1), val5);
    Value *val6 = builder.CreateInBoundsGEP(intTy, val3, {getInt(SIM_X_SIZE * 2)});
    builder.CreateStore(getInt(1), val6);
    Value *val7 = builder.CreateInBoundsGEP(intTy, val3, {getInt(SIM_X_SIZE * 2 + 1)});
    builder.CreateStore(getInt(1), val7);
    Value *val8 = builder.CreateInBoundsGEP(intTy, val3, {getInt(SIM_X_SIZE * 2 + 2)});
    builder.CreateStore(getInt(1), val8);

    // First check of loop condition
    CallInst *val9 = builder.CreateCall(fnSimShouldContinue);
    val9->setTailCall();
    Value *val10 = builder.CreateCmp(CmpInst::ICMP_EQ, val9, getInt(0));
    builder.CreateCondBr(val10, bb128, bb11);

    builder.SetInsertPoint(bb11);

    builder.SetInsertPoint(bb128);
    builder.CreateCall(fnSimEnd)->setTailCall();
    builder.CreateRet(ConstantInt::get(intTy, 0));
}

int main() {
    defineMain();
    outs() << "Module code:\n////\n" << *module << "////\n";

    return 0;
}
