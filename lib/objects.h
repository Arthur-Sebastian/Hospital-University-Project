/*
	HOSPITAL PROJECT
(C) Arthur Sebastian Miller 2021
       object header file
*/

#ifndef OBJECTS_H
#define OBJECTS_H

#include <iostream>
#include <string>
#include <list>
#include <iterator>

/*
Comment the define below to disable
debug message feature.
*/
#define debug_msg

class person;
class staffmember;
class patient;
class room;
class hospital;

/*
Base class used for inheritance for
patient and staffmember classes.

Should not be used on it's own as it
does not include a constructor. Doing
so will result in a segmentation fault.
*/
class person
{

public:
	/*
	This method attempts to set a name and surname for
	the person in question. Returns false without changes
	if:
	- name and/or surname are empty strings
	*/
	bool setName(std::string namestr, std::string surnamestr); //DONE
	/*
	Returns a name string copy.
	*/
	std::string getName() const; //DONE
	/*
	Returns a string containing surname.
	*/
	std::string getSurname() const; //DONE
	/*
	Sets the age. Fails if age is outside the
	[0;200] range.
	*/
	bool setAge(int agecount); //DONE
	/*
	Returns an integer copy of person's age.
	*/
	int getAge() const; //DONE
	/*
	This method checks if person does not
	have an assigned name or surname. Such 
	person is considered invalid for linkage.
	*/
	bool isValid() const; //DONE
	
protected:
	std::string name;
	std::string surname;
	int age;

};

/*
A staffmember class represents a medical worker
with a specified profession. Inherits data and
member methods from class person.
*/
class staffmember : public person
{

/*
This overload will output a shortened summary of staff member data.
*/
friend std::ostream& operator<< (std::ostream& str, const staffmember& stm); //DONE

public:
	/*
	This destructor unlinks the staffmember from any other
	object.
	*/
	~staffmember();
	/*
	Compares name and surname. If both match, returns
	true.
	*/
	bool operator==(const staffmember& ref) const;
	/*
	Initialises pointers to null, sets name, surname
	and age to avoid segmentation faults.
	*/
	staffmember(std::string namestr, std::string surnamestr, int age); //DONE
	/*
	Sets name and surname for staffmember.
	Returns false without changes
	if:
	- base class method setName fails
	- staffmember has any linkage to any other object 
	  (removes possible unique name check bypass)
	*/
	bool setName(std::string namestr, std::string surnamestr); //DONE
	/*
	Sets staff type. Fails if provided string is empty.
	*/
	bool setType(std::string typestr); //DONE
	/*
	This method returns a profession string
	of the staff member.
	*/
	std::string getType() const; //DONE
	/*
	Sets the link to indicate staff as working
	in a specified hospital. Returns false if:
	- staffmember does not have a name
	- staffmember does not have a profession
	- staffmember already has a hospital assignment
	*/
	bool linkToHospital(const hospital& hosp); //DONE
	/* 
	This method clears the link of a staffmember
	to a hospital. Returns false if:
	- link has not been cleared by hospital first
	- no link is present
	*/
	bool unlinkFromHospital(); //DONE
	/*
	Returns a reference to the hospital staffmember
	is in. If no link is present returns an empty 
	object reference.
	*/
	hospital& getHospital() const; //DONE
	/*
	Links the staffmember to the selected 
	room one-way. Returns false if:
	- person has an empty name
	- person already has a room assigned
	*/
	bool linkToRoom(const room& rm); //DONE
	/* 
	Removes a link to a room. Returns false if:
	- link has not been cleared by room first
	- no link is present
	*/
	bool unlinkFromRoom(); //DONE
	/*
	Returns a reference to the room the staff
	is working in.
	*/
	room& getRoom() const; //DONE

private:
	//a description of staffmember's job
	std::string stafftype;
	//a pointer to a hospital the person is in
	hospital* in_hospital;
	//a pointer to a room the person is in
	room* in_room;
	
};

