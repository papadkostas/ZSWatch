/*
 * This file is part of ZSWatch project <https://github.com/jakkra/ZSWatch/>.
 * Copyright (c) 2023 Jakob Krantz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <zephyr/types.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#define ADAFRUIT_SERVICE_TEMPERATURE    BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0100, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_TEMPERATURE       BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0101, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_ACCEL          BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0200, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_ACCEL             BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0201, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_LIGHT          BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0300, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_LIGHT             BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0301, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_GYRO           BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0400, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_GYRO              BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0401, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_MAG            BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0500, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_MAG               BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0501, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_BTN            BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0600, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_HUMIDITY       BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0700, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_HUMIDITY          BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0701, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_PRESSURE       BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0800, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_PRESSURE          BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0801, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_TONE           BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0C00, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_SERVICE_3D             BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0D00, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))
#define ADAFRUIT_CHAR_PRESSURE          BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0D01, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define ADAFRUIT_MEASUREMENT_PERIOD_ID  BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0xADAF0001, 0xC332, 0x42A8, 0x93BD, 0x25E905756CB8))

#define BLE_UUID_TRANSPORT_VAL \
    BT_UUID_128_ENCODE(0x6e400001, 0xb5a3, 0xf393, 0xe0a9, 0xe50e24dcca9e)
