// Class for simulating a linear state-space model
//  x_{k+1}=Ax_{k}+Bu_{k}
//  y_{k} = Cx_{k}
//  starting from the initial state x0;
// The class is implemented using the Eigen library:
// http://eigen.tuxfamily.org/index.php?title=Main_Page
//*******************************************************************************************************************************
// AUTHOR: Aleksandar Haber,
// DEVELOPMENT: June 2020-
// VERSION DATE: June 25, 2020
// NOTE: This implementation is not optimized for extremely large-scale problems, since all the matrices are passed by value 
//*******************************************************************************************************************************

#ifndef SIMULATESYSTEM_H
#define SIMULATESYSTEM_H
#include <iostream>
#include<Eigen/Dense>
#include<tuple>
#include<string>
#include<fstream>
#include<vector>

using namespace Eigen;

// MatrixXd is an Eigen typdef for Matrix<double, Dynamic, Dynamic>


class SimulateSystem {
public:
	
	SimulateSystem();
	// default constructor
	// sets all the variables to 1x1 dimensional matrices and sets all the variables to zero
	
	SimulateSystem(MatrixXd Amatrix, MatrixXd Bmatrix, MatrixXd Cmatrix, MatrixXd initialState, MatrixXd inputSequenceMatrix);
	// overloaded constructor assigns all the private variables 


	~SimulateSystem();
	// Default destructor  - currently just an empty implementation in the ".cpp" file
	
	// MatrixXd is an Eigen typdef for Matrix<double, Dynamic, Dynamic>
	std::tuple<MatrixXd, MatrixXd, MatrixXd> getStateOuputTime();
	//this function returns the simulated state and output sequences, as well as the time row vector used for simulation

	void runSimulation();
	// function that simulates the system 

	void saveData(std::string AFile, std::string BFile, std::string CFile, std::string x0File, std::string inputSequenceFile, std::string simulatedStateSequenceFile, std::string simulatedOutputSequenceFile) const;
	// this function saves the data in "*.csv" files
	

	MatrixXd openData(std::string fileToOpen);
	// this function opens the "*.csv" file "fileToOpen" that stores a matrix, and loads the entries into the Eigen matrix MatrixXd
	
	void openFromFile(std::string Afile, std::string Bfile, std::string Cfile, std::string x0File, std::string inputSequenceFile);

	// this function assigns the A,B,C,x0, inputSequence variables using the information stored in the corresponding files 
	// this function calls the function MatrixXd openData(std::string fileToOpen);
	// this function acts as a constructor in some way. 
	// call this function after a default constructor is being called
	// the inspiration for creating this function was drawn from here (I did NOT copy and paste the code)
	// https://stackoverflow.com/questions/34247057/how-to-read-csv-file-and-assign-to-eigen-matrix


private:
	// MatrixXd is an Eigen typdef for Matrix<double, Dynamic, Dynamic>
	MatrixXd  A,B,C; // A,B,C matrices
	MatrixXd x0;     // initial state
	MatrixXd inputSequence;  // input sequnce, dimensions: m\times  timeSamples
	MatrixXd simulatedStateSequence; //simulated state sequence, dimensions: n\times  timeSamples
	MatrixXd simulatedOutputSequence; //simulated output sequence, dimensions: r\times  timeSamples
	MatrixXd timeRowVector;           // time row vector [0,1,2,3,\ldots, timeSamples-1]
	
	int m, n, r, timeSamples; //m - input dimension, n- state dimension, r-output dimension, timeSamples- number of time samples 

};
#endif