/*
A patient class represents a medical patient
with a specified illness. Inherits data and
member methods from class person.
*/
class patient : public person
{

/*
This overload will output a shortened summary of patient data.	
*/
friend std::ostream& operator<< (std::ostream& str, const patient& ptn); //DONE

public:
	/*
	This destructor unlinks the patient from any other
	object types.
	*/
	~patient();
	/*
	Compares name and surname. If both match, returns
	true.
	*/
	bool operator==(const patient& ref) const;
	/*
	Initialises pointers to null, sets name, surname
	and age to avoid segmentation faults.
	*/
	patient(std::string namestr, std::string surnamestr, int age); //DONE
	/*
	Sets name and surname for patient.
	Returns false without changes
	if:
	- base class method setName fails
	- patient has any linkage to any other object 
	  (removes possible unique name check bypass)
	*/
	bool setName(std::string namestr, std::string surnamestr); //DONE
	/*
	Sets patient's condition. Fails if provided string is empty.
	*/
	bool setCondition(std::string conditionstr); //DONE
	/*
	Removes patient's condition, setting it to empty
	string. Patient without condition is condsidered
	healthy.
	*/
	void removeCondition(); //DONE
	/*
	Returns a string indicating an illness of the
	patient.
	*/
	std::string getCondition() const; //DONE
	/*
	Sets the link to indicate patient as treated
	in a specified hospital. Returns false if:
	- hospital did not create the link first
	- patient does not have a name
	- patient already has a hospital assignment
	*/
	bool linkToHospital(const hospital& hosp); //DONE
	/* 
	This method clears the link of a patient
	to a hospital. Returns false if:
	- link has not been cleared by hospital first
	- no link is present
	*/
	bool unlinkFromHospital(); //DONE
	/*
	Returns a reference to the hospital patient
	is in. If no link is present returns an empty 
	object reference.
	*/
	hospital& getHospital() const; //DONE
	/*
	Links a patient to the selected room 
	one-way. Returns false if:
	- room did not create the link first
	- person has an empty name
	- person already has a room assigned
	*/
	bool linkToRoom(const room& rm); //DONE
	/* 
	Removes a link to a room. Returns false if:
	- link has not been cleared by room first
	- no link is present
	*/
	bool unlinkFromRoom(); //DONE
	/*
	Returns a reference to the room the patient
	is treated in.
	*/
	room& getRoom() const; //DONE

private:
	//a description of a patient's illness
	std::string condition;
	//a pointer to a hospital the person is in
	hospital* in_hospital;
	//a pointer to a room the person is in
	room* in_room;

};

/*
A room class represents a treatment room
where patients are treated, kept under
medical supervision, etc. depending on
the type of use case. Room can be treated
as a small list of patients under a certain
name. Room also has a designated caretaker,
and a link to a specified hospital.
*/
class room
{

/*
This overload will output a shortened summary of room data.	
*/
friend std::ostream& operator<<(std::ostream& str, const room& rm);

public:
	/*
	Preinitialises pointers to null, and
	sets the name of the room.
	*/
	room(std::string rmnm); //DONE
	/*
	Removes all linkage of to object to anything
	else during destruction.
	*/
	~room();
	/*
	Sets a name for the room. 
	Returns false without changes if:
	- provided name string is empty
	- room is linked to a hospital
	  (removes possible unique name check bypass)
	*/
	bool setName(std::string rmnm); //DONE
	/*
	This method returns a copy of the room
	name.
	*/
	std::string getName() const; //DONE
	/*
	This method attempts to add a patient into
	the room. Method will return false if:
	- room does not have a name
	- patient already appears in the room
	- link fails from patient side (see patient::linkToRoom)
	*/
	bool addPatient(patient& ptn); //DONE
	/*
	Clears a mutual link between a patient and a room.
	Returns false if no link exists.
	*/
	bool removePatient(patient& ptn); //DONE
	/*
	Prints a list of patients currently in a
	given room. If a room is empty, an
	appropriate message is displayed.
	*/
	void printPatients() const; //DONE
	/*
	This method searches for a patient with a given name
	and returns a reference if it exists. If no patient
	is found, the method returns a reference to a static
	empty object.
	*/
	patient& getPatient(std::string nmstr, std::string snstr) const; //DONE
	/*
	This method attempts to assign a staff
	member to caretaker role of the room.
	Returns false if:
	- room does not have a name
	- any staffmember already appears in the room
	- staffmember refused the link from its side 
	  (see staffmember::linkToRoom)
	*/
	bool linkStaff(staffmember& stm); //DONE
	/*
	Clears the link between staffmember and a room.
	Returns false if no link is present.
	*/
	bool unlinkStaff(); //DONE
	/*
	Returns a reference to a staffmember
	assigned to the room. If no staff is assigned,
	the method returns a reference to a static empty object.
	*/
	staffmember& getStaff() const; //DONE
	/*
	This method attempts to link a specified room
	to a preexisting hospital one-way. 
	Returns false if:
	- hospital did not create its link first
	- room does not have a name
	- room already has a hospital linked
	*/
	bool linkToHospital(const hospital& hosp); //DONE
	/* 
	Clears the link of the room to a hospital,
	returns false if:
	- hospital did not unlink itself first
	- no link is present
	*/
	bool unlinkFromHospital(); //DONE
	/*
	Returns a reference to a hospital the room is
	in, if no link is present returns static empty
	object.
	*/
	hospital& getHospital() const; //DONE
	/*
	Checks if a room has an assigned name. 
	Room without a name is considered
	invalid for linkage operations.
	*/
	bool isValid() const; //DONE
	
private:
	//a room description e.g. "recovery ward 21"
	std::string name;
	//a staff member, in charge of the room
	staffmember* assignee;
	//a pointer to the hospital room is located in
	hospital* in_hospital;
	//beginning of the patient list in a given room
	std::list <patient*> patients;

};

