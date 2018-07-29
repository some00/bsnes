#include "../bsnes.hpp"
#include "platform.cpp"
#include "game.cpp"
#include "game-pak.cpp"
#include "game-rom.cpp"
#include "paths.cpp"
#include "states.cpp"
#include "video.cpp"
#include "audio.cpp"
#include "input.cpp"
#include "utility.cpp"
#include "patch.cpp"
#include "hacks.cpp"
unique_pointer<Program> program;

Program::Program(vector<string> arguments) {
  program = this;
  Emulator::platform = this;

  new Presentation;
  presentation->setVisible();

  new InputManager;
  new SettingsWindow;
  new CheatDatabase;
  new CheatWindow;
  new StateWindow;
  new ToolsWindow;
  new AboutWindow;

  if(settings["Crashed"].boolean()) {
    MessageDialog(
      "Driver crash detected. Hardware drivers have been disabled.\n"
      "Please reconfigure drivers in the advanced settings panel."
    ).setParent(*presentation).information();
    settings["Video/Driver"].setValue("None");
    settings["Audio/Driver"].setValue("None");
    settings["Input/Driver"].setValue("None");
  }

  settings["Crashed"].setValue(true);
  settings.save();
  updateVideoDriver(*presentation);
  updateAudioDriver(*presentation);
  updateInputDriver(*presentation);
  settings["Crashed"].setValue(false);
  settings.save();

  settingsWindow->drivers.videoDriverChanged();
  settingsWindow->drivers.audioDriverChanged();
  settingsWindow->drivers.inputDriverChanged();

  arguments.takeLeft();  //ignore program location in argument parsing
  for(auto& argument : arguments) {
    if(argument == "--fullscreen") {
      presentation->toggleFullscreenMode();
    } else if(inode::exists(argument)) {
      gameQueue.append(argument);
    }
  }

  if(gameQueue) load();
  Application::onMain({&Program::main, this});
}

auto Program::main() -> void {
  if(Application::modal()) return;

  updateStatus();
  video->poll();
  inputManager->poll();
  inputManager->pollHotkeys();

  if(paused()) {
    audio->clear();
    usleep(20 * 1000);
    return;
  }

  emulator->run();
  if(settingsWindow->configuration.autoSaveMemory.checked()) {
    auto currentTime = chrono::timestamp();
    if(currentTime - autoSaveTime >= settings["Emulator/AutoSaveMemory/Interval"].natural()) {
      autoSaveTime = currentTime;
      emulator->save();
    }
  }
}

auto Program::quit() -> void {
  unload();
  settings.save();
  video.reset();
  audio.reset();
  input.reset();
  Application::kill();
}