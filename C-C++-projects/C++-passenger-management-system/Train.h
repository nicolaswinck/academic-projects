#ifndef TRAIN_H_
#define TRAIN_H_

#define MIN_TIME 700
#define MAX_TIME 2300
#define MAX_NO_OF_PASSENGERS 1000

class Train
{
	char* trainName;
	int passengerNum;
	int departTime;

public:
	void initialize();
	bool validTime(int value) const;
	bool validNoOfPassengers(int value) const;
	bool load(int& unboarded);
	bool updateDepartureTime();
	void set(const char* name);
	void set(int noOfPassengers, int departure);
	void set(const char* name, int noOfPassengers, int departure);
	void finalize();
	bool isInvalid()const;
	int noOfPassengers() const;
	const char* getName() const;
	int getDepartureTime() const;
	void display() const;
	bool transfer(const Train& train);
};

#endif // !TRAIN_H_