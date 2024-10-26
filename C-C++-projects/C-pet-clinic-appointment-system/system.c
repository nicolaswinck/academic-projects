#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "system.h"


// Display functions.

void displayPatientTableHead(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}


void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


void displayScheduleTableHead(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}


void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


// Menu functions.

void menuMain(struct ClinicInfo* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}


void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}


void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


void menuAppointment(struct ClinicInfo* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, recordsOk = 0;

    // Verifying format value.
    // Displaying the table heather for the patients.
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHead();
    }

    // Iterating the patient array and displaying each patient.
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);


            // Validation flag for eligible records.
            recordsOk = 1;
        }
    }

    putchar('\n');

    // Displaying message for no records.
    if (!(recordsOk))
    {
        printf("*** No records found ***\n\n");
    }
}


void searchPatientData(const struct Patient patient[], int max)
{
    int userInput;

    // Displaying selection menu (the zero selection breaks the sequence)
    // and gets back to the previous menu.
    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        // Getting input from the user (allowed from 0 up to 2).
        userInput = inputIntRange(0, 2);
        putchar('\n');

        // Calling the selections.
        if (userInput == 1)
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (userInput == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }

    } while (userInput);
}


void addPatient(struct Patient patient[], int max)
{
    int i, idx, foundRecord = 0;

    // Assigning the patient index value.
    // Searching for empty record in the array.
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            foundRecord = 1;
            idx = findPatientIndexByPatientNum(patient[i].patientNumber, patient, max);
        }
    }

    // Allowing new patient: getting input for the new record.
    if (foundRecord)
    {
        patient[idx].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[idx]);
        printf("*** New patient record added ***\n\n");
    }
    // Record not found: displaying error message for full database.
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}


