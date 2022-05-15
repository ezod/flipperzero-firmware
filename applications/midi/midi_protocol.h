#pragma once

#define MIDI_BAUDRATE             31250

// MIDI channel commands
#define MIDI_CMD_NOTE_OFF         0x80
#define MIDI_CMD_NOTE_ON          0x90
#define MIDI_CMD_AFTERTOUCH       0xA0
#define MIDI_CMD_CC               0xB0
#define MIDI_CMD_PC               0xC0
#define MIDI_CMD_PRESSURE         0xD0
#define MIDI_CMD_PITCH_BEND       0xE0

// MIDI system messages
#define MIDI_SYS_SE_START         0xF0
#define MIDI_SYS_SE_END           0xF7
#define MIDI_SYS_TC_QF            0xF1
#define MIDI_SYS_SONG_PP          0xF2
#define MIDI_SYS_SONG_SEL         0xF3
#define MIDI_SYS_TUNE_REQ         0xF6
#define MIDI_SYS_CLOCK            0xF8
#define MIDI_SYS_START            0xFA
#define MIDI_SYS_CONTINUE         0xFB
#define MIDI_SYS_STOP             0xFC
#define MIDI_SYS_ACT_SENSING      0xFE
#define MIDI_SYS_RESET            0xFF
