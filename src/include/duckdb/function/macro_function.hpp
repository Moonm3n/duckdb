//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/macro_function.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/function/function.hpp"
#include "duckdb/main/client_context.hpp"
#include "duckdb/planner/binder.hpp"
#include "duckdb/planner/expression_binder.hpp"

namespace duckdb {

class MacroFunctionCatalogEntry;

class MacroFunction {
public:
	MacroFunction(unique_ptr<ParsedExpression> expression);
	static unique_ptr<Expression> BindMacroFunction(ClientContext &context, Binder &binder, ExpressionBinder &expr_binder,
	                                                MacroFunctionCatalogEntry &function,
	                                                vector<unique_ptr<Expression>> arguments, string &error);
	//! The macro expression
	unique_ptr<ParsedExpression> expression;
	//! The macro parameters
	vector<unique_ptr<ParsedExpression>> parameters;
};

} // namespace duckdb
