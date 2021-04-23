/*
 * Copyright (C) 2020 Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */

#include "kraken_devtools.h"
#include "kraken_bridge.h"
#include "inspector/frontdoor.h"
#include "inspector/protocol_handler.h"
#include <memory>

void attachDebugger(int32_t contextId) {
  JSGlobalContextRef ctx = getGlobalContextRef(contextId);
  std::shared_ptr<kraken::debugger::BridgeProtocolHandler> handler = std::make_shared<kraken::debugger::BridgeProtocolHandler>();
  JSC::ExecState* exec = toJS(ctx);
  JSC::VM& vm = exec->vm();
  JSC::JSLockHolder locker(vm);
  JSC::JSGlobalObject* globalObject = vm.vmEntryGlobalObject(exec);
  kraken::debugger::FrontDoor *frontDoor = new kraken::debugger::FrontDoor(contextId, ctx, globalObject->globalObject(), handler);
  registerContextDisposedCallbacks(contextId, [](void *ptr) {
    delete reinterpret_cast<kraken::debugger::FrontDoor *>(ptr);
  }, frontDoor);
}

std::shared_ptr<InspectorDartMethodPointer> inspectorMethodPointer = std::make_shared<InspectorDartMethodPointer>();
std::shared_ptr<InspectorDartMethodPointer> getInspectorDartMethod() {
  assert_m(std::this_thread::get_id() != getUIThreadId(), "inspector dart methods should be called on the inspector thread.");
  return inspectorMethodPointer;
}

void registerInspectorDartMethods(uint64_t *methodBytes, int32_t length) {
  size_t i = 0;
  inspectorMethodPointer->inspectorMessage = reinterpret_cast<InspectorMessage>(methodBytes[i++]);
  inspectorMethodPointer->registerInspectorMessageCallback = reinterpret_cast<RegisterInspectorMessageCallback>(methodBytes[i++]);
  inspectorMethodPointer->postTaskToUiThread = reinterpret_cast<PostTaskToUIThread>(methodBytes[i++]);
}

namespace kraken::debugger {

void BridgeProtocolHandler::handlePageReload() {
  // FIXME: reload with devtolls are not full working yet (debugger not working).
  // getDartMethod()->flushUICommand();
  // getDartMethod()->reloadApp(m_bridge->contextId);
}

}
