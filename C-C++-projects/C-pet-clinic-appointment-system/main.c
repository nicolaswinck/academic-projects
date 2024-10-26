#include <stdio.h>
#include "system.h"
#define MAX_PETS 20
#define MAX_APPOINTMENTS 50

// Main function to retrieve files information and start the application.
int main(void)
{
    struct Patient pets[MAX_PETS] = { {0} };
    struct Appointment appoints[MAX_APPOINTMENTS] = { {0} };
    struct ClinicInfo data = { pets, MAX_PETS, appoints, MAX_APPOINTMENTS };

    int patientCount = importPatients("patientInfo.txt", pets, MAX_PETS);
    int appointmentCount = importAppointments("appointmentInfo.txt", appoints, MAX_APPOINTMENTS);

    printf("%d patient records imported.\n", patientCount);
    printf("%d appointment records imported.\n\n", appointmentCount);

    menuMain(&data);
    
    return 0;
}