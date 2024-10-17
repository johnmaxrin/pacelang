#include "Dialect.h"

#include "mlir/IR/Builders.h"      // For mlir::OpBuilder
#include "mlir/IR/Operation.h"     // For mlir::Operation
#include "mlir/IR/Dialect.h"       // For mlir::Dialect

#include "mlir/IR/AsmState.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Verifier.h"
#include "mlir/Parser/Parser.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"


using namespace mlir::pacelang;


int main()
{
    mlir::MLIRContext context;
    mlir::OpBuilder builder(&context);

    context.loadDialect<mlir::pacelang::PaceDialect>();
    context.loadDialect<mlir::func::FuncDialect>();

    mlir::ModuleOp theModule = mlir::ModuleOp::create(builder.getUnknownLoc());

    
    auto funcTy = builder.getFunctionType({},builder.getIntegerType(32));
    auto funcBl = mlir::func::FuncOp::create(builder.getUnknownLoc(), "foo", funcTy);

    //auto &entryBlock = *funcBl.addEntryBlock();
    //builder.setInsertionPointToEnd(&entryBlock);

    auto conop = builder.create< mlir::pacelang::ConstOp>(builder.getUnknownLoc(), (double)33.0);

    theModule.push_back(funcBl);
    theModule.push_back(conop);   

    builder.create<mlir::func::ReturnOp>(builder.getUnknownLoc()); 

    theModule.dump();




    return 0;
}