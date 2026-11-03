# ESP32 Wi-Fi and Web Control Prototype

An ESP32 IoT prototype featuring Wi-Fi connectivity and a lightweight web-based control interface.

The repository also contains a separate HTML/CSS interface mockup.

## Project structure

```text
.
├── Project_1 iot/
│   ├── platformio.ini
│   └── src/
│       ├── main.cpp
│       └── secrets.h
└── Project_1 iot/MY_PROJECT/
    ├── index.html
    └── index.css
```

## Hardware and software

- ESP32 development board (PlatformIO environment: `esp32dev`)
- Arduino framework for ESP32
- PlatformIO Core or the PlatformIO IDE extension
- A Wi-Fi network for the board to connect to

## Firmware setup

The firmware expects Wi-Fi credentials in `Project_1 iot/src/secrets.h`, using the variable names `ssid` and `password`. This file is ignored by Git and is not included in the repository.

Create your local credentials file from the committed template:

```bash
cd "Project_1 iot/src"
cp secrets.example.h secrets.h
```

Edit the local `secrets.h` with your own Wi-Fi network name and password. Never commit that file. If credentials were previously committed publicly, change the Wi-Fi password because deleting the file from the latest version does not erase earlier Git history.

From the firmware project directory:

```bash
cd "Project_1 iot"
pio run
pio run --target upload
pio device monitor
```

The serial monitor is configured for 115200 baud.

## Current firmware behavior

The current firmware:

- Starts the ESP32 in Wi-Fi station mode.
- Connects using the credentials in `secrets.h`.
- Starts an HTTP server on port 80.
- Serves a web page at the root route (`/`).

The served page includes Wi-Fi scan and LED control buttons, but the corresponding `/scan` and `/led` server handlers are not yet implemented in the current firmware. Those controls should therefore be treated as an interface prototype, not as completed functionality.

## HTML/CSS mockup

The `Project_1 iot/MY_PROJECT/` directory contains a standalone HTML/CSS mockup for an ESP32 dashboard. It is separate from the page currently embedded in the firmware's `main.cpp`.

Open `index.html` in a browser to view the static mockup. Its buttons are visual elements and are not connected to the ESP32.

## Security note

Avoid publishing Wi-Fi passwords, API keys, or other credentials. If a real credential was committed, remove it from the tracked source and rotate it; adding a file to `.gitignore` alone does not remove it from Git history or undo exposure.