void editPatient(struct Patient patient[], int max)
{
    int userInput, idx;

    // Displaying user prompt for patient number.
    // Getting user input.
    printf("Enter the patient number: ");
    userInput = inputIntPositive();

    // Assigning the value (-1 if not found, the index if found).
    idx = findPatientIndexByPatientNum(userInput, patient, max);

    putchar('\n');

    if (idx != -1)
    {
        menuPatientEdit(&patient[idx]);
    }
    // Displaying error message for non-existing patient.
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


void removePatient(struct Patient patient[], int max)
{
    struct Patient empty = { 0 };
    int userInput, idx, userOption;

    // Displaying user prompt for patient number.
    // Getting user input.
    printf("Enter the patient number: ");
    userInput = inputIntPositive();

    // Assigning the value (-1 if not found, the index if found).
    idx = findPatientIndexByPatientNum(userInput, patient, max);

    putchar('\n');

    if (idx != -1)
    {
        // Displaying formatted table for the patient.
        displayPatientData(&patient[idx], FMT_FORM);

        putchar('\n');

        // Prompting user for confirmation.
        // Validating.
        printf("Are you sure you want to remove this patient record? (y/n): ");
        userOption = inputCharOption("yn");

        // Removing record/cancelling operation.
        if (userOption == 'n')
        {
            printf("Operation aborted.\n\n");
        }
        else
        {
            // Assigning the patient to be removed to an empty version.
            patient[idx] = empty;
            printf("Patient record has been removed!\n\n");
        }
    }
    // Displaying error message for non-existing patient.
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


void selectionSort(struct Appointment appoints[], int max)
{
    int calcIdx, iterIdx, tstMembIdx, curMinIdx;
    struct Appointment tempVal = { 0 };

    // Calculating for total minutes stored to get a single value to be sorted.
    for (calcIdx = 0; calcIdx < max; calcIdx++)
    {
        appoints[calcIdx].time.min =
            (appoints[calcIdx].date.year * 12 * 30 * 24 * 60) +
            (appoints[calcIdx].date.month * 30 * 24 * 60) +
            (appoints[calcIdx].date.day * 24 * 60) +
            (appoints[calcIdx].time.hour * 60) +
            appoints[calcIdx].time.min;
    }

    // Sorting elements by selection (comparing indexes and values).
    for (iterIdx = 0; iterIdx < max; iterIdx++)
    {
        curMinIdx = iterIdx;

        for (tstMembIdx = iterIdx + 1; tstMembIdx < max; tstMembIdx++)
        {
            // Checking if the test member is less than the lowest value.
            if (appoints[tstMembIdx].time.min < appoints[curMinIdx].time.min)
            {
                // Assigning the next lowest value.
                curMinIdx = tstMembIdx;
            }
        }

        // Swapping members.
        if (curMinIdx != iterIdx)
        {
            tempVal = appoints[iterIdx];
            appoints[iterIdx] = appoints[curMinIdx];
            appoints[curMinIdx] = tempVal;
        }

    }

    // Calculating the minutes back to original display (reverse operation).
    for (calcIdx = 0; calcIdx < max; calcIdx++)
    {
        appoints[calcIdx].time.min =
            appoints[calcIdx].time.min -
            (appoints[calcIdx].date.year * 12 * 30 * 24 * 60) -
            (appoints[calcIdx].date.month * 30 * 24 * 60) -
            (appoints[calcIdx].date.day * 24 * 60) -
            (appoints[calcIdx].time.hour * 60);
    }
}


void viewAllAppointments(struct ClinicInfo* data)
{
    int i, j;

    // Sorting appointments ascending by selection sort.
    selectionSort(data->appointments, data->maxAppointments);

    // Displaying the heather.
    displayScheduleTableHead(NULL, 1);

    // Iterating the records.
    for (i = 0; i < data->maxAppointments; i++) 
    {
        // Iterating the fields.
        for (j = 0; j < data->maxPatient; j++) 
        {
            // Checking for existing appointments.
            if (data->appointments[i].patientNumber && 
                data->patients[j].patientNumber) 
            {
                // Displaying data for each client.
                if (data->appointments[i].patientNumber == 
                    data->patients[j].patientNumber) 
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }
    }

    putchar('\n');
}


void viewAppointmentSchedule(struct ClinicInfo* data)
{
    int i, j;
    struct Date date = { 0 }; 

    // Prompting user for date inputs.
    date = inputDate();

    putchar('\n');

    // Sorting appointments ascending by selection sort.
    selectionSort(data->appointments, data->maxAppointments);

    // Displaying the table heather.
    displayScheduleTableHead(&date, 0);

    // Iterating the records.
    for (i = 0; i < data->maxAppointments; i++) 
    {
        // Iterating the fields.
        for (j = 0; j < data->maxPatient; j++) 
        {
            // Checking for existing appointments within records and fields.
            if (data->appointments[i].patientNumber && 
                data->patients[j].patientNumber) 
            {
                if (data->appointments[i].patientNumber == 
                    data->patients[j].patientNumber) 
                {
                    // Checking for a match for the query.
                    if (data->appointments[i].date.year == date.year && 
                        data->appointments[i].date.month == date.month && 
                        data->appointments[i].date.day == date.day) 
                    {
                        // Displaying data for the client (if found).
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }

    putchar('\n');
}


void addAppointment(struct Appointment* appoints, int maxApp, 
    struct Patient* patients, int maxPt)
{
    struct Date tempDate = { 0 };
    struct Time tempTime = { 0 };

    int patientNum, patientIdx, 
        slotAvailable = 0;

    // Prompting user for patient number.
    printf("Patient Number: ");
    patientNum = inputIntPositive();

    // Assigning patient index to the index found (if any).
    patientIdx = findPatientIndexByPatientNum(patientNum, patients, maxPt);

    if (patientIdx != -1)
    {
        while (!slotAvailable)
        {
            // Prompting user for date inputs.
            tempDate = inputDate();

            // Getting input for time.
            do {
                printf("Hour (0-23)  : ");
                tempTime.hour = inputIntRange(0, 23);

                printf("Minute (0-59): ");
                tempTime.min = inputIntRange(0, 59);

                // Checking for availability (timeslots).
                if (appointNotAvailable(tempDate, tempTime, appoints, maxApp))
                {
                    putchar('\n');

                    printf("ERROR: Appointment timeslot is not available!\n\n");
                }
                // Checking for hour and minute intervals.
                else
                {
                    if ((tempTime.hour < START_HOUR ||
                        tempTime.hour > END_HOUR) ||
                        (tempTime.hour == END_HOUR && tempTime.min > 0) ||
                        (tempTime.min % MIN_INTERVAL != 0))
                    {
                        printf("ERROR: Time must be between %02d:00 and %02d:00"
                            " in %02d minute intervals.\n\n", 
                            START_HOUR, END_HOUR, MIN_INTERVAL);
                    }
                    else
                    {
                        slotAvailable = 1;
                    }
                }

            } while ((tempTime.hour < START_HOUR ||
                tempTime.hour > END_HOUR) ||
                (tempTime.hour == END_HOUR && tempTime.min > 0) ||
                (tempTime.min % MIN_INTERVAL != 0));
        }

        putchar('\n');

        // Setting the next time window available.
        patientIdx = nextAvailableSchedule(appoints, maxApp);

        appoints[patientIdx].patientNumber = patientNum;
        appoints[patientIdx].date = tempDate;
        appoints[patientIdx].time = tempTime;

        // Displaying confirmation message to user.
        printf("*** Appointment scheduled! ***\n\n");
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


void removeAppointment(struct Appointment* appoints, int maxApp, 
    struct Patient* patients, int maxPt)
{
    struct Date tempDate = { 0 };
    struct Appointment empty = { 0 };

    int i, patientNum, patientIdx,
        appointmentIdx, appointValid = 0;

    // Prompting user for patient number.
    printf("Patient Number: ");
    patientNum = inputIntPositive();

    // Assigning patient index to the index found (if any).
    patientIdx = findPatientIndexByPatientNum(patientNum, patients, maxPt);

    // Checking for matching patient index.
    if (patientIdx != -1)
    {
        // Prompting user for date inputs.
        tempDate = inputDate();

        // Checking for valid appointment.
        i = 0;
        while (appointValid == 0 && i < maxApp)
        {
            if ((appoints[i].patientNumber == patientNum) && 
                (appoints[i].date.day == tempDate.day) && 
                (appoints[i].date.month == tempDate.month) && 
                (appoints[i].date.year == tempDate.year)) 
            {
                appointValid = 1;
            }

            i++;
        }

        // Assigning appointment index.
        // Checking for a valid index.
        appointmentIdx = i - 1;

        if (appointmentIdx > -1) 
        {
            // Displaying patient data and prompting user to complete the operation.
            putchar('\n');

            displayPatientData(&patients[patientIdx], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') 
            {
                appoints[appointmentIdx] = empty;
                printf("\nAppointment record has been removed!\n\n");
            }
            else 
            {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else 
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// Utility functions.

// Checks for the time availability for an appointment 
// (returns 1 if there are no time slots available).
int appointNotAvailable(struct Date date, struct Time time,
    struct Appointment* appoints, int maxApp) 
{
    int i, notAvailable = 0;

    // Iterating for not available times for appointments.
    for (i = 0; i < maxApp; i++)
    {
        if (date.year == appoints[i].date.year &&
            date.month == appoints[i].date.month &&
            date.day == appoints[i].date.day &&
            time.hour == appoints[i].time.hour &&
            time.min == appoints[i].time.min)
        {
            notAvailable = 1;
        }
    }

    // Returning the result (0 = FALSE, 1 = TRUE).
    return notAvailable;
}

// Checks for the next time window available (NOT MANDATORY FUNCTION). 
// (returns the free appointment index).
int nextAvailableSchedule(struct Appointment* appoints, int maxApp)
{
    int i, available = 0;

    // Iterating for empty patient slots.
    i = 0;
    while (available == 0 && i < maxApp) 
    {
        if (appoints[i].patientNumber < 1) 
        {
            available = 1;
        }

        i++;
    }

    // Returning the empty slot index.
    return i;
}

// Finds the last day of a given month and return it as an int.
int getFinalDay(int month, int year)
{
    int finalDay;

    // Checking for:
    // April, September, and November (30 days);
    // February in a leap year (29 days);
    // February in a regular year (28 days);
    // Every other month (31 days).
    switch (month)
    {
    case 4 || 9 || 11:
        finalDay = 30;
        break;
    case 2:
        if (year % 4 == 0)
        {
            finalDay = 29;
        }

        else
        {
            finalDay = 28;
        }
        break;

    default:
        finalDay = 31;
    }

    // Returning int value for total # of days.
    return finalDay;
}

// Get user input for date (year, month, day).
struct Date inputDate(void)
{
    struct Date date = { 0 };
    
    int finalDay;
    
    // Prompting user for the year input.
    // Getting input.
    printf("Year        : ");
    date.year = inputIntPositive();

    // Prompting user for the month input.
    // Getting input.
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    // Prompting user for the day input.
    printf("Day (1-");

    // Checking for appropriate final day count for the chosen month.
    finalDay = getFinalDay(date.month, date.year);

    // Getting input.
    printf("%d)  : ", finalDay);
    date.day = inputIntRange(1, finalDay);

    return date;
}


void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int userInput, idx;

    // Displaying prompt for user input.
    // Getting user input.
    printf("Search by patient number: ");
    userInput = inputIntPositive();

    putchar('\n');

    // Assigning the patient index.
    idx = findPatientIndexByPatientNum(userInput, patient, max);

    // Looking for patient (validation flag).
    if (idx != -1)
    {
        displayPatientData(&patient[idx], FMT_FORM);
        putchar('\n');
    }
    else
    {
        printf("*** No records found ***\n\n");
    }
}


void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char userInput[PHONE_LEN + 1] = { '\0' };
    int i, foundMatch = 0;

    // Displaying prompt for user input.
    printf("Search by phone number: ");
    inputCString(userInput, PHONE_LEN, PHONE_LEN);

    putchar('\n');

    displayPatientTableHead();

    // Looking for patient (validation flag).
    for (i = 0; i < max; i++)
    {
        if (!(strcmp(patient[i].phone.number, userInput)))
        {
            foundMatch = 1;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }

    putchar('\n');

    if (!(foundMatch))
    {
        printf("*** No records found ***\n\n");
    }
}


int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, nextNum, largestNum;

    // Setting the largest number to the first element.
    largestNum = patient[0].patientNumber;

    // Looking for the actual (current) largest number.
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > largestNum)
        {
            largestNum = patient[i].patientNumber;
        }
    }

    // Assigning the next number adding one to the current largest number.
    nextNum = largestNum + 1;

    // Returning the next number.
    return nextNum;
}


int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i, patientFound = 0, result;

    // Looking for a matching patient number in the array (using flag).
    for (i = 0; i < max && !(patientFound); i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            patientFound = 1;
        }
    }

    // Returning -1 (not found).
    if (!patientFound)
    {
        result = -1;
    }
    // Returning the index (found).
    else
    {
        result = i - 1;
    }

    return result;
}


// Input functions.

void inputPatient(struct Patient* patient)
{
    // Displaying the user input prompt.
    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n", patient->patientNumber);
    printf("Name  : ");

    // Getting the input for the name of the patient to be added.
    inputCString(patient->name, 0, NAME_LEN);

    putchar('\n');

    // Getting the input for the phone number.
    inputPhoneData(&patient->phone);
}


void inputPhoneData(struct Phone* phone)
{
    char strContact[PHONE_DESC_LEN + 1] = { '\0' };
    int userInput, tbd = 0;

    // Displaying selection menu.
    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");

    // Getting input from the user (allowed from 1 up to 4).
    userInput = inputIntRange(1, 4);

    putchar('\n');

    // Selecting phone description to user's profile.
    switch (userInput)
    {
    case 1:
        strcpy(strContact, "CELL");
        break;
    case 2:
        strcpy(strContact, "HOME");
        break;
    case 3:
        strcpy(strContact, "WORK");
        break;
    case 4:
        strcpy(strContact, "TBD");
        tbd = 1;
        break;
    }

    // Assigning description.
    strncpy(phone->description, strContact, PHONE_DESC_LEN + 1);

    // Getting input from user for the telephone number.
    if (!tbd)
    {
        printf("Contact: %s\n", phone->description);

        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);

        putchar('\n');
    }
    // Setting phone number to a safe empty space.
    else
    {
        *phone->number = 0;
    }
}


// File functions.

int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0, result = 0;

    // Declaring and assigning file pointer to a safe memory space.
    FILE* fp = NULL;

    // Opening file for reading.
    fp = fopen(datafile, "r");

    // Reading records with the correct format, until EOF.
    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]",
            &patients[i].patientNumber,
            patients[i].name,
            patients[i].phone.description,
            patients[i].phone.number) != EOF)
        {
            i++;
        }

        // Closing file.
        fclose(fp);
        fp = NULL;

        // Assigning number of records to result.
        result = i;
    }
    // Error message.
    else
    {
        puts("ERROR: unable to access file!\n");
    }

    return result;
}


int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0, result = 0;

    // Declaring and assigning file pointer to a safe memory space.
    FILE* fp = NULL;

    // Opening file for reading.
    fp = fopen(datafile, "r");

    // Reading records with the correct format, until EOF.
    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d",
            &appoints[i].patientNumber,
            &appoints[i].date.year,
            &appoints[i].date.month,
            &appoints[i].date.day,
            &appoints[i].time.hour,
            &appoints[i].time.min) != EOF)
        {
            i++;
        }

        // Closing file.
        fclose(fp);
        fp = NULL;

        // Assigning number of records to result.
        result = i;
    }
    // Error message.
    else
    {
        puts("ERROR: unable to access file!\n");
    }

    return result;
}