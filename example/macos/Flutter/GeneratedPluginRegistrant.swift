//
//  Generated file. Do not edit.
//

import FlutterMacOS
import Foundation

import connectivity_macos
import path_provider_macos
import shared_preferences_macos
import jsc
import kraken
import kraken_devtools

func RegisterGeneratedPlugins(registry: FlutterPluginRegistry) {
  ConnectivityPlugin.register(with: registry.registrar(forPlugin: "ConnectivityPlugin"))
  PathProviderPlugin.register(with: registry.registrar(forPlugin: "PathProviderPlugin"))
  SharedPreferencesPlugin.register(with: registry.registrar(forPlugin: "SharedPreferencesPlugin"))
  JscPlugin.register(with: registry.registrar(forPlugin: "JscPlugin"))
  KrakenPlugin.register(with: registry.registrar(forPlugin: "KrakenPlugin"))
  KrakenDevtoolsPlugin.register(with: registry.registrar(forPlugin: "KrakenDevtoolsPlugin"))
}
