# Attinylock

Attinylock is an NFC-enabled smart lock system designed to integrate with existing euro cylinder locks, adding a layer of digital access control while maintaining traditional key functionality. Its primary use case is for retrofitting onto a UPVC door to complement the lock mechanism without compromising the physical key system. Attinylock combines ease of use, convenience and customization to provide a seamless door access experience.

https://github.com/user-attachments/assets/20a3cf1a-0669-4bbe-a43e-0daaa2c50a40




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

## Ongoing Development: Compact SMT PCB Design
The current prototype has operated flawlessly for the past three years, proving its reliability in real-world conditions. We are now in the process of developing a surface-mount technology (SMT) PCB that fits directly onto the face of the NEMA17 stepper motor. This new design will significantly reduce the system's overall size and complexity, providing a more efficient and compact form factor. The PCB will integrate all necessary components, offering a streamlined solution that maintains the functionality of the original design while improving installation ease and astetics while reducing wiring clutter.

## Decision to Drop WiFi-Based UID Updates:
In earlier iterations of this smartlock, WiFi connectivity was integrated to allow for the remote updating of authorized UIDs, eliminating the need for re-uploading code manually. This feature enabled users to add or remove UIDs over a soft acsess point, which was particularly convenient for dynamic environments where access control needed frequent changes. However, during the design phase for integrating all components onto a single PCB, it became apparent that the proximity of the NEMA17 stepper motor to the PCB antenna significantly degraded signal performance.

Challenges:
Electromagnetic Interference (EMI): The powerful electromagnetic fields generated by the stepper motor, especially when it is in motion, interfered with the WiFi module's ability to transmit and receive data reliably.
Design Complexity: Trying to shield the PCB antenna or create a workaround to mitigate interference added unnecessary complexity to the system, both in terms of hardware design and firmware management.
Cost Considerations: The addition of WiFi modules and the related circuitry not only increased the manufacturing cost but also introduced more points of potential failure in the system, such as signal loss or software bugs in the WiFi handling code.
Power Consumption: Maintaining a WiFi connection requires more power, which could strain the power supply, 

To ensure a more robust, cost-effective, and power-efficient solution, the team decided to drop the WiFi feature in favor of using a UPDI programmer to re-upload the firmware when UID updates are required. This approach ensures that:

The system remains simpler to manufacture and assemble, reducing wiring clutter and potential failure points.
It is more reliable in real-world environments, particularly where WiFi signal reliability might fluctuate.
The overall cost and power requirements of the system are minimized, making Attinylock more accessible to users without sacrificing core functionality.

## Why the Stepper Motor Was Chosen
The NEMA17 pancake stepper motor was chosen for Attinylock primarily due to its ability to provide sufficient torque for locking and unlocking the door, while also offering the benefit of free rotation when the motor is not energized. This feature ensures that traditional key access is unhindered, allowing users to manually turn the lock without the motor obstructing or resisting the movement.

Unlike servos or smaller geared motors, stepper motors have the unique advantage of being able to freewheel when not powered. In Attinylock’s case, this allows the euro cylinder lock to be rotated manually with a key, even when the system is powered off or idle.
Manual Override: This feature is critical for retaining the traditional key functionality, ensuring that users can always lock or unlock the door manually without encountering resistance from the motor. Servos, by contrast, maintain a fixed position when not in use and would resist manual turning, making them less suitable for this application.
Sufficient Torque for Locking Mechanism:

The torque provided by the NEMA17 stepper motor ensures that the lock mechanism can be reliably rotated to engage or disengage the lock. Euro cylinder locks, especially in older or more complex mechanisms, can sometimes require extra force to turn due to tight tolerances or environmental factors (e.g., temperature changes causing metal parts to expand).
By using a stepper motor, Attinylock is capable of delivering the necessary rotational force without sacrificing precision, ensuring that the lock turns smoothly and reliably every time.
Balance of Torque and Power Consumption: The NEMA17 motor provides an optimal balance of torque and power consumption, ensuring that the motor can lock and unlock the door effectively without drawing excessive power, which is important for the system's power supply management.

Stepper motors are designed to move in discrete steps, which makes them ideal for applications requiring precise control over position. This ensures that Attinylock can:
Lock and unlock with exact rotational precision, aligning the lock perfectly after each operation.
Switch directions easily to either engage or disengage the lock based on the input signal from the NFC reader, with no need for additional sensors to determine the position of the motor.
Servos, on the other hand, would require continuous feedback to achieve the same level of precision, adding complexity to the system and increasing the chances of failure due to misalignment or over-rotation.

Since stepper motors do not have the gearing commonly found in smaller motors or servos, there are fewer moving parts that can wear out over time. This results in a more durable system, which is essential for a smart lock expected to perform reliably over the long term.
Geared motors can wear out over time as their mechanical gears degrade, which could introduce slack or inaccuracies in the locking mechanism, leading to eventual failure. By avoiding this, the NEMA17 stepper motor helps maintain the long-term integrity of the Attinylock system.
Comparison to Servos and Geared Motors:
Servo Motors: Servo motors hold their position unless powered down or explicitly moved. This means if a servo were used in the Attinylock design, it would offer resistance to manual key turns unless disengaged or powered off, complicating the manual override process. Additionally, servos typically offer less torque than a NEMA17 stepper motor and would require a more complex feedback mechanism to ensure accurate positioning during lock operations.

