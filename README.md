\# NOIR HOME

\### Smart Lock · Embedded Systems · Connected Intelligence



<p align="center">

&#x20; <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono\&size=18\&duration=3000\&pause=900\&color=8BCEDE\&center=true\&vCenter=true\&width=650\&lines=Engineering+Security+Through+Embedded+Systems;Real-Time+Control+%C2%B7+Connectivity+%C2%B7+Intelligence;Designed+to+Evolve" alt="NOIR HOME animated introduction" />

</p>



<p align="center">

&#x20; <strong>A modular smart-lock platform built around embedded control, connected devices, and a human-centered interface.</strong>

</p>



<p align="center">

&#x20; <img src="https://img.shields.io/badge/PROJECT-IN%20PROGRESS-8BCEDE?style=flat-square" alt="Project status" />

&#x20; <img src="https://img.shields.io/badge/EMBEDDED-C%2B%2B-777777?style=flat-square" alt="C++" />

&#x20; <img src="https://img.shields.io/badge/RTOS-FreeRTOS-777777?style=flat-square" alt="FreeRTOS" />

&#x20; <img src="https://img.shields.io/badge/CONNECTIVITY-Wi--Fi%20%7C%20MQTT-777777?style=flat-square" alt="Connectivity" />

&#x20; <img src="https://img.shields.io/badge/INTERFACE-WEB-777777?style=flat-square" alt="Web interface" />

</p>



\---



\## 01 — Overview



\*\*NOIR HOME\*\* is an in-progress smart-lock engineering project focused on reliable embedded control, modular firmware architecture, and connected home security.



Rather than treating a smart lock as a single device, the project separates real-time control, connectivity, user interaction, and supporting simulation into distinct components. This architecture is intended to make the system easier to test, extend, and eventually integrate with additional hardware and intelligent features.



The primary engineering focus is \*\*Embedded Systems (85%)\*\*, supported by web-based interaction, device communication, and future AI-assisted capabilities.



> \*\*Design principle:\*\* Keep critical control close to the hardware. Keep connectivity modular. Keep the system understandable and testable.



\## 02 — System Architecture



```text

&#x20;                    NOIR HOME

&#x20;               Smart Lock Platform

&#x20;                         |

&#x20;         +---------------+---------------+

&#x20;         |               |               |

&#x20;    noir\_core         noir\_link       Web Dashboard

&#x20;      STM32            Yolo UNO          Browser

&#x20;         |               |               |

&#x20;         |          Wi-Fi / MQTT         |

&#x20;         |               |               |

&#x20;         +-------- Communication --------+

&#x20;                         |

&#x20;                   Simulation

&#x20;                 Tests \& Tools

```



The diagram describes the intended system architecture. Hardware integration and individual communication paths are being developed incrementally.



\### Core components



| Component | Responsibility | Technology |

|---|---|---|

| `noir\_core/` | Intended real-time controller for door state, control logic, and safety-related behavior | STM32 · C/C++ · FreeRTOS planned |

| `noir\_link/` | Connectivity bridge and firmware development on the Yolo UNO platform | ESP32-S3 · C++ · PlatformIO |

| `NOIR-HOME-web-dashboard/` | Browser-based interface for interacting with and visualizing the smart-lock system | HTML · CSS · JavaScript |

| `simulation/` | Supporting environments for developing and exploring system behavior | Simulation tools |

| `tests/` | Space for component-level and integration tests | In development |

| `tools/` | Supporting scripts and engineering utilities | In development |



\## 03 — Engineering Scope



\### Access Control

\- PIN-based authentication prototype.

\- Configurable failed-attempt limits and temporary lockout behavior.

\- Door-control logic designed for modular testing.

\- Fingerprint and face-recognition integration planned.



\### Embedded Firmware

\- Modular C++ components with explicit responsibilities.

\- FreeRTOS task-based architecture and synchronization.

\- Separation between control logic and communication interfaces.

\- Gradual migration of real-time responsibilities toward the STM32 controller.



\### Connectivity \& Communication

\- Wi-Fi connectivity through the ESP32-S3 platform.

\- MQTT-oriented communication architecture.

\- A dedicated communication layer to reduce coupling between system components.

\- Future integration between the Yolo UNO bridge and STM32 controller.



\### Web Dashboard \& Intercom

\- Browser-based smart-lock interface.

\- Keypad and door-state interaction.

\- Visitor and intercom interface structure.

\- Event-log presentation and communication integration.

\- Future camera, voice interaction, and homeowner talkback capabilities.



\### Environment \& Emergency Features

\- Planned temperature and humidity monitoring.

\- Planned real-time clock and event timestamps.

\- Proposed emergency workflows for medical, fire, and police scenarios.

