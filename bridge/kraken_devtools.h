/*
 * Copyright (C) 2020 Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */

#ifndef KRAKEN_DEVTOOLS_KRAKEN_DEVTOOLS_H
#define KRAKEN_DEVTOOLS_KRAKEN_DEVTOOLS_H

#include <cinttypes>
#include "kraken_bridge.h"
#include "inspector/protocol_handler.h"
#include <JavaScriptCore/JavaScript.h>
#include "dart_methods.h"

namespace kraken::debugger {

class BridgeProtocolHandler : public ProtocolHandler {
public:
  BridgeProtocolHandler() {};

  ~BridgeProtocolHandler() {};

  void handlePageReload() override;

private:
};
}

KRAKEN_EXPORT_C
void attachDebugger(int32_t contextId);

struct InspectorDartMethodPointer {
  InspectorMessage inspectorMessage{nullptr};
  RegisterInspectorMessageCallback registerInspectorMessageCallback{nullptr};
  PostTaskToUIThread postTaskToUiThread{nullptr};
};

std::shared_ptr<InspectorDartMethodPointer> getInspectorDartMethod();

void registerInspectorDartMethods(uint64_t *methodBytes, int32_t length);

#endif //KRAKEN_DEVTOOLS_KRAKEN_DEVTOOLS_H
