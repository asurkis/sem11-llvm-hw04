#include "hw01/sim.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

using namespace llvm;

LLVMContext context;
Module *module = new Module("main.c", context);
IRBuilder<> builder(context);

// Type *charTy = builder.getInt8Ty();
Type *boolTy = builder.getInt1Ty();
Type *intTy = builder.getInt32Ty();
Type *longTy = builder.getInt64Ty();
Type *ptrTy = builder.getPtrTy();
Type *voidTy = builder.getVoidTy();

Constant *getInt(int32_t val) { return ConstantInt::get(intTy, val, true); }
Constant *getLong(int64_t val) { return ConstantInt::get(longTy, val, true); }
Constant *getBool(int val) { return ConstantInt::get(boolTy, val); }

constexpr uint64_t layerSize = SIM_X_SIZE * SIM_Y_SIZE;
Type *boardTy = ArrayType::get(intTy, layerSize);
Type *varBUFTy = ArrayType::get(boardTy, 2);
GlobalVariable *varBUF = new GlobalVariable(
    *module, varBUFTy, false, GlobalVariable::PrivateLinkage, ConstantAggregateZero::get(intTy), "BUF");

GlobalVariable *varBoardSrc
    = new GlobalVariable(*module, ptrTy, false, GlobalVariable::PrivateLinkage, varBUF, "board");

Constant *idxList[] = {getLong(0), getLong(1), getLong(0)};
GlobalVariable *varBoardDst = new GlobalVariable(*module,
                                                 ptrTy,
                                                 false,
                                                 GlobalVariable::InternalLinkage,
                                                 ConstantExpr::getInBoundsGetElementPtr(varBUFTy, varBUF, idxList),
                                                 "boardNext");

FunctionType *fnMainTy = FunctionType::get(intTy, {intTy, ptrTy}, false);
Function *fnMain = Function::Create(fnMainTy, Function::ExternalLinkage, "main", module);

FunctionType *voidFnTy = FunctionType::get(voidTy, false);
FunctionCallee fnSimBegin = module->getOrInsertFunction("simBegin", voidFnTy);
FunctionCallee fnSimFlush = module->getOrInsertFunction("simFlush", voidFnTy);
FunctionCallee fnSimEnd = module->getOrInsertFunction("simEnd", voidFnTy);

FunctionType *fnSimShouldContinueTy = FunctionType::get(intTy, false);
FunctionCallee fnSimShouldContinue = module->getOrInsertFunction("simShouldContinue", fnSimShouldContinueTy);

FunctionType *fnSimSetPixelTy = FunctionType::get(voidTy, {intTy, intTy, intTy}, false);
FunctionCallee fnSimSetPixel = module->getOrInsertFunction("simSetPixel", fnSimSetPixelTy);

