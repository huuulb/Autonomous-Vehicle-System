# Autonomous-Vehicle-System 
A smart 4-wheel car based on STM32F446RE microcontroller that suppports both manual Bluetooth control and obstacle avoiding.

## Features
- **Bluetooth Control**: Manual control via Android application using HC05 module
- **Autonomous Navigation**: Obstacle Avoidance using ultrasonic sensor and servo motor
- **Real-time Display**: Distance measurements shown on OLED screen
- **PWM Motor Control**: Smooth movement control for all 4 wheels and servo motor

### Hardware Components:

| Component | Purpose |
|-----------|---------|
| STM32F446RE | Main microcontroller |
| TB6612 | Motor driver |
| HC05 | Bluetooth communication |
| HC-SR04 | Ultrasonic distance sensor |
| Servo Motor | Sensor positioning |
| SSH1106 OLED | Distance display |
| 4x DC Motors | Wheel movement |
| AMS1117 5v | Voltage Conversion |
| Resistors (1kΩ, 2kΩ) | Circuit protection |

## 🔧 System Architecture
```
Android App ──(Bluetooth)──> HC05 ──> STM32F446RE ──> TB6612 ──> Motors
                                         │
                                         ├──> Servo Motor ──> HC-SR04
                                         │
                                         └──> SSH1106 OLED
```
## Control Modes

### 1. Manual Control (Bluetooth)
- Forward/Backward movement
- Left/Right turning
- Speed control via PWM
- Real-Time command response

### 2. Autonomous Mode
- Automatic obstacle detection
- Dynamic path planning
- Servo-controlled sensor scanning

## How It Work
1. **Bluetooth Mode**: Android app sends commands → HC05 receives → STM32 processes → Motors respond
2. **Autonomous Mode**: HC-SR04 scans environment → STM32 analyzes distances → Servo adjusts sensor angle → Motors navigate around obstacles
3. **Display**: Real-time distance measurements and system status shown on OLED

## 📊 Technical Specifications

- **Operating Voltage**: 7.5V(motor), 9V(convert to 5v for OLED/HC05)
- **Communication**: Bluetooth 2.0 (HC05)
- **Detection Range**: 2cm - 400cm (HC-SR04)
- **Motor Control**: 4-channel PWM
- **Display**: 128x64 OLED

## Demo Videos
### Bluetooth Control 
*Manual control demonstration*

<img src="https://github.com/user-attachments/assets/1e3fd09e-fa50-47ac-ac98-487bd05537cd" width="450">
<img src="https://github.com/user-attachments/assets/87320189-cdb9-435e-8e5e-a9c87a9e2041" width="450")

- [Google Drive](https://drive.google.com/file/d/1X2vIEITzeRsUi9aAgjjDEpIKbF9JVhJ4/view?usp=drive_link)

### Obstacle Avoidance

*Autonomous navigation demonstration*
video insert
