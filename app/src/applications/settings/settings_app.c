#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/settings/settings.h>

#include "settings_ui.h"
#include "ble/ble_aoa.h"
#include "ble/ble_comm.h"
#include "sensors/zsw_imu.h"
#include "drivers/zsw_display_control.h"
#include "managers/zsw_app_manager.h"
#include "zsw_settings.h"

static void settings_app_start(lv_obj_t *root, lv_group_t *group);
static void settings_app_stop(void);

static void on_close_settings(void);
static void on_brightness_changed(lv_setting_value_t value, bool final);
static void on_display_on_changed(lv_setting_value_t value, bool final);
static void on_display_vib_press_changed(lv_setting_value_t value, bool final);
static void on_aoa_enable_changed(lv_setting_value_t value, bool final);
static void on_aoa_interval_changed(lv_setting_value_t value, bool final);
static void on_pairing_enable_changed(lv_setting_value_t value, bool final);
static void on_reset_steps_changed(lv_setting_value_t value, bool final);
static void on_clear_bonded_changed(lv_setting_value_t value, bool final);

LV_IMG_DECLARE(settings);

typedef struct setting_app {
    zsw_settings_brightness_t           brightness;
    zsw_settings_vib_on_press_t         vibration_on_click;
    zsw_settings_display_always_on_t    display_always_on;
    zsw_settings_ble_aoa_en_t           ble_aoa_enabled;
    zsw_settings_ble_aoa_int_t          ble_aoa_tx_interval;
} setting_app_t;

// Default values.
static setting_app_t settings_app = {
    .brightness = 30,
    .vibration_on_click = true,
    .display_always_on = false,
    .ble_aoa_enabled = false,
    .ble_aoa_tx_interval = 100
};

static application_t app = {
    .name = "Settings",
    .icon = &settings,
    .start_func = settings_app_start,
    .stop_func = settings_app_stop
};

