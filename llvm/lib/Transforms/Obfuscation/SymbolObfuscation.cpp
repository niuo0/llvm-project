//
//  SymbolObfuscation.cpp
//  LLVMObfuscation
//
//  Created by niu_o0 on 2022/7/30.
//


#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Obfuscation/SymbolObfuscation.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace llvm;
using namespace std;
static string obfcharacters="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
namespace llvm{
    struct SymbolObfuscation : public llvm::ModulePass {
        static char ID;
        int seed = 0;
        SymbolObfuscation() : ModulePass(ID) {}
        string randomString(int length){
            string name = "$";
            name.resize(length+1);
            srand(seed);
            seed++;
            for(int i = 1; i <= length; i++){
                name[i] = obfcharacters[rand()%(obfcharacters.length())];
            }
            return name;
        }
        bool runOnModule(Module &M) override {
            
            errs()<<"Start Symbol Rewrite!\n";
            
            for (Module::global_iterator Glo = M.global_begin(); Glo != M.global_end(); Glo++) {
                
                GlobalVariable &V = *Glo;
                
                string name = V.getName().str();
                if (name.rfind("ERBypuVBafrcfFEXzWttPybmEMdNNVYQV", 0) == 0 ||
                    name.rfind("$kpfckufgVuflzrhxqDtdCWDTZpmCfPFA", 0) == 0) {
                    //Rename
                    string newname = randomString(256);
                    errs()<<"Renaming GlobalVariable: "<<name<<" --> New Name: "<<newname<<"\n";
                    V.setName(newname);
                    
                }else {
                    //errs() << V.getName() << "\n";
                }
                
            }
            
            errs() << "-------------start function------------";
            
            for(Module::iterator Fun=M.begin();Fun!=M.end();Fun++){
                Function &F=*Fun;
                
                if (F.empty()) continue;
                
                string name = F.getName().str();
                
                //errs() << name << "\n";
                
                if (name.rfind("$xRDpsoQUkrANREHhfwvVkOZ", 0) == 0 ||
                    name.rfind("$vERBypuVBafrcfFEXzWStPy", 0) == 0 ||
                    name.rfind("$CYmzUhtGmzysMiDnuRFXPSt", 0) == 0 ||
                    name.rfind("$YkEonaSsynGyvpCaJPzWwUQ", 0) == 0 ) {
                    //Rename
                    string newname = randomString(256);
                    errs()<<"Renaming Function: "<<name<<" --> New Name: "<<newname<<"\n";
                    F.setName(newname);
                }
//                if (F.getName().str().compare("main")==0){
//                    errs()<<"Skipping main\n";
//                }
//                else if(F.empty()==false){
//                    //Rename
//                    string newname = randomString(16);
//                    errs()<<"Renaming Function: "<<F.getName()<<" --> New Name: "<<newname<<"\n";
//                    F.setName(newname);
//                }
//                else{
//                    errs()<<"Skipping External Function: "<<F.getName()<<"\n";
//                }
            }
            
            errs() << "End Symbol Rewrite!\n";
            
            return true;
        }
    };
    
}

char SymbolObfuscation::ID = 0;
//INITIALIZE_PASS(SymbolObfuscation, "symbolobf", "Rewrite Symbols", false, false)
//static RegisterPass<SymbolObfuscation> X("symbolobf", "Rewrite Symbols", false, false);

ModulePass * llvm::createSymbolObfuscationPass() {
    cout<<"Initializing SymbolObf!!!"<<endl;
    return new SymbolObfuscation();
}
