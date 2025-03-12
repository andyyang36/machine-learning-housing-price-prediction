## Machine Learning Housing Price Prediction
---

This project implements a housing price prediction model using linear regression with custom matrix operations in C. The application reads training and test data files, computes regression weights through matrix inversion and multiplication, and outputs predictions for the test data.

The goal is to demonstrate how fundamental matrix manipulation techniques—such as allocation, transposition, multiplication, and inversion—can be combined to solve a real-world problem like housing price prediction.

## Examples of Usage:
---
Training the Model and Generating Predictions: 
Training Data:

<img width="303" alt="image" src="https://github.com/user-attachments/assets/06057861-e990-4c42-a1fc-abc7ced4b6a9" />

Training File (Train.txt):

<img width="144" alt="image" src="https://github.com/user-attachments/assets/a99fb309-93de-4518-99b9-429a987a7832" />

Prediction Data:

<img width="199" alt="image" src="https://github.com/user-attachments/assets/a9e67bdc-a9f6-4319-acb5-6e39ba86caaf" />


Prediction File:

<img width="77" alt="image" src="https://github.com/user-attachments/assets/eac96f06-f2ff-4788-aaf8-78c3a5d1c6fe" />

Program Prediction:

<img width="644" alt="image" src="https://github.com/user-attachments/assets/f5bb6c1f-d6f5-4be8-a02f-0152f06a8bd9" />



Displaying Predictions:  



## Features
---
Efficient Matrix Operations:  
Implements custom functions for matrix allocation, transposition, multiplication, and inversion to perform linear regression.

Accurate Price Prediction:  
Computes regression weights from training data and applies them to test data to predict housing prices.

Dynamic Data Handling:  
Reads input data from formatted training and test files, allowing for flexible model training and testing.

Modular Code Structure:  
Separates functionality into multiple files for easier maintenance and potential future enhancements.

Command-Line Interface:  
Offers a simple interface for running predictions by specifying training and test data files.

## File Descriptions
---
main.c  
The main entry point of the application. It reads training and test data from files, orchestrates matrix operations to compute regression weights, and outputs housing price predictions for the test data.

matrix_functions.c  
Contains implementations of various matrix operations including allocation, freeing, augmentation, transposition, multiplication, and inversion used by the model.

matrix_functions.h  
Header file declaring the matrix operation functions implemented in matrix_functions.c.

Makefile  
Provides build instructions for compiling the project using gcc. It compiles the source files and links them into an executable named main.

## Installation
---
1. Clone the Repository  
   git clone https://github.com/andyyang36/machine-learning-housing-price-prediction.git

2. Change into the Project Directory  
   cd housing-model-predictor

3. Build the Project  
   Use the provided Makefile to compile the project:  
   make
   
4. Ensure proper train.txt and data.txt
   Train.txt should be the data you are using to train the prediction model
   Data.txt should be the data you are using to predict the price of

5. Run the Application  
   The executable expects two command-line arguments: the training data file and the test data file. For example:  
   ./main train.txt data.txt

6. Clean Up  
   To remove the compiled files and executable, run:  
   make clean
