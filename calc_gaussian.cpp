#include <iostream>
#include <math.h>
#include <tuple>
using namespace std;

double f(double mu, double sigma2, double x){
	//Use mu, sigma 2 and x to code the 1-dimensional Gaussian 
	double prob = 0.0;
	double constant = 1 / (sqrt(sigma2 * 2 * M_PI));
	double exponent = exp(-pow((x - mu), 2)/(2*sigma2));
	prob = constant*exponent;
	

	return prob;
}
tuple<double, double> measurement_update(double prior_mean, double prior_variance, double measurement_mean, double measurement_variance){
	// TODO: Code the measurement update mean function mu;
	double new_mean = (measurement_variance * prior_mean + prior_variance * measurement_mean) / (measurement_variance + prior_variance);
	// TODO: Code the measurement update variance function sigma squared
	double new_var = 1 / ((1 / measurement_variance) + (1 / prior_variance));
	return  make_tuple(new_mean, new_var);
}
tuple<double, double> state_prediction(double prior_mean, double prior_variance, double motion_mean, double motion_variance){
	// TODO: Code the measurement update mean function mu;
	double new_mean = prior_mean + motion_mean;
	// TODO: Code the measurement update variance function sigma squared
	double new_var = prior_variance + motion_variance;
	return  make_tuple(new_mean, new_var);
}


int main(){
	double measurements[5] = {5, 6, 7, 9, 10};
	double measurement_sig = 4;
	
	double motion[5] = {1, 1, 2, 1, 1};
	double motion_sig = 2;
	
	double mu = 0;
	double sig = 1000;
	// TODO: Put code below this
	// TODO: Loop through all the measurements
		// TODO: Apply a measurement update
		cout << "update:[" << mu << "][" << sig << "]" << endl;
		// TODO: Apply a state prediction
		cout << "update:[" << mu << "][" << sig << "]" << endl;

	return 0;
}