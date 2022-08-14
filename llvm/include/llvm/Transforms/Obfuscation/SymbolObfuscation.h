//
//  SymbolObfuscation.h
//  LLVM
//
//  Created by niu_o0 on 2022/7/30.
//

#ifndef SymbolObfuscation_h
#define SymbolObfuscation_h

#include "llvm/Pass.h"
#include <ostream>

namespace llvm {
ModulePass* createSymbolObfuscationPass();
}

#endif /* SymbolObfuscation_h */
