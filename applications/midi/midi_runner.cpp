#include "midi_app.h"

extern "C" int32_t midi_app(void* p)
{
  MidiApp* app = new MidiApp();
  int32_t result = app->run(p);
  delete app;

  return result;
}
