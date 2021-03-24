# 40-vp3380-fee1g
Research of 40-vp3380-fee1g board

## Connection
Board has 11 connection PINs:  
1. W-SW
2. U5V
3. IR
4. VCC
5. GND
6. Data
7. CS
8. CLK
9. GND
10. KS2
11. LED-


## Hardware
* Main component is TM1628 LED Driver ([datasheet](https://datasheetspdf.com/pdf-file/730553/TitanMicroElectronics/TM1628/1))
* 2 buttons
* IR sensor
  
On additional `40-vp3380-swe1g` board:
* 1 button
* 1 LED

### Buttons
Button IDs received from chip to use in Arduino sketch:
* K301 - 4
* K302 - 2
* K303 - 16

### LED
LED addresses
* LED3 - 1