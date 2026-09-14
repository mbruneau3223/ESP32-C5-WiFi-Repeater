# ESP32-C5 WiFi Repeater

ESP32-C5 transparent WiFi repeater with L2 bridging, Web UI, OTA updates, client blocking, and mDNS management.

## Features

- Transparent Layer-2 WiFi repeater
- Same subnet as the upstream router
- Web-based configuration
- OTA firmware updates
- Client blocking
- DHCP reservation support
- mDNS management
- Addressable LED status indication
- ESP32-C5 support
- Waveshare ESP32-C5-Zero support
- External antenna selection on GPIO26
- WS2812 status LED on GPIO27

## Management Address

A freshly installed repeater is available at:

`http://esp32-repeater.local/`

If using multiple repeaters, rename the current repeater before installing another.

For example:

- `esp32-repeater1.local`
- `esp32-repeater2.local`
- `esp32-repeater3.local`

Before installing the next repeater, change the Hostname under **Configuration → Access Point Settings**, then click **Save & Reboot**.

The next freshly installed repeater will again use:

`http://esp32-repeater.local/`

## First Setup

Fresh installations create the setup WiFi network:

`ESP32-Repeater-Setup`

The setup network has no password by default.

The Web UI also has no password on first setup. A Web UI password can be configured after installation.

Once configured, the repeater can normally be managed at:

`http://esp32-repeater.local/`

## LED Status

The onboard WS2812 status LED indicates the current state:

- Breathing red — not connected to the upstream access point
- Breathing green — connected to the upstream access point
- Alternating red/blue — factory reset in progress

On the Waveshare ESP32-C5-Zero, the onboard WS2812 uses GPIO27.

## External Antenna

For the Waveshare ESP32-C5-Zero, GPIO26 is used to select the external IPEX/u.FL antenna.

The firmware automatically sets GPIO26 HIGH during startup to select the external antenna.

## OTA Updates

Firmware can be updated over WiFi from the Web UI.

Open the **Configuration** page and locate **Firmware Update (OTA)**.

For an OTA update, upload only:

`esp32_nat_router.bin`

Do not upload `bootloader.bin`, `partition-table.bin`, or `ota_data_initial.bin` through the OTA firmware update page.

## Building

This project is built using Espressif ESP-IDF.

The current development version uses:

- ESP-IDF 5.5.5
- Target: ESP32-C5
- Flash size: 4 MB

Build with:

```powershell
idf.py build
```

Flash over USB with:

```powershell
idf.py -p COM6 flash
```

Replace `COM6` with the appropriate serial port for your system.

## Flash Layout

The current ESP32-C5 build uses:

| Offset | Image |
|---|---|
| `0x2000` | `bootloader.bin` |
| `0x8000` | `partition-table.bin` |
| `0xF000` | `ota_data_initial.bin` |
| `0x20000` | `esp32_nat_router.bin` |

These images can also be used with ESP Web Tools for initial installation.

## Upstream Project / Credits

This project is based on Martin Ger's `esp32_nat_router` project, specifically the `esp32_wifi_repeater` branch.

Original project:

https://github.com/martin-ger/esp32_nat_router

This fork adds and modifies functionality for the ESP32-C5, including:

- Waveshare ESP32-C5-Zero support
- External antenna selection
- WS2812 status indication
- Web UI improvements
- Client blocking
- OTA firmware management
- mDNS management
- Simplified repeater setup
- ESP32-C5-specific compatibility changes

Many thanks to Martin Ger and the original project contributors for their work.

## Disclaimer

This project is provided without warranty. Review the source code and configuration for suitability before deploying it in your network.