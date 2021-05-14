/*
	HOSPITAL PROJECT
(C) Arthur Sebastian Miller 2021
    unit testing source file
*/

#include "unit_tests.h"

using namespace std;

void testRoutine()
{

	cout << "[testRoutine():][Creating class objects...]" << endl;

	staffmember staff1("Alexander", "White", 44);
	staff1.setType("surgeon");
	staffmember staff2("Julia", "MacDonald", 35);
	staff2.setType("nurse");
	staffmember staff3("", "",0);
	patient pat1("Mark", "Blair", 31);
	pat1.setCondition("hemorrhage");
	patient pat2("Betty", "Smith", 67);
	pat2.setCondition("hyponatremia");
	patient pat3("Jason", "Bird", 34);
	pat3.setCondition("poisoning");
	patient pat4("Jenny", "Portman", 53);
	pat3.setCondition("fracture");
	patient pat5("", "", 0);
	pat5.setCondition("stroke");
	room ward1("surgical");
	room ward2("observation");
	room ward3("");
	hospital hospital1("St. Mark's general");
	hospital hospital3("TestHospital");
	hospital hospital2("");

	cout << staff1 << endl;
	cout << staff2 << endl;
	cout << staff3 << endl;
	cout << pat1 << endl;
	cout << pat2 << endl;
	cout << pat3 << endl;
	cout << pat4 << endl;
	cout << pat5 << endl;
	cout << ward1 << endl;
	cout << ward2 << endl;
	cout << ward3 << endl;
	cout << hospital1 << endl;
	cout << hospital3 << endl;
	cout << hospital2 << endl;
	

	cout << "\n[testRoutine()][Testing class person:]" << endl;

	staff1.setName("", ""); //wrong, empty string
	cout << staff1.setName("Bob", "Ross") << endl; //ok
	cout << staff1.getName() << endl; //ok
	cout << staff1.getSurname() << endl; //ok
	staff1.setAge(250); //wrong, >200
	staff1.setAge(-30); //wrong, <0
	cout << staff1.getAge() << endl; //ok
	cout << staff1.setAge(90) << endl; //ok

	cout << "\n[testRoutine()][Testing class staffmember:]" << endl;

	cout << staff1 << endl; //ok
	cout << staff1.getType() << endl; //ok
	staff1.setType(""); //wrong, empty string
	cout << staff1.setType("janitor") << endl; //ok
	staff1.linkToHospital(hospital1); //wrong, one-way link
	staff1.linkToRoom(ward1); //wrong, one-way link
	cout << staff1 << endl; //ok

	cout << "\n[testRoutine()][Testing class patient:]" << endl;

	cout << pat1 << endl; //ok
	cout << pat1.getCondition() << endl; //ok
	pat1.setCondition(""); //wrong, empty string
	cout << pat1.setCondition("dehydration") << endl; //ok
	pat1.linkToHospital(hospital1); //wrong, one-way link
	pat1.linkToRoom(ward1); //wrong, one-way link
	cout << pat1 << endl; //ok

	cout << "\n[testRoutine()][Testing class room:]" << endl;

	ward1.setName(""); //wrong, empty string
	cout << ward1.setName("TestRoom") << endl; //ok
	cout << ward1.getName() << endl; //ok
	ward1.linkToHospital(hospital1); //wrong, one-way link

	cout << "\n[testRoutine()][Testing room -> patient link:]" << endl;

	cout << ward1.addPatient(pat1) << endl; //ok
	ward3.addPatient(pat2); //wrong, unnamed room
	ward1.addPatient(pat1); //wrong, already has this patient
	ward1.addPatient(pat5); //wrong, unnamed patient
	ward2.addPatient(pat1); //wrong, patient has other room
	cout << ward1.addPatient(pat2) << endl; //ok
	cout << ward1.removePatient(pat1) << endl; //ok
	ward1.removePatient(pat1); //wrong, patient isn't in the room
	cout << ward1.removePatient(ward1.getPatient("Betty", "Smith")) << endl; //ok
	ward1.addPatient(pat1);
	ward1.addPatient(pat2);
	ward1.addPatient(pat3);
	ward1.addPatient(pat4);
	
	cout << "\n[testRoutine()][Testing room printing functions:]" << endl;
	
	ward1.printPatients(); //ok
	ward2.printPatients(); //ok
	cout << ward1 << endl; //ok
	ward1.linkStaff(staff1); //ok
	cout << ward1 << endl; //ok
	ward1.unlinkStaff(); //ok
	cout << endl;

	cout << "\n[testRoutine()][Testing room -> staff link:]" << endl;

	cout << staff1 << endl;
	cout << ward1.linkStaff(staff1) << endl; //ok
	staff1.setName("a","b"); //wrong, object is linked
	ward3.linkStaff(staff2); //wrong, unnamed room
	ward1.linkStaff(staff1); //wrong, already has staff
	ward2.linkStaff(staff3); //wrong, unnamed staff
	ward2.linkStaff(staff1); //wrong, staff has other room
	cout << ward2.linkStaff(staff2) << endl; //ok
	cout << ward1.getStaff() << endl; //ok
	cout << ward2.getStaff() << endl; //ok
	cout << ward1.unlinkStaff() << endl; //ok
	ward1.unlinkStaff(); //wrong, room does not have staff

	cout << "\n[testRoutine()][Testing class hospital:]" << endl;

	cout << hospital1.getName() << endl; //ok
	hospital1.setName(""); //wrong, empty string
	cout << hospital1.setName("St. Patrick's psychiatric") << endl; //ok
	cout << hospital1.getName() << endl; //ok

	cout << "\n[testRoutine()][Testing hospital -> patient link:]" << endl;

	cout << hospital1.registerPatient(pat1) << endl; //ok
	hospital1.registerPatient(pat1); //wrong, already on list
	cout << hospital3.registerPatient(pat2) << endl; //ok
	hospital1.registerPatient(pat2); //wrong, already in other hospital
	hospital1.registerPatient(pat5); //wrong, unnamed patient
	cout << hospital1.registerPatient(pat3) << endl; //ok
	cout << hospital1.dischargePatient(pat3) << endl; //ok
	hospital1.dischargePatient(pat3); //wrong, patient already discharged
	hospital1.printPatients(); //ok

	cout << "\n[testRoutine()][Testing hospital -> staff link:]" << endl;

	cout << hospital1.employStaff(staff1) << endl; //ok
	hospital1.employStaff(staff1); //wrong, already on the list
	hospital1.employStaff(staff3); //wrong, unnamed staff
	cout << hospital3.employStaff(staff2) << endl; //ok
	hospital1.employStaff(staff2); //wrong, already in another hospital
	cout << hospital1.dismissStaff(staff1) << endl; //ok
	hospital1.dismissStaff(staff1); //wrong, staff already dismissed
	hospital1.printStaff(); //empty list, but ok
	hospital1.employStaff(staff1); //ok
	hospital3.dismissStaff(staff2); //ok 
	hospital1.employStaff(staff2); //ok
	hospital1.printStaff(); //ok
	cout << hospital1.getStaff("Julia", "MacDonald") << endl; //ok

	cout << "\n[testRoutine()][Testing hospital -> room link:]" << endl;

	cout << hospital1.addRoom(ward1) << endl; //ok
	ward1.setName("a"); //wrong, object has linkage
	hospital1.addRoom(ward1); //wrong, room already exists
	hospital1.addRoom(ward3); //wrong, unnamed room
	cout << hospital3.addRoom(ward2) << endl; //ok
	hospital1.addRoom(ward2); //wrong, room already has hospital
	hospital1.printRooms(); //ok
	cout << hospital1.removeRoom(hospital1.getRoom("TestRoom")) << endl; //ok
	hospital1.removeRoom(hospital1.getRoom("TestRoom")); //wrong, room removed already
	hospital1.getRoom(""); //wrong, should return reference to empty room

	cout << "\n[testRoutine()][Testing hospital status counter:]" << endl;
	
	hospital1.printStatus(); //ok
	hospital1.printRooms(); //ok
	hospital3.printStatus(); //ok
	hospital3.printRooms(); //ok
	
	cout << "\n[testRoutine()][Dynamic memory + destructor test:]" << endl;
	
	staffmember* dyns1 = new staffmember("Dylan","Mackintosh",14);
	dyns1 -> setType("physycian's kid");
	staffmember* dyns2 = new staffmember("Sylvia","Stout",27);
	dyns2 -> setType("nurse");
	patient* dynp1 = new patient("Dr","Jeckyll",20);
	patient* dynp2 = new patient("Alexander","Jaw",22);
	patient* dynp3 = new patient("Mr","Hyde",44);
	room* dynr1 = new room("testing chamber");
	room* dynr2 = new room("testing hall");
	hospital* dynh1 = new hospital("testing building");
	
	dynr1 -> linkStaff(*dyns1);
	dynr1 -> addPatient(*dynp1);
	dynh1 -> addRoom(*dynr1);
	cout << *dynr1 << endl;
	cout << *dyns1 << endl;
	cout << *dynp1 << endl;
	dynh1 -> printRooms();
	cout << "Deleting room " << dynr1 -> getName() << endl;
	delete dynr1;
	cout << *dyns1 << endl;
	cout << *dynp1 << endl;
	cout << *dynh1 << endl;
	dynh1 -> printRooms();
	
	dynr2 -> linkStaff(*dyns1);
	dynr2 -> addPatient(*dynp1);
	dynh1 -> employStaff(*dyns1);
	dynh1 -> registerPatient(*dynp1);
	dynh1 -> addRoom(*dynr2);
	dynh1 -> printStaff();
	cout << "Deleting staffmember " << dyns1 -> getName() << endl;
	delete dyns1;
	dynh1 -> printPatients();
	cout << "Deleting patient " << dynp1 -> getName() << endl;
	delete dynp1;
	dynh1 -> printPatients();
	cout << "Room's hospital: ";
	cout << dynr2 -> getHospital() << endl;
	cout << "Deleting hospital " << dynh1 -> getName() << endl;
	delete dynh1;
	cout << "Room's hospital post-deletion: ";
	cout << dynr2 -> getHospital() << endl;
	
	
	cout << "\n[Dynamic memory + destructor test finished!]" << endl;

}
