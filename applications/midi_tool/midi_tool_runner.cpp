#include "midi_tool_app.h"

extern "C" int32_t midi_tool_app(void* p)
{
  MidiToolApp* app = new MidiToolApp();
  int32_t result = app->run(p);
  delete app;

  return result;
}
