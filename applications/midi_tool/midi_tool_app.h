#pragma once

#include <furi.h>

/** Main MIDI Tool application class. */
class MidiToolApp {
public:

	/** Run application.
	 * 
	 * @param args Application arguments.
	 * @return 0 on success, error code otherwise.
	 */
  int32_t run(void* args);
};
