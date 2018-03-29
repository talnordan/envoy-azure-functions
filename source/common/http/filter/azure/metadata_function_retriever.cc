#include "common/http/filter/azure/metadata_function_retriever.h"

#include "common/common/macros.h"
#include "common/config/azure_functions_well_known_names.h"
#include "common/config/solo_metadata.h"

namespace Envoy {
namespace Http {
namespace Azure {

using Config::SoloMetadata;

Optional<Function> MetadataFunctionRetriever::getFunction(
    const MetadataAccessor &metadataccessor) const {

  Optional<const ProtobufWkt::Struct *> maybe_function_spec =
      metadataccessor.getFunctionSpec();
  if (!maybe_function_spec.valid()) {
    return {};
  }

  const ProtobufWkt::Struct &function_spec = *maybe_function_spec.value();

  Optional<const std::string *> host = SoloMetadata::nonEmptyStringValue(
      function_spec, Config::AzureFunctionsMetadataKeys::get().HOST);
  Optional<const std::string *> path = SoloMetadata::nonEmptyStringValue(
      function_spec, Config::AzureFunctionsMetadataKeys::get().PATH);

  return Function::createFunction(host, path);
}

} // namespace Azure
} // namespace Http
} // namespace Envoy
