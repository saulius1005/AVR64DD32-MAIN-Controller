# SunFlower Dual Motor Controller for Solar Tracking System (AVR64DD32-MAIN-Controller)


![IMG_20251014_100444_282](https://github.com/user-attachments/assets/acdc728d-2162-4942-aba2-b8eaf4ced532)


---

## Overview

**Purpose:**  
This controller is designed to operate **two motors**:  
- **Azimuth motor** (stepper motor)  
- **Elevation motor** (linear motor)

---

## Hardware Description

The controller consists of the following main components:

- **AVR64DD32** — Main MCU operating at **24 MHz** (external TCXO).  
  Responsible for:
  - Processing **RS485** data  
  - Controlling the **LCD display**  
  - Reading input from an **analog joystick**  
  - Controlling motor drivers:
    - **CL86T v4.1** (external) — for *Azimuth motor*
    - **TLE9201SG** (on-board) — for *Elevation motor*
- **AMC1311** — Optically isolated op-amp used for motor voltage sensing  
- **TMCS1100A4** — Isolated Hall-effect DC current sensor  
- **ST485** — RS485 transceiver  

All control signals in the controller are **optically isolated** using  
`ADUM1201ARZ` and `CA-IS7320`, **except**:
- Azimuth motor signals (already isolated within CL86T)  
- If a wired UART data connection is used between the Top Controller and ATtiny212 
- Azimuth end switch inputs  

---

## Secondary Microcontroller (ATtiny212)

- Operates at **20 MHz** (external TCXO)  
- Receives data via:
  - **Fiber optic link**, or  
  - **UART cable** from *Top Controller* (sensor data, elevation end-switches, solar panel parameters)
- **Azimuth end switches** are directly connected through an intermediate connector.

---

## Operation Modes

The controller has **two operating modes**:

### Automatic Mode

![IMG_20251014_100137_100](https://github.com/user-attachments/assets/511e07b7-4b6d-4c8b-a507-60490bcd621d)


In this mode, the controller:
- Receives data from a **Weather Station** (via RS485):
  
```
{AAAABBBBCCCCDDEFFFGG}
```
**Where:**

* **AAAA** – Azimuth angle

* **BBBB** – Elevation angle

* **CCCC** – Day Top Elevation angle

* **DD** – Wind speed

* **E** – Wind direction

* **FFF** – Light Level

* **GG** – CRC-8 value

Also receives data from the **Top Controller** (via UART):

```
<EEEEAAAAVVVCCCYXX>
```
**Where:**

* **EEEE** – Elevation angle

* **AAAA** – Azimuth angle

* **VVV** – Voltage

* **CCC** – Current

* **Y** – End switch state

* **XX** – CRC-8 checksum


### Functionality in Automatic Mode

In **Automatic Mode**, the controller performs the following operations:

1. **Receives and processes data** from:
   - The **Weather Station** via RS485
   - The **Top Controller** via wired UART or fiber optic link

2. **Controls both motors** (Azimuth and Elevation) according to the received data.

3. **Monitors system conditions** and performs safety actions when necessary.

---

#### Error Detection and Display

The controller includes an **error handling system** that detects communication faults and data integrity issues.  
Detected errors are shown on the **LCD main screen** using short codes:

| Code | Meaning |
|------|----------|
| **LCE** | *Lost Connection Error* — Communication lost |
| **CRC** | *CRC Error* — Invalid data checksum, data ignored |
| **FOE** | *Fiber Optic Error* — UART link lost, but ATtiny212 remains operational |

> **Note:** All errors are displayed on the main LCD screen and are ignored only when the controller is in **Manual Mode**.

---

#### Viewing Motor and PV Parameters

![IMG_20251014_100156_181](https://github.com/user-attachments/assets/43034485-4481-49cf-8f70-71e0e94e0c6c)


By moving the **joystick down**, the user can open a **secondary display window** that shows:
- Azimuth and Elevation motor voltage and current  
- Photovoltaic (PV) system electrical parameters  

This allows monitoring of system performance in real time.

---

#### Automatic Weather Response

The controller reacts automatically to **extreme weather conditions** received from the weather station:

- **Strong Wind:**  
  Rotates the solar panels **parallel to the wind direction** and adjusts the **elevation** to a **vertical position** for protection.

- **Low Light Level:**  
  Automatically **stops both motors** to prevent unnecessary movement.

---

#### Summary of Automatic Mode Behavior

| Condition | Controller Action |
|------------|------------------|
| Normal operation | Track sun position (azimuth & elevation) |
| Strong wind | Rotate panels parallel to wind direction, elevate vertically |
| Low illumination | Stop motor activity |
| Lost communication | Display LCE error, stop movement |
| CRC mismatch | Ignore corrupted data, display CRC error |
| Fiber optic/wired UART link lost | Stop motor activity |
| RS485 link lost | Display LCE error, stop movement |

---

> ⚙️ *Automatic Mode ensures full autonomous operation and protection of the solar tracking system based on live meteorological data.*

---

### Manual Mode

![IMG_20251014_100216_279](https://github.com/user-attachments/assets/17e5e30d-ca14-4970-868d-a31da7688840)


In **Manual Mode**, the controller allows **direct user control** of both motors.  
This mode is designed for testing, calibration, and maintenance purposes.

**Key features:**
- Ignores all communication and CRC errors  
- Allows manual operation of Azimuth and Elevation motors via the joystick  
- Displays real-time electrical parameters of both motors instead of error messages  

**Activation:**
- Press the **joystick button** (neutral position) to toggle between *Automatic* and *Manual* modes.  
- The current mode is indicated on the **LCD display**.

> **Warning:** In Manual Mode, safety checks are disabled.  
> Ensure that the system is operated under safe conditions.

---

### Displayed Data

The LCD screen provides **real-time operational data** in both modes.

| Displayed Value | Description |
|------------------|-------------|
| **Target Azimuth / Elevation** | Calculated angles from Weather Station data |
| **Current Azimuth / Elevation** | Measured angles from position sensors |
| **Voltage / Current** | Electrical parameters of both motors and PV system |
| **Error Codes** | Displayed only in Automatic Mode when a fault occurs |

By navigating the joystick:
- **Up/Down:** switch between main and secondary display screens  (Automatic mode only)
- **Center press:** toggle between modes (Manual / Automatic)

---

### Notes

 **Development Status:**  
> This system is **currently in testing** and the firmware is being actively developed.  
> The hardware layout and optical interface may still be adjusted based on field results.

**Current observations:**
- The system operates correctly with **PMMA 4 mm optical fiber**.  
- **ABS plastic components** (optocoupler and photodiode adapters) are **too sensitive** to ambient light.  
- The current PCB design is optimized for **photodiode photovoltaic mode**, which increases light sensitivity.

---

### Summary

**System Features:**
- Dual motor control: *Azimuth* (stepper) + *Elevation* (linear)
- Communication interfaces: **RS485**, **UART**, and **Fiber Optic**
- Optically isolated signals for maximum noise immunity
- Integrated fault detection and real-time status display
- Automatic protection logic for strong wind and low light
- Manual override mode for maintenance and testing
- LCD user interface with live telemetry

---

### Components List

| Component | Function | Notes |
|------------|-----------|--------|
| **AVR64DD32** | Main MCU | 24 MHz (external TCXO) |
| **ATtiny212** | Secondary MCU | 20 MHz (external TCXO) |
| **CL86T v4.1** | Stepper Motor Driver | Controls Azimuth motor |
| **TLE9201SG** | Linear Motor Driver | Mounted on PCB, controls Elevation motor |
| **AMC1311** | Voltage Sensor | Optically isolated amplifier |
| **TMCS1100A4** | Current Sensor | Isolated Hall-effect current measurement |
| **ST485** | Transceiver | RS485 communication interface |
| **ADUM1201ARZ / CA-IS7320** | Isolators | Signal isolation between MCU and peripherals |

---

### Development Status

**Work In Progress**

| Aspect | Status | Notes |
|---------|---------|--------|
| Hardware | Stable | PCB tested and functional |
| Firmware | In development | Functionality improving |
| Communication | Stable | RS485 & UART verified |
| Optical link | Under testing | Sensitivity issues due to ambient light |
| UI / LCD | Working | Displays live data and errors |

> The firmware is currently in *testing stage (v1.0)*.  
> Updates and refinements are planned for improved stability and environmental resistance.

---

**Author:** *Saulius Stasys*  
**Project:** SunFlower AVR64DD32-MAIN-Controller  
**Version:** 1.0 *(Testing Stage)*  
**Language:** C / Embedded C for AVR-DD Series  
**Date:** 2025-10-14

---