\- Emergency functions are intended for controlled demonstration until properly validated.



\## 04 — Technology Stack



<p align="center">

&#x20; <img src="https://img.shields.io/badge/C%2B%2B-Embedded%20Firmware-8BCEDE?style=flat-square\&logo=cplusplus\&logoColor=white" alt="C++" />

&#x20; <img src="https://img.shields.io/badge/FreeRTOS-Real--Time%20Tasks-555555?style=flat-square" alt="FreeRTOS" />

&#x20; <img src="https://img.shields.io/badge/ESP32--S3-Yolo%20UNO-555555?style=flat-square" alt="ESP32-S3" />

&#x20; <img src="https://img.shields.io/badge/STM32-Core%20Controller-555555?style=flat-square\&logo=stmicroelectronics\&logoColor=white" alt="STM32" />

&#x20; <img src="https://img.shields.io/badge/PlatformIO-Firmware%20Workflow-555555?style=flat-square\&logo=platformio\&logoColor=white" alt="PlatformIO" />

&#x20; <img src="https://img.shields.io/badge/HTML%20%2F%20CSS%20%2F%20JS-Web%20Interface-555555?style=flat-square" alt="Web technologies" />

&#x20; <img src="https://img.shields.io/badge/MQTT-Device%20Messaging-555555?style=flat-square" alt="MQTT" />

</p>



\*\*Primary focus:\*\* C/C++ firmware, embedded architecture, real-time task coordination, communication interfaces, and hardware integration.



The technology badges describe the project's development direction; they do not imply that every component is already implemented or integrated.



\## 05 — Repository Structure



```text

SmartLock-AI-Intercom/

├── noir\_core/                  # STM32 core controller

├── noir\_link/                  # Yolo UNO connectivity firmware

├── NOIR-HOME-web-dashboard/    # Web interface

│   ├── assets/

│   ├── css/

│   ├── js/

│   └── index.html

├── simulation/

│   ├── noir\_core\_sim/

│   └── noir\_link\_sim/

├── tests/                      # Test development

├── tools/                      # Supporting utilities

└── README.md

```



Some directories are placeholders for upcoming implementation. The repository structure will evolve as additional modules, tests, and hardware integrations are added.



\## 06 — Development Roadmap



\- \[x] Establish the project repository and initial modular structure.

\- \[x] Develop initial Yolo UNO firmware components for access control, door control, event handling, and communication.

\- \[x] Create the initial web dashboard structure.

\- \[x] Add initial simulation directory structure.

\- \[ ] Complete and verify FreeRTOS task coordination and synchronization.

\- \[ ] Complete the first-stage Yolo UNO firmware integration.

\- \[ ] Develop and test the STM32 core controller.

\- \[ ] Establish and validate inter-controller communication.

\- \[ ] Integrate the dashboard with the actual device communication layer.

\- \[ ] Add systematic component and integration tests.

\- \[ ] Extend visitor, intercom, environmental monitoring, and event-history functionality.

\- \[ ] Explore AI-assisted features after the embedded foundation is stable.



\*Roadmap items will be marked complete as their implementation and verification progress.\*



\## 07 — Getting Started



\### Yolo UNO Firmware



1\. Install \[Visual Studio Code](https://code.visualstudio.com/).

2\. Install the \[PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode).

3\. Open the `noir\_link/` directory as a PlatformIO project.

4\. Review `platformio.ini` and the board configuration.

5\. Build the firmware before uploading it to compatible hardware.



\### Web Dashboard



1\. Open `NOIR-HOME-web-dashboard/index.html` in a browser, or use a local development server.

2\. Explore the available interface components.

3\. Note that a functional connection to the physical device depends on the communication implementation and configuration.



\### STM32 Development



The `noir\_core/` directory is reserved for the STM32 controller. Toolchain configuration, firmware implementation, and hardware validation should be documented as they become available.



\## 08 — Engineering Notes



\- This repository represents a work in progress, not a production-ready security product.

\- Prototype authentication and communication must not be treated as sufficient protection for a real residential door.

\- Hardware-specific behavior must be validated on the target board.

\- Credentials, private keys, and deployment secrets must never be committed to the repository.

\- Simulation results do not replace hardware testing.



\## 09 — Project Vision



NOIR HOME is an opportunity to explore how dependable embedded software, modular architecture, and connected interfaces can come together in a practical device.



The long-term direction is to establish a reliable embedded foundation first, then extend the system with richer interaction and intelligent capabilities.



\*\*Built incrementally. Tested deliberately. Designed to evolve.\*\*



\---



<p align="center">

&#x20; <sub>NOIR HOME · Smart Lock Engineering Project · Firmware in Progress</sub>

</p>



