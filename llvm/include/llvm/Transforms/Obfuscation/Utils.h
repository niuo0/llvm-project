#ifndef __UTILS_OBF__
#define __UTILS_OBF__

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Utils/Local.h" // For DemoteRegToStack and DemotePHIToStack
#include <stdio.h>
#include <sstream>
#include <map>
#include <set>

#define INIT_CONTEXT(X) CONTEXT=&X.getContext()
#define TYPE_I64 Type::getInt64Ty(*CONTEXT)
#define TYPE_I32 Type::getInt32Ty(*CONTEXT)
#define TYPE_I8 Type::getInt8Ty(*CONTEXT)
#define GET_TYPE(X) TYPE::getInt(X)Ty(*CONTEXT)
#define CONST_I64(V) ConstantInt::get(TYPE_I64, V, false)
#define CONST_I32(V) ConstantInt::get(TYPE_I32, V, false)
#define CONST_I8(V) ConstantInt::get(TYPE_I8, V, false)
#define CONST(T, V) ConstantInt::get(T, V)
#define RANDOM(X) (cryptoutils->get_uint8_t() % 100 < X)

extern llvm::LLVMContext *CONTEXT;

void fixStack(llvm::Function *f);
std::string readAnnotate(llvm::Function *f);
std::map<llvm::GlobalValue*,llvm::StringRef> BuildAnnotateMap(llvm::Module& M);
bool toObfuscate(bool flag, llvm::Function *f, std::string attribute);
void FixBasicBlockConstantExpr(llvm::BasicBlock *BB);
void FixFunctionConstantExpr(llvm::Function *Func);
void appendToAnnotations(llvm::Module &M,llvm::ConstantStruct *Data);
#endif
