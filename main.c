#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hidapi/hidapi.h"

// MK prefix stands for Magic Keyboard.
// Those VID/PID values come from inspecting connected devices info, and are
// very likely to be the same for everyone. Report data comes from inspecting
// packets sent by Magic Utilities using Wireshark HID protocol analyzer.
#define MK_BLUETOOTH_VID 0x004c
#define MK_PID 0x026c
#define MK_BATTERY_REPORT_ID 0xf0
#define MK_BATTERY_REPORT_SIZE 3
#define MK_BATTERY_REPORT_INDEX 2

int main(int argc, char *argv[]) {
  hid_device *handle;
  unsigned char
      buffer[MK_BATTERY_REPORT_SIZE + 1]; // 1 extra byte for report ID
  int result = {0};
  int battery_level = {0};

  printf("Magic Keyboard battery tool. Using HIDAPI runtime %s\n",
         hid_version_str());
  if (hid_init()) {
    printf("Couldn't open HIDAPI, aborted\n");
    return -1;
  }

  handle = hid_open(MK_BLUETOOTH_VID, MK_PID, NULL);
  if (!handle) {
    printf("Couldn't open Magic Keyboard. Please make sure it's connected via "
           "Bluetooth\n");
	hid_exit();
	return -2;
  }

  printf("\n");
  memset(buffer, 0x00, sizeof(buffer));
  buffer[0] = MK_BATTERY_REPORT_ID;
  result = hid_get_input_report(handle, buffer, sizeof(buffer));
  if (result < MK_BATTERY_REPORT_SIZE + 1) {
    printf("Unable to get battery level :(\n");
    printf("HID error: %ls\n", hid_error(handle));
  } else {
    battery_level = buffer[MK_BATTERY_REPORT_INDEX + 1];
    printf("Current battery level: %d%%\n", battery_level);
    printf("  |");
    int i;
    for (i = 0; i < battery_level; i += 5) {
      printf("=");
    }
    for (; i < 100; i += 5) {
      printf("-");
    }
    printf("|\n");
  }

  hid_close(handle);
  hid_exit();
  return 0;
}
