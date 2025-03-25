![STM32CubeIDE](https://img.shields.io/badge/STM32CubeIDE-%20lightblue?style=flat&logo=stmicroelectronics&link=https%3A%2F%2Fgithub.com%2FPhersax)
![GitHub](https://img.shields.io/badge/Github-purple?style=flat&logo=github&link=https%3A%2F%2Fgithub.com%2FPhersax)
![C](https://img.shields.io/badge/-%20darkblue?style=flat-square&logo=C)
![MATLAB](https://img.shields.io/badge/MATLAB-blue)
![Solidworks](https://img.shields.io/badge/SolidWorks-red?logo=solidworks&logoColor=white)
|[Kikad](https://img.shields.io/badge/KiCad-black?logo=kicad&logoColor=white)

## About the Project

This project aims to develop and implement a five-degree-of-freedom anthropomorphic manipu-
lator.
The ultimate goal is to create a modular robotic arm that is entirely 3D-printable and released as open-source, to promote
system reproducibility and accessibility.
The robot is designed using 3D modeling software. Subsequently, 3D printers are used to obtain
the parts needed for assembly. The motors used enable open-loop control, in fact, stepper motors have rotors that perform predefined rotations as long as no steps are lost,
while the servo motor has an internal control logic that allows for precise movements. 
The hardware required to operate the robot will consist of dedicated drivers and a control board. 
The ultimate goal of the project is to enable the end effector to follow specific trajectories with a
trapezoidal joint profile.


## Schematic

<img src="schematic/schematic.jpg" alt="Schematic" width="510" height="330">

### Note
The V1.0_gripper is the main folder of the whole code, anyway you can see for trajectories tested example in the folder v1.0_traj or the 'interrupt_vers' if you're looking for the implementation based on all interrupts. 

If you don't want to use the trapezoidal profile just comment the code as mentioned above, be sure that the timers are set in interrupt mode and check for __HAL_TIM_Base_Start_IT 

## Additional info
Check out the report if you are interested in our work!

[Link to the report](Dr5_report.pdf)

[Link to the pinout and configuration](Dr5_pinout&configuration.pdf)
🚀 Happy coding! 🌟
