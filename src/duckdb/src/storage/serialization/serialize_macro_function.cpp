//===----------------------------------------------------------------------===//
// This file is automatically generated by scripts/generate_serialization.py
// Do not edit this file manually, your changes will be overwritten
//===----------------------------------------------------------------------===//

#include "duckdb/common/serializer/serializer.hpp"
#include "duckdb/common/serializer/deserializer.hpp"
#include "duckdb/function/macro_function.hpp"
#include "duckdb/function/scalar_macro_function.hpp"
#include "duckdb/function/table_macro_function.hpp"

namespace duckdb {

void MacroFunction::Serialize(Serializer &serializer) const {
	serializer.WriteProperty<MacroType>(100, "type", type);
	serializer.WritePropertyWithDefault<vector<unique_ptr<ParsedExpression>>>(101, "parameters", parameters);
	serializer.WritePropertyWithDefault<case_insensitive_map_t<unique_ptr<ParsedExpression>>>(102, "default_parameters", default_parameters);
}

unique_ptr<MacroFunction> MacroFunction::Deserialize(Deserializer &deserializer) {
	auto type = deserializer.ReadProperty<MacroType>(100, "type");
	auto parameters = deserializer.ReadPropertyWithDefault<vector<unique_ptr<ParsedExpression>>>(101, "parameters");
	auto default_parameters = deserializer.ReadPropertyWithDefault<case_insensitive_map_t<unique_ptr<ParsedExpression>>>(102, "default_parameters");
	unique_ptr<MacroFunction> result;
	switch (type) {
	case MacroType::SCALAR_MACRO:
		result = ScalarMacroFunction::Deserialize(deserializer);
		break;
	case MacroType::TABLE_MACRO:
		result = TableMacroFunction::Deserialize(deserializer);
		break;
	default:
		throw SerializationException("Unsupported type for deserialization of MacroFunction!");
	}
	result->parameters = std::move(parameters);
	result->default_parameters = std::move(default_parameters);
	return result;
}

void ScalarMacroFunction::Serialize(Serializer &serializer) const {
	MacroFunction::Serialize(serializer);
	serializer.WritePropertyWithDefault<unique_ptr<ParsedExpression>>(200, "expression", expression);
}

unique_ptr<MacroFunction> ScalarMacroFunction::Deserialize(Deserializer &deserializer) {
	auto result = duckdb::unique_ptr<ScalarMacroFunction>(new ScalarMacroFunction());
	deserializer.ReadPropertyWithDefault<unique_ptr<ParsedExpression>>(200, "expression", result->expression);
	return std::move(result);
}

void TableMacroFunction::Serialize(Serializer &serializer) const {
	MacroFunction::Serialize(serializer);
	serializer.WritePropertyWithDefault<unique_ptr<QueryNode>>(200, "query_node", query_node);
}

unique_ptr<MacroFunction> TableMacroFunction::Deserialize(Deserializer &deserializer) {
	auto result = duckdb::unique_ptr<TableMacroFunction>(new TableMacroFunction());
	deserializer.ReadPropertyWithDefault<unique_ptr<QueryNode>>(200, "query_node", result->query_node);
	return std::move(result);
}

} // namespace duckdb