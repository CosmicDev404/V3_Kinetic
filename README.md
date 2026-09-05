# V3 Kinetic

A minimalist Wi-Fi RC trike controller built around an ESP8266, with independent rear-wheel drive, servo steering, haptic feedback, and a transmission watchdog.🛞

## Features
- Wi-Fi control through an ESP8266 access point
- Independent control of both rear motors
- Servo-based front steering
- Dual-wheel / synchronized-wheel mode
- WebSocket control on port ```81```
- Automatic stop if transmission is lost
- Built-in LED status feedback
- Mobile-friendly touch controls
- Haptic feedback through ```navigator.vibrate()```
## Setup
- Open the ```.ino``` file.
- Find the comment marking the webpage section.
- In the ```V3Kinetic.html```, replace ```45``` with the correct value wherever the servo center is defined.
- Paste the complete HTML controller code inside the ```PROGMEM``` webpage string at that location. 
- Set the servo center to your actual mechanical center. Replace ```45``` with the correct value wherever the servo center is defined.
- Set the servo limits to the actual safe range of your servo by replacing ```0–90``` with your measured minimum and maximum values.
- Upload the .ino to the ESP8266.
- Power the V3 Kinetic trike.
- Connect your phone/computer to the Wi-Fi network: ```V3 Kinetic``` 
- Password: ```AgiI-BAS0007(404)```
- Open (on any browser): ```192.168.4.1```

<i> The controller communicates with the ESP8266 using WebSockets on port 81. </i>

## Architecture

```Controller → Wi-Fi AP → WebSocket → ESP8266 → Servo + Motor Drivers```

The controller sends the current actuator values, while the ESP8266 watchdog stops the motors and returns the servo to its safe position when communication is lost.

## Hardware

Built around an ESP8266 NodeMCU, an L298N motor driver, two drive motors, and a servo-steered front wheel.

## Controller
- <strong> Wheel 1:</strong> Controls the first rear motor.
- <strong>Wheel 2:</strong> Controls the second rear motor.
- <strong>Servo:</strong> Controls the front steering angle. Release it to automatically return to its center.
- <strong>Dual:</strong> Both rear wheels can be controlled independently.
- <strong>Sync:</strong> Synchronizes both rear wheels to the Wheel control, turning the two-wheel controls into a single drive control.
- <strong>Park:</strong> Returns the motors to zero and the servo to its center position.
<p align=center>
<img width="50%" alt="Screenshot 2026-09-04 232255" src="https://github.com/user-attachments/assets/387ae211-2ec0-44eb-b6df-5838f7c12a82" /> <br> sync mode <br>
<img width="50%" alt="Screenshot 2026-09-04 232235" src="https://github.com/user-attachments/assets/e10d6744-e829-4581-a896-03f81ea6857a"/>  <br> dual mode
</p>


