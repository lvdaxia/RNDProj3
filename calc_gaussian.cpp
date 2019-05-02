#include <iostream>
#include <math.h>
#include <tuple>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/LU>
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
tuple<MatrixXf, MatrixXf> multi_measurement_update(){
	
}


int main(){
	// ? The measurement values to feed into the measurement update step
	vector<double> measurements = {5, 6, 7, 9, 10};
	double measurement_sig = 4;
	// ? The motion values to feed into the state prediction step
	vector<double> motion = {1,1,2,1,1};
	double motion_sig = 2;
	// * Initial state	
	double mu = 0;
	double sig = 1000;
	// TODO: Put code below this
	// TODO: Loop through all the measurements
	tuple<double, double> output_placeholder;
	// ? My understanding of the Kalman Filter is to perform the measurement update
	// ? then perform the state prediction and then feed these values back into mu and sig
	for(int i = 0; i < measurements.size(); i++)
	{
		tie(mu, sig) = measurement_update(mu, sig, measurements[i], measurement_sig);
	cout << "update: [" << mu << ", " << sig << "]" << endl;
		// cout << "measurement mean: " << mu << endl;
		// cout << "measurement variance: " << sig << endl;
		tie(mu, sig) = state_prediction(mu, sig, motion[i], motion_sig);
	cout << "predict: [" << mu << ", " << sig << "]" << endl;
		// cout << "state mean: " << mu << endl;
		// cout << "state variance: " << sig << endl;
	}
	// tie(mu, sig) = measurement_update(20, 9, 30, 3);	
	// tie(mu, sig) = state_prediction(mu, sig, 7.5, 5);

	return 0;
}