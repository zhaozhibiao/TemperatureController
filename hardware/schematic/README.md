# Temperature Controller Hardware Design Guide

This directory contains the schematic design resources for the Profinet Temperature Controller.

## Directory Structure
- `/schematic` - EDA schematic files (Altium/KiCad).
- `/pcb` - EDA PCB layout files.
- `/datasheets` - Save critical datasheets here (ADS124S08, netX 90, STM32G4).
- `/exports` - Gerber files, Pick & Place data, and PDF schematics.

## Key Design Constraints (Checklist)

### 1. Power Supply & Grounding
- [ ] **24V Input Protection**: Implement reverse polarity protection, over-voltage TVS (SMBJ30A), and a PPTC fuse.
- [ ] **Isolated Analog Section**: The ADS124S08 and thermocouple terminals MUST reside on an isolated analog ground plane (`AGND_ISO`).
- [ ] **Digital Isolation**: Use ISO7741 (or similar) to isolate the SPI bus and DRDY signal between the STM32 (`DGND`) and the ADS124S08 (`AGND_ISO`). Power the isolated side with a dedicated B0505S isolated DC-DC converter.

### 2. Thermocouple Acquisition (ADS124S08)
- [ ] **Input Filtering**: Every K-type TC input pair must have differential and common-mode RC low-pass filters to reject industrial EMI.
- [ ] **ESD Protection**: Use low-leakage ESD diodes on the TC inputs. Standard TVS diodes leak too much current and affect TC accuracy.
- [ ] **CJC Sensor**: Place a PT100 or precision NTC thermistor near the center of the TC terminal blocks. Route to AIN10/AIN11 of the ADS124S08 for Cold Junction Compensation.

### 3. MCU & Profinet (STM32G4 + netX 90)
- [ ] **Pin Mapping**: Refer to `STM32G474_Pinout.csv` for exact MCU pin assignments.
- [ ] **High-Speed SPI**: Route the SPI bus between the STM32 and netX 90 keeping traces short. Add 22Ω or 33Ω series termination resistors on the SCK and MOSI/MISO lines to prevent ringing.
- [ ] **Ethernet Magentics**: Maintain 100Ω differential impedance for the netX 90 TX/RX pairs. Use an RJ45 connector with integrated magnetics to save space.

### 4. Output Control
- [ ] **SSR Drives**: The 5 output channels from the MCU must drive optocouplers (e.g., TLP281-4) to isolate the MCU from the external SSR load.
- [ ] **LED Indicators**: Include LEDs on the primary side of the optocouplers for visual debugging of PWM outputs.

## Next Steps
1. Create the Altium/KiCad project in this directory.
2. Build the component library referencing the `../BOM.csv`.
3. Draw the hierarchical schematics.
