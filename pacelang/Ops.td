#ifndef PACEOP
#define PACEOP

include "mlir/IR/OpBase.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

def PaceDialect : Dialect {
    let name = "pacelang";
    let cppNamespace = "::mlir::pacelang";
}

class PaceOp<string mnemonic, list<Trait> traits = []>:
    Op<PaceDialect,mnemonic,traits>;


// OPS

def ConstOp : PaceOp<"constant", [Pure]> {
    let arguments = (ins F64ElementsAttr:$value);
    let results = (outs F64Tensor);
    let hasCustomAssemblyFormat = 1;

    let builders = [
    OpBuilder<(ins "double":$value)>
    ];

    let hasVerifier = 1;
}


#endif //PACEOP