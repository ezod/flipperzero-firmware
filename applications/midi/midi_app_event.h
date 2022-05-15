#pragma once

#include <gui/modules/dialog_ex.h>

/** MIDI app event class. */
class MidiAppEvent 
{
public:
  enum class Type : uint8_t
  {
    Tick,
    Exit,
    Back,
    MenuSelected,
    MenuSelectedPress,
    MenuSelectedRelease,
    DialogExSelected,
    InfraredMessageReceived,
    TextEditDone,
    PopupTimer,
    ButtonPanelPressed,
  };

  union
  {
    int32_t dummy;
    int32_t menu_index;
    DialogExResult dialog_ex_result;
  } payload;

  Type type;  ///< Event type.
};
