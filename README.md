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

* 02: Threshold for the decision making on investment
   * This variable sets the maximum number of flags at which a firm decides to invest.
   The number of flags is increased by 1 when the products are sold out during the current period. Values of 10 or 20 were used in the present study, with 10 corresponding to firms investing more actively.

* 03: Timing of public investment-start-
   * This variable sets the period at which the government starts to purchase goods as a public investment. A value of 120 was used as a standard, but it was also changed variously in the present study to clarify the effect of timing of public investment on GDP.

* 04: Timing of public investment-end-
   * This variable sets the period at which the government ceases to purchase goods as a public investment. A value of 12 was used in the present study. This value is relative to the start period; that is, 12 corresponds to the public investment ending at the 132nd period, if it starts at the 120th period.

* 05: Amount of funds for investment
   * This variable sets the amount of funds available for public investment. This number is changed between three levels (i.e. small, middle, or large) for each of the two levels of ‘Thresholds for the decision making on investment’ variable in the present study.

* 06: DeltaPurchaseRatio
   * This variable sets the ratio of the funds used for efficient public spending. This value was changed from 0 to 1 with increments of 0.1, in the present study. A value of 1 corresponds to the extreme case of perfectly efficient public spending.

* 07: DeltaSubsidyRatio
   * This variable sets the ratio of funds used for inefficient public spending. This was set to be 1 − DeltaPurchaseRatio in the present study. A value of 1 here corresponds to the extreme case of perfectly inefficient public spending.

### 02Initial_file.csv

`02Initial_file.csv` contains parameters for initial conditions. Please do not change the values, to avoid execution errors. The values listed on the right-hand side were used in the present study.

Parameter | Description | Value used in the present study
---|---|---
01:period_max|Maximum number of simulation periods|360
02:nconsumer|Number of consumers|150
03:nretailer|Number of retailers|30
04:nwholesaler|Number of material-makers|6
05:nequipment|Number of equipment-makers|1
06:bank|Number of banks|1
07:min_with_drawal_ratio|Minimum value of withdrawal ratio for bank account|0
08:max_with_drawal_ratio|Maximum value of withdrawal ratio for bank account|0.5
09:bank_interest_rate|Interest rate of bank account|0.03
10:bonus_rate_min|Minimum value of the rate of bonus|0.75
11:bonus_rate_max|Maximum value of the rate of bonus|0.75
12:housyu_rate|The rate of executive compensation|0.95
13:n_class|Number of classes of products|12
14:Keynes_a|Constant value of Keynesian consumption function|3000
15:threshold_deposit|Value corresponding to marginal propensity to consume being 0.7| 10000
16:min_constant_wage|Minimum value of constant wage|7000
17:max_constant_wage|Maximum value of constant wage|7500
18:price_up_rate|The rate of increasing product price for producers|1.15
19:price_down_rate|The rate of reducing product price for producers|0.1
20:repay_time_ave|Repayment period for loans on investment (months)|120
21:invest_money|Price of equipment on investment|500000
22:max_ban|Maximum number of flags at which production is stopped|20
23:nmax_p|Maximum number of product classes produced by producers|2
24:nmax_c |Maximum number of product classes purchased by consumers|5

Remarks
* 02: The number of consumers must be larger than the sum of firms listed in 03–06, otherwise, the system will return an error.
* 10,11: The values for 10 and 11 must be the same
* 20: The number of flags increases by 1 when all of the products remain unsold in a certain period. When the cumulative number of flag reaches this value, the producer halts production of that class of products.
* 23: The value for 23 must be less than half that for 13.
* 24: The value for 24 must be less than half that for 13.

### 03Variable_file.csv

`03Variable_file.csv` contains the initial value of parameters for state variables which will change in its value during the simulation. Please do not change these values, because they are responsible for stable funds circulation.

### 04Other_file.csv

04Other_file.csv contains parameters for the standard variables of simulation. Please do not change these values, because they are not related to the present study but are related to stable running of the simulation.

## Simulation results

The simulation results are output to as csv files and stored in the “data” folder. The data files directly relating to the present study are 01OUTPUT_GDP.csv and 02OUTPUT_Deposit.csv. The multipliers are calculated based on the GDP data of simulation runs with and without public investment.

### 01OUTPUT_GDP.csv

Calculated GDP values at the end of each period are listed in this file. The period is listed in the first column and the GDP value at each period is listed in the next column.  

### 02OUTPUT_Deposit.csv

Total amounts of deposit of consumers and producers are listed in this file. The period is listed in the first column and the total deposits of consumers and producers at each period are listed in the subsequent columns.





