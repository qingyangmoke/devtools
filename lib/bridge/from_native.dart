import 'dart:ffi';
import 'dart:typed_data';

import 'package:ffi/ffi.dart';
import 'package:kraken/launcher.dart';
import 'platform.dart';
import 'package:kraken_devtools/inspector/ui_inspector.dart';

typedef Native_PostTaskToInspectorThread = Void Function(Int32 contextId, Pointer<Void> context, Pointer<Void> callback);
typedef Dart_PostTaskToInspectorThread = void Function(int contextId, Pointer<Void> context, Pointer<Void> callback);

void _postTaskToInspectorThread(int contextId, Pointer<Void> context, Pointer<Void> callback) {
  KrakenController controller = KrakenController.getControllerOfJSContextId(contextId);
  if (controller.view.uiInspector != null) {
    controller.view.uiInspector.viewController.isolateServerPort.send(InspectorPostTaskMessage(context.address, callback.address));
  }
}

final Pointer<NativeFunction<Native_PostTaskToInspectorThread>> _nativePostTaskToInspectorThread = Pointer.fromFunction(_postTaskToInspectorThread);

final List<int> _dartNativeMethods = [
  _nativePostTaskToInspectorThread.address
];

typedef Native_RegisterDartMethods = Void Function(Pointer<Uint64> methodBytes, Int32 length);
typedef Dart_RegisterDartMethods = void Function(Pointer<Uint64> methodBytes, int length);

final Dart_RegisterDartMethods _registerDartMethods =
    nativeDynamicLibrary.lookup<NativeFunction<Native_RegisterDartMethods>>('registerDartMethods').asFunction();

void registerDartMethodsToCpp() {
  Pointer<Uint64> bytes = allocate<Uint64>(count: _dartNativeMethods.length);
  Uint64List nativeMethodList = bytes.asTypedList(_dartNativeMethods.length);
  nativeMethodList.setAll(0, _dartNativeMethods);
  _registerDartMethods(bytes, _dartNativeMethods.length);
}