/*
A hospital class represents an instance of
a selected medical facility. Unifies lists.
*/
class hospital
{

//displays a hospital name
friend std::ostream& operator<<(std::ostream& str, const hospital& hosp);

public:
	/*
	Sets the name of the hospital.
	*/
	hospital(std::string hsnm); //DONE
	/*
	Removes all the linkage of the hospital
	to any other object, both ways, to avoid
	freed pointer access by objects.
	*/
	~hospital();
	/*
	Sets a name of the hospital, returns without
	changes if provided string is empty.
	*/
	bool setName(std::string hsnm); //DONE
	/*
	Returns a copy of a hospital name.
	*/
	std::string getName() const; //DONE
	/*
	This method attempts to register a patient
	object and add it into patient list.
	Method returns false if:
	- patient refuses the link (see patient::linkToHospital)
	- hospital does not have a name
	- patient already exists on patient list
	*/
	bool registerPatient(patient& ptn); //DONE
	/*
	Removes the patient from the hospital, terminating
	the mutual link both ways. Returns false if no link
	is present.
	*/
	bool dischargePatient(patient& ptn); //DONE
	/*
	This method displays a list of the patient data.
	If a patient does not have a illness, it is displayed
	as healthy. If search for a patient is unsuccessful,
	the method displays a message that the patient was 
	not found.
	*/
	void printPatients() const; //DONE
	/*
	Method for searching for patient objects and returning their references.
	Returns constant empty object reference on failure.
	*/
	patient& getPatient(std::string nmstr, std::string snstr) const; //DONE
	/*
	This method attempts to add a staff memeber.
	Method fails if:
	- staffmember refuses the link (see staffmember::linkToHospital)
	- hospital does not have a name
	- staffmemeber is already employed in this hospital
	*/
	bool employStaff(staffmember& stm); //DONE
	/*
	Removes a mutual link to a staff member, returns
	false if no such link is present.
	*/
	bool dismissStaff(staffmember& stm); //DONE
	/*
	Displays a list of staff currently in the hospital, 
	their rooms, along with their profession. 
	If there's no staff, displays appropriate message.
	*/
	void printStaff() const; //DONE
	/*
	Method for searching for staff objects and returning their references.
	Returns constant empty object reference on failure.
	*/
	staffmember& getStaff(std::string namestr, std::string surnamestr) const; //DONE
	/*
	This method attempts to incorporate a room
	into the hospital. Returns false if:
	- room refuses to be linked (see room::linkToHospital)
	- hospital does not have a name
	- room with the same name already exists
	*/
	bool addRoom(room& rm);
	/*
	Removes the mutual link to a room unless
	no such link exists. In this case returns false.
	*/
	bool removeRoom(room& rm);
	/*
	Displays a list of rooms in the hospital. 
	If there's no rooms, displays an apropriate 
	message.
	*/
	void printRooms() const;
	/*
	Searches for room objects and returns their references.
	Returns constant empty object reference on failure.
	*/
	room& getRoom(std::string nmstr) const;
	/*
	Displays the count of staff members,
	registered patients and amount of rooms in the hospital.
	*/
	void printStatus() const;
	/*
	Checks if a hospital does not have a name. 
	Such a hospital is considered invalid 
	for linkage operations.
	*/
	bool isValid() const; //DONE
	

private:
	//string descirbing hospital name
	std::string name;
	//list of pointers to staff members
	std::list <staffmember*> stafflist;
	//list of pointers to rooms in the hospital
	std::list <room*> roomlist;
	//list of pointers to registered patients
	std::list <patient*> patients;

};

#endif
