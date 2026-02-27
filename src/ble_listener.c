#include "ble_listener.h"
#include "protocol.h"
#include <furi_hal_bt.h>
#include <profiles/serial_profile.h>
#include <services/serial_service.h>
#include <furi.h>

static FuriHalBleProfileBase* ble_profile = NULL;

static uint16_t BleSerialCallback(SerialServiceEvent event, void* context) {
  if (event.event == SerialServiceEventTypeDataReceived) {
    FlipperBleDispatchPacket(event.data.buffer, event.data.size);
  }
  UNUSED(context);
  return 0;
}

int FlipperBleListenerStart(void) {
  if (ble_profile != NULL) return 0;
  
  ble_profile = furi_hal_bt_start_app(ble_profile_serial, NULL, NULL, NULL, NULL);
  if (ble_profile == NULL) return -1;
  
  ble_profile_serial_set_event_callback(ble_profile, 512, BleSerialCallback, NULL);
  
  return 0;
}

int FlipperBleListenerStop(void) {
  if (ble_profile == NULL) return 0;
  
  // Stopping the app is usually done via changing the app back to default
  FuriHalBleProfileBase* result = furi_hal_bt_change_app(NULL, NULL, NULL, NULL, NULL);
  UNUSED(result);
  ble_profile = NULL;
  
  return 0;
}

int FlipperBleDispatchPacket(const uint8_t* data, size_t length) {
  // Dispatched from callback
  return FlipperProtocolParse(data, length);
}
