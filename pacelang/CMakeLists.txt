get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(translation_libs GLOBAL PROPERTY MLIR_TRANSLATION_LIBS)


set(LLVM_TARGET_DEFINITIONS Ops.td)
mlir_tablegen(Ops.h.inc -gen-op-decls)
mlir_tablegen(Ops.cpp.inc -gen-op-defs)
mlir_tablegen(Dialect.h.inc -gen-dialect-decls)
mlir_tablegen(Dialect.cpp.inc -gen-dialect-defs)
add_public_tablegen_target(MLIRpacelangIncGen)

# Define the location for generated include files
set(GENERATED_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/pacelang)
file(MAKE_DIRECTORY ${GENERATED_INCLUDE_DIR})


add_llvm_executable(
  pacelang
  main.cpp
  Dialect.cpp

  DEPENDS
  MLIRpacelangIncGen)

  llvm_update_compile_flags(pacelang)


target_link_libraries(
  pacelang
  PRIVATE ${dialect_libs}
          ${translation_libs}
          MLIRAnalysis
          MLIRIR
          MLIRParser
          MLIRPass
          MLIRSPIRVDialect
          MLIRTranslateLib
          MLIRSupport
          MLIRSideEffectInterfaces
          MLIRTransforms)

mlir_check_link_libraries(pacelang)

# Include the directory with generated .inc files
target_include_directories(pacelang PRIVATE
  ${CMAKE_BINARY_DIR}
)