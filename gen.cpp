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
Module *module = new Module("", context);
IRBuilder<> builder(context);

// Type *charTy = builder.getInt8Ty();
Type *boolTy = builder.getInt1Ty();
Type *intTy = builder.getInt32Ty();
Type *longTy = builder.getInt64Ty();
Type *ptrTy = builder.getPtrTy();
Type *voidTy = builder.getVoidTy();

Constant *getInt(int32_t val) { return ConstantInt::get(intTy, val, true); }
Constant *getBool(int val) { return ConstantInt::get(boolTy, val); }

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
    Value *val28 = builder.CreateAlignedLoad(ptrTy, varBoardSrc, {});
    Value *val29 = builder.CreateAdd(val27, getInt(-1), "", false, true);
    Value *val30 = builder.CreateICmpULT(val29, getInt(SIM_X_SIZE));
    Value *val31 = builder.CreateSelect(val15, val30, getBool(0));
    builder.CreateCondBr(val31, bb32, bb37);

    builder.SetInsertPoint(bb32);
    Value *val33 = builder.CreateAdd(val29, val16, "", true, true);
    Value *val34 = builder.CreateZExt(val33, longTy);
    Value *val35 = builder.CreateInBoundsGEP(intTy, val28, val33);
    Value *val36 = builder.CreateAlignedLoad(intTy, val35, {});
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
    Value *val46 = builder.CreateAlignedLoad(intTy, val45, {});
    Value *val47 = builder.CreateAdd(val46, val42, "", false, true);
    Value *val48 = builder.CreateAdd(val27, getInt(1), "", true, true);
    Value *val49 = builder.CreateICmpNE(val27, getInt(SIM_X_SIZE - 1));
    Value *val50 = builder.CreateSelect(val15, val49, getBool(0));
    builder.CreateCondBr(val50, bb51, bb57);

    builder.SetInsertPoint(bb51);
    Value *val52 = builder.CreateAdd(val48, val16, "", true, true);
    Value *val53 = builder.CreateZExt(val52, longTy);
    Value *val54 = builder.CreateInBoundsGEP(intTy, val28, val53);
    Value *val55 = builder.CreateAlignedLoad(intTy, val54, {});
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
    Value *val66 = builder.CreateAlignedLoad(intTy, val65, {});
    Value *val67 = builder.CreateAdd(val66, val60, "", false, true);
    builder.CreateBr(bb69);

    builder.SetInsertPoint(bb68);
    builder.CreateCondBr(val12, bb69, bb83);
    /*
69:                                               ; preds = %68, %62
  %70 = phi i32 [ %67, %62 ], [ %60, %68 ]
  %71 = or i32 %27, %17
  %72 = zext i32 %71 to i64
  %73 = getelementptr inbounds i32, ptr %28, i64 %72
  %74 = load i32, ptr %73, align 4, !tbaa !9
  %75 = add nsw i32 %74, %70
  %76 = select i1 %12, i1 %58, i1 false
  br i1 %76, label %77, label %83

77:                                               ; preds = %69
  %78 = add nuw nsw i32 %59, %17
  %79 = zext i32 %78 to i64
  %80 = getelementptr inbounds i32, ptr %28, i64 %79
  %81 = load i32, ptr %80, align 4, !tbaa !9
  %82 = add nsw i32 %81, %75
  br label %83

83:                                               ; preds = %77, %69, %68
  %84 = phi i32 [ %82, %77 ], [ %75, %69 ], [ %60, %68 ]
  %85 = select i1 %18, i1 %30, i1 false
  br i1 %85, label %86, label %92

86:                                               ; preds = %83
  %87 = add nuw nsw i32 %29, %19
  %88 = zext i32 %87 to i64
  %89 = getelementptr inbounds i32, ptr %28, i64 %88
  %90 = load i32, ptr %89, align 4, !tbaa !9
  %91 = add nsw i32 %90, %84
  br label %93

92:                                               ; preds = %83
  br i1 %18, label %93, label %107

93:                                               ; preds = %92, %86
  %94 = phi i32 [ %91, %86 ], [ %84, %92 ]
  %95 = or i32 %27, %19
  %96 = zext i32 %95 to i64
  %97 = getelementptr inbounds i32, ptr %28, i64 %96
  %98 = load i32, ptr %97, align 4, !tbaa !9
  %99 = add nsw i32 %98, %94
  %100 = select i1 %18, i1 %58, i1 false
  br i1 %100, label %101, label %107

101:                                              ; preds = %93
  %102 = add nuw nsw i32 %59, %19
  %103 = zext i32 %102 to i64
  %104 = getelementptr inbounds i32, ptr %28, i64 %103
  %105 = load i32, ptr %104, align 4, !tbaa !9
  %106 = add nsw i32 %105, %99
  br label %107

107:                                              ; preds = %101, %93, %92
  %108 = phi i32 [ %106, %101 ], [ %99, %93 ], [ %84, %92 ]
  %109 = or i32 %27, %17
  %110 = zext i32 %109 to i64
  %111 = getelementptr inbounds i32, ptr %28, i64 %110
  %112 = load i32, ptr %111, align 4, !tbaa !9
  %113 = icmp eq i32 %112, 0
  %114 = icmp eq i32 %108, 3
  %115 = add i32 %108, -3
  %116 = icmp ult i32 %115, 2
  %117 = select i1 %113, i1 %114, i1 %116
  %118 = zext i1 %117 to i32
  %119 = load ptr, ptr @board_next, align 8, !tbaa !5
  %120 = getelementptr inbounds i32, ptr %119, i64 %110
  store i32 %118, ptr %120, align 4, !tbaa !9
  %121 = select i1 %117, i32 0, i32 16777215
  tail call void @simSetPixel(i32 noundef %27, i32 noundef %13, i32 noundef %121) #2
  %122 = icmp ult i32 %59, 64
  br i1 %122, label %26, label %20, !llvm.loop !13

123:                                              ; preds = %20
  %124 = load ptr, ptr @board, align 8, !tbaa !5
  %125 = load ptr, ptr @board_next, align 8, !tbaa !5
  store ptr %125, ptr @board, align 8, !tbaa !5
  store ptr %124, ptr @board_next, align 8, !tbaa !5
  tail call void (...) @simFlush() #2
  %126 = tail call i32 (...) @simShouldContinue() #2
  %127 = icmp eq i32 %126, 0
  br i1 %127, label %128, label %23

128:                                              ; preds = %123, %2
  tail call void (...) @simEnd() #2
  ret i32 0
    */

    builder.SetInsertPoint(bb128);
    builder.CreateCall(fnSimEnd)->setTailCall();
    builder.CreateRet(getInt(0));
}

int main() {
    defineMain();
    outs() << "Module code:\n////\n" << *module << "////\n";

    return 0;
}
