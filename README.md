# This is a code uploaded into ATmega32P MCU
## Menu loop
When powered the cube displays 0 digit. By pressing "up button" you can increment the digit displayed by one. Each digit represenst one display pattern. When "action button" pressed the pattern displays

## Display pattern
There are 6 displays pattern on digits from 0 to 5
- Random number
- Rain
- Heavy rain
- Crusher
- Running points
- Expanding cube

## Presentation
Presentation of working code and (electronics was still in progress)
https://youtu.be/NpTNd8zq_Pg

## Electronic schematic
![Scheme-LED](https://user-images.githubusercontent.com/62220648/164735447-10ad1311-a12c-4e7d-9ef5-8022c1860d6d.jpg)
<p align="center">
  Scheme of 125 LED's
</p>

![Scheme-MCU](https://user-images.githubusercontent.com/62220648/164736124-25907489-04eb-4d05-99e8-45eada0dbdfe.jpg)
<p align="center">
  Scheme of MCU placement and it's peripherials
</p>
##
- Powered with 5V by USB mini-B input
- 2 buttons to navigate throughout menu
- 1 button to choose display pattern and leave one
- TransistorSwitches is a scheme of electronics allowing to control 125 LED's with 15 output pins of MCU showed belowe

![Scheme-Transistor](https://user-images.githubusercontent.com/62220648/164736286-79ba2c55-30b3-454f-a71d-779dbadbbc2f.jpg)
<p align="center">
  Scheme of module allowing to control 125 LED's
</p>