static lv_settings_item_t general_page_items[] = {
    {
        .type = LV_SETTINGS_TYPE_SLIDER,
        .icon = LV_SYMBOL_SETTINGS,
        .change_callback = on_brightness_changed,
        .item = {
            .slider = {
                .name = "Brightness",
                .inital_val = &settings_app.brightness,
                .min_val = 1,
                .max_val = 100,
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_AUDIO,
        .change_callback = on_display_vib_press_changed,
        .item = {
            .sw = {
                .name = "Vibrate on click",
                .inital_val = &settings_app.vibration_on_click,
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_TINT,
        .change_callback = on_display_on_changed,
        .item = {
            .sw = {
                .name = "Display always on",
                .inital_val = &settings_app.display_always_on
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_BTN,
        .icon = LV_SYMBOL_REFRESH,
        .change_callback = on_reset_steps_changed,
        .item = {
            .btn = {
                .name = "Reset step counter",
                .text = LV_SYMBOL_REFRESH
            }
        }
    },
};

static lv_settings_item_t bluetooth_page_items[] = {
    {
        .type = LV_SETTINGS_TYPE_BTN,
        .icon = LV_SYMBOL_BLUETOOTH,
        .change_callback = on_pairing_enable_changed,
        .item = {
            .btn = {
                .name = "Pairable",
                .text = "Enable"
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_BTN,
        .icon = LV_SYMBOL_BACKSPACE,
        .change_callback = on_clear_bonded_changed,
        .item = {
            .btn = {
                .name = "Delete all bonded peers",
                .text = LV_SYMBOL_TRASH
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = "",
        .change_callback = on_aoa_enable_changed,
        .item = {
            .sw = {
                .name = "AoA",
                .inital_val = &settings_app.ble_aoa_enabled
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SLIDER,
        .icon = LV_SYMBOL_SHUFFLE,
        .change_callback = on_aoa_interval_changed,
        .item = {
            .slider = {
                .name = "CTE Tx interval",
                .inital_val = &settings_app.ble_aoa_tx_interval,
                .min_val = 10,
                .max_val = 5000
            }
        }
    },
};

static lv_settings_page_t settings_menu[] = {
    {
        .name = "General",
        .num_items = ARRAY_SIZE(general_page_items),
        .items = general_page_items
    },
    {
        .name = "Bluetooth",
        .num_items = ARRAY_SIZE(bluetooth_page_items),
        .items = bluetooth_page_items
    },
};

static void settings_app_start(lv_obj_t *root, lv_group_t *group)
{
    lv_settings_create(settings_menu, ARRAY_SIZE(settings_menu), "N/A", group, on_close_settings);
}

static void settings_app_stop(void)
{
    settings_ui_remove();
}

static void on_close_settings(void)
{
    zsw_app_manager_app_close_request(&app);
}

static void on_brightness_changed(lv_setting_value_t value, bool final)
{
    settings_app.brightness = value.item.slider;
    zsw_display_control_set_brightness(settings_app.brightness);
    if (final) {
        settings_save_one(ZSW_SETTINGS_BRIGHTNESS, &settings_app.brightness, sizeof(settings_app.brightness));
    }
}

static void on_display_on_changed(lv_setting_value_t value, bool final)
{
    settings_app.display_always_on = value.item.sw;
    settings_save_one(ZSW_SETTINGS_DISPLAY_ALWAYS_ON, &settings_app.display_always_on,
                      sizeof(settings_app.display_always_on));
}

static void on_display_vib_press_changed(lv_setting_value_t value, bool final)
{
    settings_app.vibration_on_click = value.item.sw;
    settings_save_one(ZSW_SETTINGS_VIBRATE_ON_PRESS, &settings_app.vibration_on_click,
                      sizeof(settings_app.vibration_on_click));
}

static void on_aoa_enable_changed(lv_setting_value_t value, bool final)
{
    settings_app.ble_aoa_enabled = value.item.sw;
    bleAoaAdvertise(settings_app.ble_aoa_tx_interval, settings_app.ble_aoa_tx_interval, settings_app.ble_aoa_enabled);
    settings_save_one(ZSW_SETTINGS_BLE_AOA_EN, &settings_app.ble_aoa_enabled, sizeof(settings_app.ble_aoa_enabled));
}

static void on_aoa_interval_changed(lv_setting_value_t value, bool final)
{
    settings_app.ble_aoa_tx_interval = value.item.slider;
    if (final) {
        settings_save_one(ZSW_SETTINGS_BLE_AOA_INT, &settings_app.ble_aoa_tx_interval,
                          sizeof(settings_app.ble_aoa_tx_interval));
    }
}

static void on_pairing_enable_changed(lv_setting_value_t value, bool final)
{
    if (value.item.sw) {
        ble_comm_set_pairable(true);
    } else {
        ble_comm_set_pairable(false);
    }
}

static void on_clear_bonded_changed(lv_setting_value_t value, bool final)
{
    if (final) {
        int err = bt_unpair(BT_ID_DEFAULT, NULL);
        if (err) {
            printk("Cannot unpair for default ID");
            return;
        }
    }
}

static void on_reset_steps_changed(lv_setting_value_t value, bool final)
{
    if (final) {
        zsw_imu_reset_step_count();
    }
}

static int settings_load_cb(const char *name, size_t len,
                            settings_read_cb read_cb, void *cb_arg)
{
    const char *next;
    int rc;

    if (settings_name_steq(name, ZSW_SETTINGS_KEY_BRIGHTNESS, &next) && !next) {

        if (len != sizeof(settings_app.brightness)) {
            return -EINVAL;
        }

        rc = read_cb(cb_arg, &settings_app.brightness, sizeof(settings_app.brightness));
        zsw_display_control_set_brightness(settings_app.brightness);
        if (rc >= 0) {
            return 0;
        }
        return rc;
    }
    if (settings_name_steq(name, ZSW_SETTINGS_KEY_VIBRATION_ON_PRESS, &next) && !next) {
        if (len != sizeof(settings_app.vibration_on_click)) {
            return -EINVAL;
        }

        rc = read_cb(cb_arg, &settings_app.vibration_on_click, sizeof(settings_app.vibration_on_click));
        settings_app.vibration_on_click = settings_app.vibration_on_click;
        if (rc >= 0) {
            return 0;
        }
        return rc;
    }
    if (settings_name_steq(name, ZSW_SETTINGS_KEY_DISPLAY_ALWAYS_ON, &next) && !next) {
        if (len != sizeof(settings_app.display_always_on)) {
            return -EINVAL;
        }

        rc = read_cb(cb_arg, &settings_app.display_always_on, sizeof(settings_app.display_always_on));
        settings_app.display_always_on = settings_app.display_always_on;
        if (rc >= 0) {
            return 0;
        }
        return rc;
    }
    if (settings_name_steq(name, ZSW_SETTINGS_KEY_BLE_AOA_EN, &next) && !next) {
        if (len != sizeof(settings_app.ble_aoa_enabled)) {
            return -EINVAL;
        }

        rc = read_cb(cb_arg, &settings_app.ble_aoa_enabled, sizeof(settings_app.ble_aoa_enabled));
        settings_app.ble_aoa_enabled = settings_app.ble_aoa_enabled;
        if (rc >= 0) {
            return 0;
        }
        return rc;
    }
    if (settings_name_steq(name, ZSW_SETTINGS_KEY_BLE_AOA_INT, &next) && !next) {
        if (len != sizeof(settings_app.ble_aoa_tx_interval)) {
            return -EINVAL;
        }

        rc = read_cb(cb_arg, &settings_app.ble_aoa_tx_interval, sizeof(settings_app.ble_aoa_tx_interval));
        settings_app.ble_aoa_tx_interval = settings_app.ble_aoa_tx_interval;
        if (rc >= 0) {
            return 0;
        }
        return rc;
    }

    return -ENOENT;
}

static int settings_app_add(void)
{
    zsw_app_manager_add_application(&app);
    memset(&settings_app, 0, sizeof(settings_app));

    return 0;
}

SETTINGS_STATIC_HANDLER_DEFINE(settings_app_handler, ZSW_SETTINGS_PATH, NULL,
                               settings_load_cb, NULL, NULL);

SYS_INIT(settings_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
