// main.c
#include "two_stream.h"
#include "constant.h"  // <-- Add this line
#include "planck.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main() {
    // Sample data for the function (you'll need to provide appropriate values or adjust as necessary)
    int NLAYER = 10;
    int kmin = 1;
    double w0_array[NLAYER];
    double g0_array[NLAYER];
    double temperature_array[NLAYER];
    double tau_array[NLAYER];
    double NU = 1.133e+14; // Sample value
    double NU_BIN = 1.0; // Sample value
    double incident_frac = 1.0; // Sample value
    double dtau_array[NLAYER];

    double start_w0 = 0.2;
    double end_w0 = 0.8;
    double step_w0 = (end_w0 - start_w0) / (NLAYER - 1);

    double startLog_dtau = log(1e-4);
    double endLog_dtau = log(1e2);
    double step_dtau = (endLog_dtau - startLog_dtau) / (NLAYER - 1);

    double test;

    // Start the running sum
    double running_sum = 0.0;

    double intensity_vals[2];

    for (int i = 0; i < NLAYER; i++) {
        w0_array[i] = start_w0 + i * step_w0;
        g0_array[i] = 0.0;
        temperature_array[i] = 1000.0 + i * 100;

        // Compute the dtau value
        dtau_array[i] = pow(M_E, startLog_dtau + i * step_dtau);

        // Update the running sum and assign to tau_array
        running_sum += dtau_array[i];
        tau_array[i] = running_sum;
    }

    // Call the two_stream function
    two_stream(NLAYER, kmin, w0_array, g0_array, temperature_array, tau_array, NU, NU_BIN, incident_frac, dtau_array, intensity_vals);
    //printf("Two stream %le %le\n", intensity_vals[0], intensity_vals[1]);


    //printf("\n");
    //for(int J=0; J<NLAYER; J++)
    //{
    //    test = test + Planck(temperature_array[J], CLIGHT / NU) * exp(-tau_array[J]) * dtau_array[J];
    //}
    //printf("Abs Only %le\n", test);

    return 0;
}
