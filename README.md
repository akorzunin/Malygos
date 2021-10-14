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

## Button(внешняя)
	- lump(внешняя)
	- sound generator
	- MCU
	- Display

pinouts
---
- распиновка разьема с кнопкой который юсб-Б
- распиновка разъема к лампе


3D models
---
- рендеры моделей
- 
<!--stackedit_data:
eyJoaXN0b3J5IjpbMjk3ODAwNjgwLDIxMzY5ODk1MTIsLTIwMT
c2NzMwODUsMTkyNTc3OTM3NSwtODAxMDAwNTUxLDczMTk1NTkw
OCwtMTk4Mzk3MjE3OSwxNTEyMTcwMDk0LC02NDM2MjQwNjMsMj
EwMTk2MjE0OSwyMjk4MDU2NjgsLTE0ODQyNTgxNzVdfQ==
-->