void defineMain() {
    module->setTargetTriple("x86_64-pc-linux-gnu");
    BasicBlock *bb2 = BasicBlock::Create(context, "", fnMain);
    builder.SetInsertPoint(bb2);
    builder.CreateCall(fnSimBegin)->setTailCall();

    BasicBlock *bb11 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb20 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb23 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb26 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb32 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb37 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb38 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb41 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb51 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb57 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb62 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb68 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb69 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb77 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb83 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb86 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb92 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb93 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb101 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb107 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb123 = BasicBlock::Create(context, "", fnMain);
    BasicBlock *bb128 = BasicBlock::Create(context, "", fnMain);

    // initBoard
    Value *val3 = builder.CreateLoad(ptrTy, varBoardSrc);
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
    Value *val10 = builder.CreateICmpEQ(val9, getInt(0));
    builder.CreateCondBr(val10, bb128, bb11);

    builder.SetInsertPoint(bb11);
    // %12 = phi i1 [ %24, %23 ], [ true, %2 ]
    // %13 = phi i32 [ %25, %23 ], [ 0, %2 ]
    PHINode *val12 = builder.CreatePHI(boolTy, 1);
    PHINode *val13 = builder.CreatePHI(intTy, 1);
    Value *val14 = builder.CreateNSWAdd(val13, getInt(-1));
    Value *val15 = builder.CreateICmpULT(val14, getInt(SIM_Y_SIZE));
    // x * 64 == x << 6
    Value *val16 = builder.CreateShl(val14, getInt(6), "", true, true);
    Value *val17 = builder.CreateShl(val13, getInt(6));
    Value *val18 = builder.CreateICmpULT(val13, getInt(SIM_Y_SIZE - 1));
    Value *val19 = builder.CreateAdd(val17, getInt(SIM_X_SIZE), "", true, true);
    builder.CreateBr(bb26);

    builder.SetInsertPoint(bb20);
    Value *val21 = builder.CreateAdd(val13, getInt(1), "", true, true);
    Value *val22 = builder.CreateICmpEQ(val21, getInt(SIM_Y_SIZE));
    builder.CreateCondBr(val22, bb123, bb23);

    builder.SetInsertPoint(bb23);
    // %24 = phi i1 [ %18, %20 ], [ true, %123 ]
    // %25 = phi i32 [ %21, %20 ], [ 0, %123 ]
    PHINode *val24 = builder.CreatePHI(boolTy, 1);
    PHINode *val25 = builder.CreatePHI(intTy, 1);
    // Ignoring metadata
    builder.CreateBr(bb11);

    builder.SetInsertPoint(bb26);
    // %27 = phi i32 [ 0, %11 ], [ %59, %107 ]
    PHINode *val27 = builder.CreatePHI(intTy, 1);
    Value *val28 = builder.CreateLoad(ptrTy, varBoardSrc);
    Value *val29 = builder.CreateAdd(val27, getInt(-1), "", false, true);
    Value *val30 = builder.CreateICmpULT(val29, getInt(SIM_X_SIZE));
    Value *val31 = builder.CreateSelect(val15, val30, getBool(0));
    builder.CreateCondBr(val31, bb32, bb37);

    builder.SetInsertPoint(bb32);
    Value *val33 = builder.CreateAdd(val29, val16, "", true, true);
    Value *val34 = builder.CreateZExt(val33, longTy);
    Value *val35 = builder.CreateInBoundsGEP(intTy, val28, val34);
    Value *val36 = builder.CreateLoad(intTy, val35);
    builder.CreateBr(bb41);

    builder.SetInsertPoint(bb37);
    builder.CreateCondBr(val15, bb41, bb38);

    builder.SetInsertPoint(bb38);
    Value *val39 = builder.CreateAdd(val27, getInt(1), "", true, true);
    Value *val40 = builder.CreateICmpNE(val27, getInt(SIM_X_SIZE - 1));
    builder.CreateBr(bb57);

    builder.SetInsertPoint(bb41);
    // %42 = phi i32 [ %36, %32 ], [ 0, %37 ]
    PHINode *val42 = builder.CreatePHI(intTy, 1);
    Value *val43 = builder.CreateOr(val27, val16);
    Value *val44 = builder.CreateZExt(val43, longTy);
    Value *val45 = builder.CreateInBoundsGEP(intTy, val28, val44);
    Value *val46 = builder.CreateLoad(intTy, val45);
    Value *val47 = builder.CreateAdd(val46, val42, "", false, true);
    Value *val48 = builder.CreateAdd(val27, getInt(1), "", true, true);
    Value *val49 = builder.CreateICmpNE(val27, getInt(SIM_X_SIZE - 1));
    Value *val50 = builder.CreateSelect(val15, val49, getBool(0));
    builder.CreateCondBr(val50, bb51, bb57);

    builder.SetInsertPoint(bb51);
    Value *val52 = builder.CreateAdd(val48, val16, "", true, true);
    Value *val53 = builder.CreateZExt(val52, longTy);
    Value *val54 = builder.CreateInBoundsGEP(intTy, val28, val53);
    Value *val55 = builder.CreateLoad(intTy, val54);
    Value *val56 = builder.CreateAdd(val55, val47, "", false, true);
    builder.CreateBr(bb57);

    builder.SetInsertPoint(bb57);
    // %58 = phi i1 [ true, %51 ], [ %49, %41 ], [ %40, %38 ]
    // %59 = phi i32 [ %48, %51 ], [ %48, %41 ], [ %39, %38 ]
    // %60 = phi i32 [ %56, %51 ], [ %47, %41 ], [ 0, %38 ]
    PHINode *val58 = builder.CreatePHI(boolTy, 3);
    PHINode *val59 = builder.CreatePHI(intTy, 3);
    PHINode *val60 = builder.CreatePHI(intTy, 3);
    Value *val61 = builder.CreateSelect(val12, val30, getBool(false));
    builder.CreateCondBr(val61, bb62, bb68);

    builder.SetInsertPoint(bb62);
    Value *val63 = builder.CreateAdd(val29, val17, "", true, true);
    Value *val64 = builder.CreateZExt(val63, longTy);
    Value *val65 = builder.CreateInBoundsGEP(intTy, val28, val64);
    Value *val66 = builder.CreateLoad(intTy, val65);
    Value *val67 = builder.CreateAdd(val66, val60, "", false, true);
    builder.CreateBr(bb69);

    builder.SetInsertPoint(bb68);
    builder.CreateCondBr(val12, bb69, bb83);

    builder.SetInsertPoint(bb69);
    // %70 = phi i32 [ %67, %62 ], [ %60, %68 ]
    PHINode *val70 = builder.CreatePHI(intTy, 2);
    Value *val71 = builder.CreateOr(val27, val17);
    Value *val72 = builder.CreateZExt(val71, longTy);
    Value *val73 = builder.CreateInBoundsGEP(intTy, val28, val72);
    Value *val74 = builder.CreateLoad(intTy, val73);
    Value *val75 = builder.CreateAdd(val74, val70, "", false, true);
    Value *val76 = builder.CreateSelect(val12, val58, getBool(0));
    builder.CreateCondBr(val76, bb77, bb83);

    builder.SetInsertPoint(bb77);
    Value *val78 = builder.CreateAdd(val59, val17, "", true, true);
    Value *val79 = builder.CreateZExt(val78, longTy);
    Value *val80 = builder.CreateInBoundsGEP(intTy, val28, val79);
    Value *val81 = builder.CreateLoad(intTy, val80);
    Value *val82 = builder.CreateAdd(val81, val75, "", false, true);
    builder.CreateBr(bb83);

    builder.SetInsertPoint(bb83);
    // %84 = phi i32 [ %82, %77 ], [ %75, %69 ], [ %60, %68 ]
    PHINode *val84 = builder.CreatePHI(intTy, 3);
    Value *val85 = builder.CreateSelect(val18, val30, getBool(0));
    builder.CreateCondBr(val85, bb86, bb92);

    builder.SetInsertPoint(bb86);
    Value *val87 = builder.CreateAdd(val29, val19, "", true, true);
    Value *val88 = builder.CreateZExt(val87, longTy);
    Value *val89 = builder.CreateInBoundsGEP(intTy, val28, val88);
    Value *val90 = builder.CreateLoad(intTy, val89);
    Value *val91 = builder.CreateAdd(val90, val84, "", false, true);
    builder.CreateBr(bb93);

    builder.SetInsertPoint(bb92);
    builder.CreateCondBr(val18, bb93, bb107);

    builder.SetInsertPoint(bb93);
    // %94 = phi i32 [ %91, %86 ], [ %84, %92 ]
    PHINode *val94 = builder.CreatePHI(intTy, 2);
    Value *val95 = builder.CreateOr(val27, val19);
    Value *val96 = builder.CreateZExt(val95, longTy);
    Value *val97 = builder.CreateInBoundsGEP(intTy, val28, val96);
    Value *val98 = builder.CreateLoad(intTy, val97);
    Value *val99 = builder.CreateAdd(val98, val94, "", false, true);
    Value *val100 = builder.CreateSelect(val18, val58, getBool(0));
    builder.CreateCondBr(val100, bb101, bb107);

    builder.SetInsertPoint(bb101);
    Value *val102 = builder.CreateAdd(val59, val19, "", true, true);
    Value *val103 = builder.CreateZExt(val102, longTy);
    Value *val104 = builder.CreateInBoundsGEP(intTy, val28, val103);
    Value *val105 = builder.CreateLoad(intTy, val104);
    Value *val106 = builder.CreateAdd(val105, val99, "", false, true);
    builder.CreateBr(bb107);

    builder.SetInsertPoint(bb107);
    // %108 = phi i32 [ %106, %101 ], [ %99, %93 ], [ %84, %92 ]
    PHINode *val108 = builder.CreatePHI(intTy, 3);
    Value *val109 = builder.CreateOr(val27, val17);
    Value *val110 = builder.CreateZExt(val109, longTy);
    Value *val111 = builder.CreateInBoundsGEP(intTy, val28, val110);
    Value *val112 = builder.CreateLoad(intTy, val111);
    Value *val113 = builder.CreateICmpEQ(val112, getInt(0));
    Value *val114 = builder.CreateICmpEQ(val108, getInt(3));
    Value *val115 = builder.CreateAdd(val108, getInt(-3));
    Value *val116 = builder.CreateICmpULT(val115, getInt(2));
    Value *val117 = builder.CreateSelect(val113, val114, val116);
    Value *val118 = builder.CreateZExt(val117, intTy);
    Value *val119 = builder.CreateLoad(ptrTy, varBoardDst);
    Value *val120 = builder.CreateInBoundsGEP(intTy, val119, val110);
    builder.CreateStore(val118, val120);
    Value *val121 = builder.CreateSelect(val117, getInt(0), getInt(0xFFFFFF));
    builder.CreateCall(fnSimSetPixel, {val27, val13, val121})->setTailCall();
    Value *val122 = builder.CreateICmpULT(val59, getInt(SIM_X_SIZE));
    builder.CreateCondBr(val122, bb26, bb20);

    builder.SetInsertPoint(bb123);
    Value *val124 = builder.CreateLoad(ptrTy, varBoardSrc);
    Value *val125 = builder.CreateLoad(ptrTy, varBoardDst);
    builder.CreateStore(val125, varBoardSrc);
    builder.CreateStore(val124, varBoardDst);
    builder.CreateCall(fnSimFlush)->setTailCall();
    CallInst *val126 = builder.CreateCall(fnSimShouldContinue);
    val126->setTailCall();
    Value *val127 = builder.CreateICmpEQ(val126, getInt(0));
    builder.CreateCondBr(val127, bb128, bb23);

    builder.SetInsertPoint(bb128);
    builder.CreateCall(fnSimEnd)->setTailCall();
    builder.CreateRet(getInt(0));

    // %12 = phi i1 [ %24, %23 ], [ true, %2 ]
    val12->addIncoming(val24, bb23);
    val12->addIncoming(getBool(1), bb2);
    // %13 = phi i32 [ %25, %23 ], [ 0, %2 ]
    val13->addIncoming(val25, bb23);
    val13->addIncoming(getInt(0), bb2);
    // %24 = phi i1 [ %18, %20 ], [ true, %123 ]
    val24->addIncoming(val18, bb20);
    val24->addIncoming(getBool(1), bb123);
    // %25 = phi i32 [ %21, %20 ], [ 0, %123 ]
    val25->addIncoming(val21, bb20);
    val25->addIncoming(getInt(0), bb123);
    // %27 = phi i32 [ 0, %11 ], [ %59, %107 ]
    val27->addIncoming(getInt(0), bb11);
    val27->addIncoming(val59, bb107);
    // %42 = phi i32 [ %36, %32 ], [ 0, %37 ]
    val42->addIncoming(val36, bb32);
    val42->addIncoming(getInt(0), bb37);
    // %58 = phi i1 [ true, %51 ], [ %49, %41 ], [ %40, %38 ]
    val58->addIncoming(getBool(1), bb51);
    val58->addIncoming(val49, bb41);
    val58->addIncoming(val40, bb38);
    // %59 = phi i32 [ %48, %51 ], [ %48, %41 ], [ %39, %38 ]
    val59->addIncoming(val48, bb51);
    val59->addIncoming(val48, bb41);
    val59->addIncoming(val39, bb38);
    // %60 = phi i32 [ %56, %51 ], [ %47, %41 ], [ 0, %38 ]
    val60->addIncoming(val56, bb51);
    val60->addIncoming(val47, bb41);
    val60->addIncoming(getInt(0), bb38);
    // %70 = phi i32 [ %67, %62 ], [ %60, %68 ]
    val70->addIncoming(val67, bb62);
    val70->addIncoming(val60, bb68);
    // %84 = phi i32 [ %82, %77 ], [ %75, %69 ], [ %60, %68 ]
    val84->addIncoming(val82, bb77);
    val84->addIncoming(val75, bb69);
    val84->addIncoming(val60, bb68);
    // %94 = phi i32 [ %91, %86 ], [ %84, %92 ]
    val94->addIncoming(val91, bb86);
    val94->addIncoming(val84, bb92);
    // %108 = phi i32 [ %106, %101 ], [ %99, %93 ], [ %84, %92 ]
    val108->addIncoming(val106, bb101);
    val108->addIncoming(val99, bb93);
    val108->addIncoming(val84, bb92);
}

int main() {
    defineMain();
    outs() << *module;

    return 0;
}
