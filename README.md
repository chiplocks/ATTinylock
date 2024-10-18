# Attinylock

Attinylock is an NFC-enabled smart lock system designed to integrate with existing euro cylinder locks, adding a layer of digital access control while maintaining traditional key functionality. Its primary use case is for retrofitting onto a UPVC door to complement the lock mechanism without compromising the physical key system. Attinylock combines ease of use, convenience and customization to provide a seamless door access experience.

https://github.com/user-attachments/assets/20a3cf1a-0669-4bbe-a43e-0daaa2c50a40

![image](https://github.com/user-attachments/assets/6ef4d7ab-96e4-4bea-9226-0243cf697907)


## Key Features 

NFC Control for Keyless Entry
Attinylock uses Near Field Communication (NFC) technology to scan a user’s unique identifier (UID) from an NFC card, fob, or implant. Depending on the UID presented, the system commands a stepper motor to lock or unlock the door. This enables convenient keyless access, removing the need for traditional keys while retaining the option to use them.

## Stepper Motor Integration for Automated Locking
The system is built around a NEMA17 pancake stepper motor, which handles the rotation of the lock mechanism. This motor is strong enough to rotate the locking mechanism of most euro cylinder locks, ensuring smooth and reliable operation when locking or unlocking the door.

## Mechanical Toggle for Lock Status Detection
Attinylock uses a pogo pin toggle switch to detect whether the door is in a locked or unlocked state. This allows the system to stay synchronized with manual key turns, ensuring it knows the current status of the lock at all times. If the toggle is disengaged, it assumes a manual lock or unlock occurred and will adjust its behavior on the next scan accordingly.

## Feedback System for User Interaction
Visual and auditory feedback are provided via a WS2812b RGB LED and a 5020 buzzer. The RGB LED changes color to indicate different statuses, such as successful unlocks, lock errors, or communication problems with the NFC reader. The buzzer gives auditory confirmation with beeps, such as one beep for successful unlocking or three beeps for an invalid UID.

## Security Against Brute Force Attacks
To protect against brute-force attempts, the system increases the time delay between scans when multiple incorrect UIDs are presented. This delay increment helps slow down potential attackers trying to unlock the door by scanning numerous unauthorized UIDs in rapid succession.

## Error Detection with LED Indicators
The system’s RGB LED provides error notifications, such as a blue flash indicating a communication issue with the NFC reader. More color indicators can be added for different errors like power issues, motor jams, or NFC misreads.

## Hardware Components
NFC Reader: A PN532 NFC reader module scans the user’s NFC card, fob, or implant to compare UIDs.
Microcontroller: The ATtiny1616 serves as the control hub, executing code that drives the stepper motor and manages user input through NFC.

Motor: 
The NEMA17 pancake stepper motor ensures smooth and reliable rotation of the lock mechanism.
Power Supply: Requires a 12-15V power supply, typically from a mains adapter (wall wart).
## Other Essential Components:
AP63203 buck converter: Converts power from the mains to usable voltage for the system.
WS2812b RGB LED: Provides visual feedback during operation and error reporting.
5020 buzzer: Emits beeps for auditory feedback.
Pogo pin toggle switch: Detects manual locking or unlocking.
Custom 3D-printed barrel coupler: Adapts the motor to the euro cylinder lock mechanism.
## Installation Guide
Modify the Code
Before installing, add your authorized NFC UIDs (from cards, fobs, or implants) to the provided code. Compile the code and upload it to the ATtiny1616 microcontroller using a UPDI interface.

## Test the Lock Mechanism
After uploading the code, ensure the lock operates as expected by scanning your NFC card or fob. The motor should rotate the lock, and you should receive visual and auditory feedback indicating success.

## Prepare the Euro Cylinder Lock
Disassemble the rear barrel of the thumb-turn euro cylinder lock and replace it with the custom 3D-printed barrel coupler. This coupler connects the lock to the NEMA17 motor via a secure grub screw.

## Install the NFC Reader
Drill a 6mm hole in the UPVC door to feed the NFC reader's wire through. Connect the reader to the labeled JST-SH 6-pin header on the system.

## Secure the Final Setup
Make sure all connections are secure, especially between the motor, power supply, and microcontroller. Test the system by scanning your UID to lock and unlock the door.

## Usage Instructions
Unlocking/Locking the Door
Present your NFC card, fob, or implant to the reader. If the UID matches an authorized entry in the system, the buzzer will emit a beep, and the stepper motor will rotate the lock accordingly. If the lock was previously unlocked, it will lock, and vice versa.

## Incorrect UID Handling
If an incorrect UID is scanned, the buzzer will beep three times. After several incorrect attempts, the system will increase the delay between subsequent scans to deter brute-force attacks.

## Automatic Locking Feature
If the lock is manually turned, and neither pogo pin engages the system, the door will automatically lock upon the next correct UID scan.

## Troubleshooting
RGB LED Indicators

## Blue Flash: 
This indicates a communication error with the NFC reader. Ensure all connections are secure and that the reader is receiving sufficient power.

## Additional Error Colors:
The system can be extended with new LED color codes to signal different errors, such as power loss, motor failure, or incorrect installation.

## Manual Lock Disengagement
If the lock is turned manually, but the mechanical toggle fails to engage, the system will still attempt to lock automatically after the next correct scan. You can adjust the motor's locking direction by uncommenting the corresponding lock_clock or lock_anticlock definitions in the code.

## Power Supply Considerations
Attinylock requires a stable 12-15V power source, typically supplied via a mains adapter. Ensure the power adapter is properly rated to avoid issues with underpowering the stepper motor or NFC reader.

## Software & Libraries
The Attinylock codebase includes necessary libraries for NFC functionality, motor control, and feedback management. Users should refer to the documentation for installing and setting up the required software.
