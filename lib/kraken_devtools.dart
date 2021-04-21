
import 'dart:async';

import 'package:flutter/services.dart';

class KrakenDevtools {
  static const MethodChannel _channel =
      const MethodChannel('kraken_devtools');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
}
