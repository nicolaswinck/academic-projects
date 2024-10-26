#ifndef SYSTEM_H
#define SYSTEM_H


#define FMT_FORM 1
#define FMT_TABLE 2
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10
#define MIN_INTERVAL 30
#define START_HOUR 10
#define END_HOUR 14


struct Phone
{
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];
};


struct Patient
{
    int patientNumber;
    char name[NAME_LEN + 1];
    struct Phone phone;
};


struct Time
{
    int hour;
    int min;
};


struct Date
{
    int year;
    int month;
    int day;
};


struct Appointment
{
    int patientNumber;
    struct Date date;
    struct Time time;
};


struct ClinicInfo
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};


void selectionSort(struct Appointment appoints[], int max);

// Display functions.

void displayPatientTableHead(void);

void displayPatientData(const struct Patient* patient, int fmt);

void displayScheduleTableHead(const struct Date* date, int isAllRecords);

void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField);

// Menu functions.

void menuMain(struct ClinicInfo* data);

void menuPatient(struct Patient patient[], int max);

void menuPatientEdit(struct Patient* patient);

void menuAppointment(struct ClinicInfo* data);

void displayAllPatients(const struct Patient patient[], int max, int fmt);

void searchPatientData(const struct Patient patient[], int max);

void addPatient(struct Patient patient[], int max);

void editPatient(struct Patient patient[], int max);

void removePatient(struct Patient patient[], int max);

void viewAllAppointments(struct ClinicInfo* data);

void viewAppointmentSchedule(struct ClinicInfo* data);

void addAppointment(struct Appointment* appoints, int maxApp,
    struct Patient* patients, int maxPt);

void removeAppointment(struct Appointment* appoints, int maxApp,
    struct Patient* patients, int maxPt);


// Utility functions

void searchPatientByPatientNumber(const struct Patient patient[], int max);

void searchPatientByPhoneNumber(const struct Patient patient[], int max);

int nextPatientNumber(const struct Patient patient[], int max);

int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);

int appointNotAvailable(struct Date date, struct Time time,
    struct Appointment* appoints, int maxApp);

int nextAvailableSchedule(struct Appointment* appoints, int maxApp);

int getFinalDay(int month, int year);


// Input functions.

void inputPatient(struct Patient* patient);

void inputPhoneData(struct Phone* phone);

struct Date inputDate(void);


// File functions.

int importPatients(const char* datafile, struct Patient patients[], int max);

int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !SYSTEM_H