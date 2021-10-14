# Malygos
Control panel for intelligent team games
[Пульт управления для проведения интеллектуальных командных игр]
![Untitled](https://user-images.githubusercontent.com/54314123/137319788-ccec4c78-6cbe-46f5-9a30-05d019a2019e.JPG)


Introduction
---
### Top view:
![Artboard 1](https://user-images.githubusercontent.com/54314123/137303006-9e96bf90-dd47-48e2-9a92-495c06d83456.png)
1. MODE button
2. RESET button
3. START button
4. Time display
5. Mode indicator
6. Player button state indicator

### Right side view:
![Artboard 2](https://user-images.githubusercontent.com/54314123/137315055-df0e9c35-79ad-4655-a752-640abe631d8b.png)
7. DC-in jack
8. Power switch
9. Volume regulator
10. Speaker-out 3.5mm jack 
### Front view:
![Artboard 3](https://user-images.githubusercontent.com/54314123/137315685-522b7b23-c030-4e0a-854c-928fd0ea4df7.png)
11. RS-232 connector for display
12. Micro USB port

### Rear view:
![image](https://user-images.githubusercontent.com/54314123/137315934-f6aca98a-af7f-4295-8fb9-7bb81112c131.png)
 - 15 USB type B ports

How to use
===
## Quick start
1. Attach the AC/DC adapter to the DC-In jack
2. Attach speaker to audio jack
3. Plug in display to RS-232 connector
4. Use front buttons to select and run game modes

## How to update firmware
1. Disconnect all peripheral connectors
2. Attach micro USB cable
3. Upload firmware file with Arduino ide


Settings
---
- Adjust menu button timings:
	```
	//настройки для обработки кнопок меню [мс]

	#define DEBOUNCE 80 //антидребезг
	#define HOLD_TIMEOUT 1000 //удрежание
	#define CLICK_TIMEOUT 500 //одиночное нажатие
	```
- Change settings of sound subsystem:
	```
	//настройки звуковых сигналов  
	#define SHORT_SHORT_TONE_DUR 100  
	#define SHORT_TONE_DUR 300  
	#define LONG_TONE_DUR 1000  
	#define TONE_FREQ 500
	```
	

Schematic Diagrams
===
## System block diagram
![Malygos Diagram](https://user-images.githubusercontent.com/54314123/137328062-9f11bbd6-0966-4423-834c-058434eea05f.png)
### Front panel
![Front panel](https://user-images.githubusercontent.com/54314123/137330713-57e81d27-af7b-445b-a6dc-227b47d18e88.png)

### Button
![Button](https://user-images.githubusercontent.com/54314123/137337599-0c6f3976-c660-4446-821b-c970a43d1695.png)
NOTE: all disconnected pins connected with wires
### Button general
![Button general](https://user-images.githubusercontent.com/54314123/137337667-c846fdd1-4eb5-4d7b-910f-a5f02ff11912.png)
### MCU general
![MCU](https://user-images.githubusercontent.com/54314123/137338031-9ddc6f52-7889-4602-b8a7-b0450a896589.png)
### Sound preamp and interrupt circuitry
![sound and interrupt](https://user-images.githubusercontent.com/54314123/137338257-ffad3237-c4b2-4a39-8651-c85a5b550bc1.png)

### Display
![displayt](https://user-images.githubusercontent.com/54314123/137338482-ecfbc6aa-3d41-4327-834c-86868dee4ab4.png)


Pinouts
---
- USB type B player button pinout
![pinout](https://user-images.githubusercontent.com/54314123/137340688-7850846f-8a02-4305-ba0d-f12852f4eaab.png)



3D models
---
### Main body
![image](https://user-images.githubusercontent.com/54314123/137342293-1e99ceda-4560-4334-9ed2-0329849563ba.png)

### Lamp
![lamp](https://user-images.githubusercontent.com/54314123/137341362-1e88ea72-3584-4d13-940f-cacdeef3fedf.png)
### Player button
![button](https://user-images.githubusercontent.com/54314123/137341550-47e094f2-5823-4099-9620-5d9f1b8d77ea.png)
### Display

  
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTQwNDA1ODk1NCwtMTg2ODY5OTkxNCwyMD
cxNDk5NDAwLDI5NzgwMDY4MCwyMTM2OTg5NTEyLC0yMDE3Njcz
MDg1LDE5MjU3NzkzNzUsLTgwMTAwMDU1MSw3MzE5NTU5MDgsLT
E5ODM5NzIxNzksMTUxMjE3MDA5NCwtNjQzNjI0MDYzLDIxMDE5
NjIxNDksMjI5ODA1NjY4LC0xNDg0MjU4MTc1XX0=
-->