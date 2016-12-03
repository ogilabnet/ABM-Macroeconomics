# ABM-Macro

## Background

This program was written for use in our study (hereinafter, referred to as “present study”) “Influence of Inefficiency in Government Expenditure on the Multiplier of Public Investment,” now under submission to Computational Economics. In this study we analyzed the relationships between GDP and inefficiency in government expenditure, as well as the amount of public spending and other factors.

This program is written using Visual C++, part of Microsoft Visual Studio 2010. If you use this program, please use the same version of the compiler, to avoid any issues.

There are three folders in ABM-Macroeconomics: “code,” “parameter,” and “Release”.
The “code” folder contains the source files and header files. The “parameter” folder contains four parameter files. The “Release” folder contains four files including an executable file.

Questions on this software program are welcome; please email them to Shigeaki Ogibayashi (ogibayashi@ogi-lab.net).

## Running ABM-Macroeconomics

Running ABM-Macroeconomics without using an application development environment

1. Create three folders in any directory on your local computer and name them “Release,” “parameter,” and “data”.
2. Copy the files from ABM-Macroeconomics to the corresponding folders in your computer. The “data” folder will be empty, initially.
3. Run Up_code10.exe, located in the “Release” folder.
4. The program will run, and the files of simulated results will be stored in the “data” folder. You can change the calculation parameters according to the instructions explained below. This procedure has been confirmed to work in the Windows environment. 

## Running ABM-Macroeconomics using Microsoft Visual Studio

1. Create a solution as well as a project in Visual Studio 2010.
2. Create folders named “data” and “parameter” inside the directory for the solution (i.e. the directory above the project).
3. Copy the four files from the “parameter” folder of ABM-Macroeconomics to the corresponding folder on your computer.
4. Copy the header files and source files from the “code” folder of ABM-Macroeconomics to the newly created project on your computer.
5. Add the header files and source files into the project.
6. Build the solution and project, and run the simulation.
7. The simulation results will be stored in the folder named “data”.

## Setting parameters

Parameter files `01Experimental_file.csv`, `02Initial_file.csv`, and `03Variable.csv` include the parameter values relating to the present study. These parameters can be changed by the user. Each parameter file contains parameter values to be set on the first row as well as the variable name for each value on the second row. Please change only the parameter values (on the first row), not the variable names. The parameter file 04Other_file.csv includes the parameters relating to the environmental variables for calculation; please do not change the set values.

### 01Experimental_file.csv

`01Experimental_file.csv` contains parameters for experimental levels of the present study. The users can change the value of these parameters.

* 01: Upper limit of the number of loans
   * This variable sets the maximum number of loans firms can hold at the same time in each period. Smaller values correspond to more severe credit rationing. Values between 1 to 3 were used in the present study. 
