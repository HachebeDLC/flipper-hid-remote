#include "settings.h"
#include <storage/storage.h>
#include <furi.h>

void FlipperKbConfigLoad(FlipperKbConfig* config) {
    furi_assert(config);
    
    // Default values
    strncpy(config->layout_path, "default", sizeof(config->layout_path));
    config->vibro_enabled = true;

    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    if (storage_file_open(file, FLIPPER_KB_CONFIG_PATH, FSAM_READ, FSOM_OPEN_EXISTING)) {
        storage_file_read(file, config, sizeof(FlipperKbConfig));
    }

    storage_file_close(file);
    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
}

void FlipperKbConfigSave(FlipperKbConfig* config) {
    furi_assert(config);

    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    if (storage_file_open(file, FLIPPER_KB_CONFIG_PATH, FSAM_WRITE, FSOM_CREATE_ALWAYS)) {
        storage_file_write(file, config, sizeof(FlipperKbConfig));
    }

    storage_file_close(file);
    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
}
