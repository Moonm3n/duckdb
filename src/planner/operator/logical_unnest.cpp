#include "duckdb/common/field_writer.hpp"
#include "duckdb/planner/operator/logical_unnest.hpp"

namespace duckdb {

vector<ColumnBinding> LogicalUnnest::GetColumnBindings() {
	auto child_bindings = children[0]->GetColumnBindings();
	for (idx_t i = 0; i < expressions.size(); i++) {
		child_bindings.emplace_back(unnest_index, i);
	}
	return child_bindings;
}

void LogicalUnnest::ResolveTypes() {
	types.insert(types.end(), children[0]->types.begin(), children[0]->types.end());
	for (auto &expr : expressions) {
		types.push_back(expr->return_type);
	}
}

void LogicalUnnest::Serialize(FieldWriter &writer) const {
	writer.WriteField(unnest_index);
}

unique_ptr<LogicalOperator> LogicalUnnest::Deserialize(LogicalDeserializationState &state, FieldReader &reader) {
	auto unnest_index = reader.ReadRequired<idx_t>();
	return make_unique<LogicalUnnest>(unnest_index);
}
} // namespace duckdb