Geared Motors: Geared motors often have a higher torque than servos but come with the drawback of mechanical resistance due to the gear train, even when not powered. This resistance would interfere with manual key use and could cause wear over time, reducing reliability. Geared motors are also less precise without a feedback system and may not provide the same level of control required for precise locking operations.

The free-rotating feature of the stepper motor ensures that manual access remains fully functional even if there’s a power failure or if the motor is offline for any reason. This design choice adds an extra layer of safety and reliability, allowing users to fall back on traditional key-based access if needed.

By using the stepper motor, you’ve also allowed for simple and safe manual operation, meaning that users can still feel confident that they will never be locked out due to mechanical failures or system malfunctions.

## Why ATtiny1616?

Low Power Consumption: The ATtiny1616 is a microcontroller from the AVR family, known for its efficiency in power-constrained applications. This ensures that the system can operate reliably even in environments where power conservation is important.
Sufficient I/O Ports: With its 16 pins, the ATtiny1616 provides enough general-purpose input/output (GPIO) for all the components in Attinylock (NFC reader, stepper motor driver, RGB LED, buzzer, toggle switch, etc.).
Cost-Effectiveness: The ATtiny1616 is a cost-effective choice that balances performance and affordability, making it an excellent fit for a project like Attinylock, where keeping manufacturing costs low is crucial.
Memory and Storage: It has enough flash memory (16KB) and RAM (2KB) to handle the NFC UID authentication, motor control, and feedback management without needing a more complex (and expensive) microcontroller.
Compact Size: Its small form factor allows it to fit neatly into a compact PCB design, minimizing the overall size of the Attinylock system.

## Why PN532?

Industry Standard for NFC: The PN532 is one of the most widely used and reliable NFC modules, making it a safe choice in terms of compatibility and documentation.
Ease of Integration: The module supports I2C, SPI, and UART interfaces, making it flexible and easy to integrate into systems with a variety of microcontrollers, including the ATtiny1616.
UID Reading Accuracy: The PN532 can accurately and quickly read ISO/IEC 14443 Type A/B cards, ensuring seamless user experience when scanning NFC tags for lock/unlock operations.
Wide Range of NFC Options: It supports different types of NFC media, such as cards, key fobs, and even implants, which adds to the system’s versatility in access control.

## Why 12-15V Power Supply?

Stepper Motor Power Requirements: Stepper motors, especially those like the NEMA17, require a higher voltage than typical low-power microcontrollers. A 12-15V power supply ensures that the motor receives enough power to operate reliably without stalling.
Buck Converter Compatibility: This voltage range is compatible with the AP63203 buck converter, which steps down the voltage to levels suitable for powering the microcontroller and other low-power components.

## Why AP63203 Buck Converter?

High Efficiency: The AP63203 is a synchronous step-down converter known for its high efficiency, which minimizes heat generation and power loss during operation. This is important for ensuring stable power delivery, especially during the stepper motor’s high-current demands.
Compact Design: Its small size fits well within the compact PCB layout of Attinylock, minimizing overall system size and making installation easier.
Wide Input Voltage Range: It can accept input voltages between 3.8V and 32V, making it versatile for a range of power supplies and ensuring stable operation even if the input voltage fluctuates slightly.

## Why WS2812b RGB LED?

Single-Wire Communication: The WS2812b uses a single-wire communication protocol, meaning fewer GPIO pins are needed to control it, freeing up pins on the ATtiny1616 for other tasks.
Customizable Colors: This LED can display millions of colors, allowing for easily customizable feedback signals, such as green for successful unlocks or red for errors.
Power Efficiency: It is relatively low-power, making it a good choice for providing feedback without significantly increasing the system's overall power consumption.

## Why 5020 Buzzer?

Simple, Effective Feedback: The buzzer can emit audible tones to quickly alert the user of the system’s status, adding an extra layer of feedback beyond the LED.
Low Power Consumption: This buzzer consumes very little power, making it an excellent fit for Attinylock, where power efficiency is important.
Compact Size: Its small size allows it to fit easily into the system’s compact design.

## Why Pogo Pin Toggle Switch?

Mechanical Flexibility: Pogo pins are spring-loaded, ensuring reliable contact even in slightly misaligned or moving parts. This makes them well-suited for detecting mechanical movements like the rotation of a lock.
Durability: Pogo pins are designed to endure repeated engagements, making them durable enough for frequent locking and unlocking operations without wearing out.
Accurate State Detection: The toggle switch ensures that the system always knows the current state of the lock, preventing errors like attempting to re-lock an already locked door or unlock an already unlocked door.

Each hardware component in Attinylock was carefully selected based on its ability to meet the design goals of reliability, precision, cost-effectiveness, and user-friendly functionality. By choosing components like the NEMA17 stepper motor, ATtiny1616 microcontroller, and PN532 NFC reader, the system ensures smooth, efficient, and flexible access control, all while retaining traditional manual key functionality.
