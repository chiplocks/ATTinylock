# Attinylock

**Attinylock** is an NFC-controlled smart lock designed to replace traditional key access to a euro cylinder barrel lock on a UPVC door. It uses NFC technology to scan UIDs and commands a stepper motor to lock or unlock the door based on user input. With Attinylock, you can streamline your door locking mechanism and increase convenience by eliminating the need for physical keys.

![image](https://github.com/user-attachments/assets/6ef4d7ab-96e4-4bea-9226-0243cf697907)


## Features

- **NFC Controlled:** Scans a 4-byte or 7-byte UID via an NFC card, fob, or implant to unlock or lock the door.
- **Stepper Motor Integration:** Uses a NEMA17 pancake stepper motor to rotate the lock mechanism.
- **Mechanical Toggle:** Utilizes a mechanical toggle switch to determine the locked or unlocked state.
- **Feedback System:** Provides visual and auditory feedback with a WS2812b RGB LED and 5020 buzzer.
- **Anti-Brute Force Security:** If an incorrect UID is scanned, and the delay between scans increases to deter brute-force attacks.
- **Error Detection:** The RGB LED flashes different colors to indicate errors (e.g., communication issues with the reader show a blue flash).

## Hardware Components

- **NFC Reader:** PN532 NFC reader module.
- **Microcontroller:** ATtiny1616.
- **Motor:** NEMA17 pancake stepper motor.
- **Power Supply:** 12-15V, typically from a wall wart.
- **Other Components:**
  - AP63203 buck converter
  - WS2812b addressable RGB LED
  - 5020 buzzer
  - Pogo pin toggle switch
  - Custom 3D-printed barrel coupler

## Installation

1. **Modify Code:** Add your NFC card or fob UIDs to the code. Compile and upload using the UPDI interface.
2. **Testing:** Verify that the lock operates correctly by scanning your UID.
3. **Disassemble Euro Cylinder Lock:** Remove the rear barrel from the thumb-turn euro cylinder lock.
4. **Install Barrel Coupler:** Replace the rear barrel with a custom 3D-printed barrel coupler (an example STL file is provided). Ensure that the coupler fits securely onto the motor shaft with the grub screw.
5. **Drill Hole for NFC Reader:** Drill a 6mm hole in the PVC door to feed the NFC reader wire through. Connect the reader to the JST-SH 6-pin connector labeled "header."
6. **Final Setup:** Ensure all connections are secure and test the system by scanning your UID.

## Usage

1. **Scan to Unlock/Lock:** Present your NFC card, fob, or implant to the reader. If the UID matches, the buzzer will beep, and the motor will rotate the lock.
2. **UID Rejection:** If an incorrect UID is scanned, the buzzer will beep three times, and the delay between scans will increase.
3. **Automatic Locking:** If the lock is manually turned and neither pogo pin is engaged, the system will automatically lock on the next correct UID scan.

## Troubleshooting

1. **RGB LED Indicators:**
   - **Blue Flash:** Indicates a communication issue with the NFC reader.
   - **Additional Colors:** More colors will be added for other error conditions.
   
2. **Manual Lock Issue:** If the lock is manually turned and the mechanical toggle does not engage, the system will attempt to lock automatically after the next correct scan. Ensure that you specify the locking direction in the code by uncommenting either the `lock_clock` or `lock_anticlock` definition.

## Power Supply

- Attinylock requires a 12-15V power source, typically connected to a mains power outlet via a wall adapter.

## Software & Libraries

Refer to the codebase for required libraries and dependencies.

## Customization

- Users will need to adjust the 3D-printed barrel coupler's dimensions to match their specific euro cylinder lock barrel.

---
