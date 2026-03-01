#include "ble_listener.h"
#include "protocol.h"
#include <bt/bt_service/bt.h>
#include <profiles/serial_profile.h>
#include <services/serial_service.h>
#include <furi_hal_bt.h>
#include <furi.h>
#include <rpc/rpc.h>

static FuriHalBleProfileBase* ble_profile = NULL;
static Bt* bt_system = NULL;
static void* app_gui_manager = NULL;
static FuriTimer* timer = NULL;
static RpcSession* rpc_session_blocker = NULL;

#include <furi_hal_vibro.h>
#include "gui_manager.h"

static uint16_t BleSerialCallback(SerialServiceEvent event, void* context) {
  if (event.event == SerialServiceEventTypeDataReceived) {
    if (app_gui_manager != NULL) {
        // We found that raw bytes work best in this mode
        GuiManagerHandleBleData(app_gui_manager, event.data.buffer, event.data.size);
    }
  }
  UNUSED(context);
  // Returning the full buffer size signals to the radio that we are ready for more data
  return 512; 
}

// Aggressively re-register the callback to prevent the system from stealing it
static void TimerCallback(void* context) {
    if (ble_profile != NULL) {
        ble_profile_serial_set_event_callback(ble_profile, 512, BleSerialCallback, NULL);
    }
    UNUSED(context);
}

int FlipperBleListenerStart(void* gui_manager) {
  if (ble_profile != NULL) return 0;
  
  app_gui_manager = gui_manager;
  
  // 1. Lock out the system RPC
  Rpc* rpc = furi_record_open(RECORD_RPC);
  rpc_session_blocker = rpc_session_open(rpc, RpcOwnerBle);
  
  bt_system = furi_record_open(RECORD_BT);
  bt_disconnect(bt_system);
  furi_delay_ms(500);

  // 2. Start the profile
  ble_profile = bt_profile_start(bt_system, ble_profile_serial, NULL);
  if (ble_profile == NULL) {
      if (rpc_session_blocker) rpc_session_close(rpc_session_blocker);
      furi_record_close(RECORD_RPC);
      furi_record_close(RECORD_BT);
      return -1;
  }
  
  furi_delay_ms(1500);
  
  // 3. Register the callback and disable RPC parsing
  ble_profile_serial_set_event_callback(ble_profile, 512, BleSerialCallback, NULL);
  ble_profile_serial_notify_buffer_is_empty(ble_profile);
  ble_profile_serial_set_rpc_active(ble_profile, false);
  
  furi_hal_bt_start_advertising();
  
  // 4. Start the "Aggressive Re-registration" timer
  timer = furi_timer_alloc(TimerCallback, FuriTimerTypePeriodic, NULL);
  furi_timer_start(timer, furi_ms_to_ticks(500));
  
  // DOUBLE VIBRATION = BLE READY
  furi_hal_vibro_on(true);
  furi_delay_ms(50);
  furi_hal_vibro_on(false);
  furi_delay_ms(100);
  furi_hal_vibro_on(true);
  furi_delay_ms(50);
  furi_hal_vibro_on(false);
  
  return 0;
}

int FlipperBleListenerStop(void) {
  if (timer) {
      furi_timer_stop(timer);
      furi_timer_free(timer);
      timer = NULL;
  }
  if (ble_profile == NULL) return 0;
  
  bt_profile_restore_default(bt_system);
  furi_record_close(RECORD_BT);
  
  if (rpc_session_blocker) {
      rpc_session_close(rpc_session_blocker);
      rpc_session_blocker = NULL;
  }
  furi_record_close(RECORD_RPC);
  
  ble_profile = NULL;
  bt_system = NULL;
  app_gui_manager = NULL;
  
  return 0;
}

int FlipperBleDispatchPacket(const uint8_t* data, size_t length) {
  return FlipperProtocolParse(data, length);
}
