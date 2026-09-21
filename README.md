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
- In the ```V3Kinetic.html```, update ```servo_centre``` variable and servo slider logic according to arrangement.
- Paste the complete HTML controller code inside the ```PROGMEM``` webpage string at that location. 
- Set the servo center to your actual mechanical center by updating ```servo_centre``` variable.
- Set the servo limits to the actual safe range of your servo by replacing ```0–90``` with your measured minimum and maximum values.
- Upload the .ino to the ESP8266.
- Power the V3 Kinetic trike.
- Connect your phone/computer to the Wi-Fi network: ```V3 Kinetic``` 
- Password: ```AgiI-BAS0007(404)```
- Open (on any browser): ```192.168.4.1```

<i> The controller communicates with the ESP8266 using WebSockets on port 81. </i>

### FPV Setup
(optional)

- Using [scrcpy](https://github.com/genymobile/scrcpy), any mobile phone can be mounted on V3 Kinetic acting as an FPV cam.
- Open a terminal window in ```scrcpy``` folder on your PC.
- Connect your phone via USB to the ```adb```.
- Ensure both the PC and phone are on the same wi-fi/hotspot network.
- Next, to switch to wifi connection, type ```adb tcpip 5555```, where 5555 can be any free ip port.
- Now, enter the following command: ```adb connect {phoneip}:5555``` where ```{phoneip}``` is the actual ip address of the phone in the network.
- Once adb is connected, following command can be used to access the camera sensor

 ```scrcpy --video-source=camera --camera-id={cam} --camera-size={size} --camera-fps={fps} --camera-zoom={zoom} --no-audio --video-codec=h264```
 
  where:
  - ```{cam}``` is the camera id → 0 for back cam and 1 for front cam
  - ```{size}``` is the stream resolution like 1280x720 or 640x480 (using small sizes can help reduce latency on a weak connection)
  - ```{fps}``` is the fps setting of the stream, like 15, 24, 30, etc.
  - ```{zoom}``` refers to camera zoom, typically 1-4
  - additionally, ```--camera-torch``` can be added to turn on the flashlight

 #### Architecture 

 ``` Phone mounted on V3 Kinetic → Wi-Fi → adb connection → scrcpy camera access → Live video stream on the PC screen ```
    
## Architecture

```Controller → Wi-Fi AP → WebSocket → ESP8266 → Servo + Motor Drivers```

The controller sends the current actuator values, while the ESP8266 watchdog stops the motors and returns the servo to its safe position when communication is lost.

## Hardware

Built around an ESP8266 NodeMCU, an L298N motor driver, two drive motors, and a servo-steered front wheel.

## Controller
- <strong>Wheel 1:</strong> Controls the first rear motor.
- <strong>Wheel 2:</strong> Controls the second rear motor.
- <strong>Servo:</strong> Controls the front steering angle. Release it to automatically return to its center.
- <strong>Dual:</strong> Both rear wheels can be controlled independently.
- <strong>Sync:</strong> Synchronizes both rear wheels to the Wheel control, turning the two-wheel controls into a single drive control.
- <strong>Neutral:</strong> Cuts power from the motors and returns the servo to its center position.
<p align=center>
<img width="1350" height="603" alt="Screenshot 2026-09-13 160350" src="https://github.com/user-attachments/assets/14556115-2329-442b-9540-5f694a5fc228" /> <br> sync mode <br>
<img width="1348" height="605" alt="Screenshot 2026-09-13 160319" src="https://github.com/user-attachments/assets/d6ad88f4-1255-4b07-a30f-d9ca5aecd1f8" />  <br> dual mode
</p>

## AI Disclosure

Large Language Models (LLMs) including ChatGPT and Gemini were used as productivity assistants during the development of this project.
- Human Core: The entire physical circuitry, Arduino IDE firmware, HTML controller structure, custom CSS styling, and core debugging were architected and implemented by the developer.
- AI Assistance: LLMs were utilized strictly to help scaffold the JavaScript boilerplate and initial WebSocket connection structure, along with minor CSS boxing issues.
- Developer Oversight: Advanced JavaScript layers—including the real-time UI controls and haptic feedback logic—were custom-written by hand. No automated suggestions were accepted blindly; all code was manually reviewed, verified, and integrated by the developer.

## Third-Party Software

This project uses [scrcpy](https://github.com/Genymobile/scrcpy)
by Genymobile for Android device camera access.

scrcpy is used as an external, unmodified tool and is not included
or modified in this repository.

Licensed under the Apache License 2.0.
