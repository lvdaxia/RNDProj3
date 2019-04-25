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


int main(){
	cout << f(10.0, 4.0, 8.0) << endl;
	return 0;
}