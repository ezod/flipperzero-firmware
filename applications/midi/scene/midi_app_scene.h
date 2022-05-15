#pragma once

#include "../midi_app_event.h"

class MidiApp;

/** Base scene class. */
class MidiAppScene
{
public:
  virtual ~MidiAppScene() = default;

  virtual void on_enter(MidiApp* app) = 0;
  virtual bool on_event(MidiApp* app, MidiAppEvent* event) = 0;
  virtual void on_exit(MidiApp* app) = 0;
};
