#include "ble_listener.h"
#include "protocol.h"
#include <bt/bt_service/bt.h>
#include <profiles/serial_profile.h>
#include <services/serial_service.h>
#include <services/battery_service.h>
#include <furi_hal_bt.h>
#include <furi_hal_power.h>
#include <furi_hal_version.h>
#include <furi.h>
#include <rpc/rpc.h>

static FuriHalBleProfileBase* ble_profile = NULL;
static Bt* bt_system = NULL;
void* app_gui_manager = NULL;
static FuriTimer* timer = NULL;
static Rpc* rpc_system = NULL;
static RpcSession* rpc_session_blocker = NULL;
static BleServiceBattery* battery_svc = NULL;

#include <furi_hal_vibro.h>
#include "gui_manager.h"

// --- MOMENTUM OPTIMIZED V2 ---

static FuriHalBleProfileBase* ble_profile_serial_momentum_start(FuriHalBleProfileParams profile_params) {
    return ble_profile_serial->start(profile_params);
}

static void ble_profile_serial_momentum_stop(FuriHalBleProfileBase* profile) {
    ble_profile_serial->stop(profile);
}

static void ble_profile_serial_momentum_get_config(GapConfig* config, FuriHalBleProfileParams profile_params) {
    // 1. Get standard NUS (Nordic UART Service) config
    ble_profile_serial->get_gap_config(config, profile_params);
    
    // 2. Override Name with HID_ prefix (Safely)
    // We preserve the first byte which is the BLE AD Type (0x09 for Local Name)
    uint8_t ad_type = config->adv_name[0];
    char custom_name[FURI_HAL_VERSION_DEVICE_NAME_LENGTH];
    snprintf(custom_name, sizeof(custom_name), "HID_%s", furi_hal_version_get_name_ptr());
    strlcpy(config->adv_name + 1, custom_name, sizeof(config->adv_name) - 1);
    config->adv_name[0] = ad_type;
}

static const FuriHalBleProfileTemplate profile_momentum_callbacks = {
    .start = ble_profile_serial_momentum_start,
    .stop = ble_profile_serial_momentum_stop,
    .get_gap_config = ble_profile_serial_momentum_get_config,
};

static const FuriHalBleProfileTemplate* ble_profile_momentum = &profile_momentum_callbacks;

static uint16_t BleSerialCallback(SerialServiceEvent event, void* context) {
  if (event.event == SerialServiceEventTypeDataReceived) {
    if (app_gui_manager != NULL) {
        GuiManagerHandleBleData(app_gui_manager, event.data.buffer, event.data.size);
    }
  }
  UNUSED(context);
  return 512; 
}

static void TimerCallback(void* context) {
    if (ble_profile != NULL) {
        ble_profile_serial_set_event_callback(ble_profile, 512, BleSerialCallback, NULL);
    }
    UNUSED(context);
}

int FlipperBleListenerStart(void* gui_manager) {
  if (ble_profile != NULL) return 0;
  app_gui_manager = gui_manager;
  
  rpc_system = furi_record_open(RECORD_RPC);
  rpc_session_blocker = rpc_session_open(rpc_system, RpcOwnerBle);
  
  bt_system = furi_record_open(RECORD_BT);
  bt_disconnect(bt_system);
  furi_delay_ms(500);

  ble_profile = bt_profile_start(bt_system, ble_profile_momentum, NULL);
  if (ble_profile == NULL) {
      if (rpc_session_blocker) rpc_session_close(rpc_session_blocker);
      furi_record_close(RECORD_RPC);
      furi_record_close(RECORD_BT);
      return -1;
  }
  
  furi_delay_ms(1000);
  
  battery_svc = ble_svc_battery_start(true);
  uint8_t level = furi_hal_power_get_pct();
  ble_svc_battery_update_level(battery_svc, level);
  
  ble_profile_serial_set_event_callback(ble_profile, 512, BleSerialCallback, NULL);
  ble_profile_serial_notify_buffer_is_empty(ble_profile);
  ble_profile_serial_set_rpc_active(ble_profile, false);
  
  furi_hal_bt_start_advertising();
  
  timer = furi_timer_alloc(TimerCallback, FuriTimerTypePeriodic, NULL);
  furi_timer_start(timer, furi_ms_to_ticks(500));
  
  furi_hal_vibro_on(true); furi_delay_ms(50); furi_hal_vibro_on(false);
  return 0;
}

int FlipperBleListenerStop(void) {
  if (timer) { furi_timer_stop(timer); furi_timer_free(timer); timer = NULL; }
  if (battery_svc) {
      ble_svc_battery_stop(battery_svc);
      battery_svc = NULL;
  }
  if (ble_profile == NULL) return 0;
  bt_profile_restore_default(bt_system);
  furi_record_close(RECORD_BT);
  if (rpc_session_blocker) { rpc_session_close(rpc_session_blocker); rpc_session_blocker = NULL; }
  furi_record_close(RECORD_RPC);
  ble_profile = NULL;
  return 0;
}

void FlipperBleNotifyEmpty(void) {
  if (ble_profile != NULL) {
      ble_profile_serial_notify_buffer_is_empty(ble_profile);
  }
}

bool FlipperBleIsBatteryServiceActive(void) {
    return battery_svc != NULL;
}

int FlipperBleDispatchPacket(const uint8_t* data, size_t length) {
  return FlipperProtocolParse(data, length);
}
