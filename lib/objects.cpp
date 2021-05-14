/*
	HOSPITAL PROJECT
(C) Arthur Sebastian Miller 2021
       object source file
*/

#include "objects.h"

#ifdef debug_msg
#define debug(method, message) std::cerr << #method << ": " << #message << "!\n"
#else
#define debug(method, message)
#endif

patient empty_patient("","",0);
staffmember empty_staff("","",0);
room empty_room("");
hospital empty_hospital("");

/*

[][][][][!] CLASS PERSON [!][][][][]

*/

bool person::setName(std::string namestr, std::string surnamestr)
{
	//check if given name or surname is not empty
	if(namestr == "" || surnamestr == "")
	{
		debug(person::setName, provided name and/or surname is an empty string);
		return false;
	}
	//set values if name and surname are correct
	else
	{
		name = namestr;
		surname = surnamestr;
	}
	return true;
}

std::string person::getName() const
{
	//return a string copy
	return name;
}

std::string person::getSurname() const
{
	//return a string copy
	return surname;
}

bool person::setAge(int agecount)
{
	//check if age is in the impossible range
	if(agecount < 0 || agecount > 200)
	{
		debug(person::setAge,age was outside [0;200] range);
		return false;
	}
	//set if age is correct
	else age = agecount;
	return true;
}

int person::getAge() const
{
	//return a copy
	return age;
}

bool person::isValid() const
{
	//check if name or surname is empty
	if(name != "" && surname != "") return true;
	else return false;
}

/*

[][][][][!] CLASS STAFFMEMBER [!][][][][]

*/
std::ostream& operator<< (std::ostream& str, const staffmember& stm)
{
	str << "STAFF: ";
	//check if staff is a valid member
	if(stm.isValid())
	{
		str << stm.name << " " << stm.surname << ", " << stm.age;
		//check for profession and print if applicable
		if(stm.stafftype != "") str << " | " << stm.stafftype;
		//print out room and hospital assignments if applicable
		//uses getter methods to avoid null pointer access
		if(stm.getHospital().isValid()) str << " | " << stm.in_hospital -> getName();
		if(stm.getRoom().isValid()) str << " | " << stm.in_room -> getName();
	}
	//point out the staff is empty
	else str << "NULL";
	return str;
}

staffmember::~staffmember()
{
	//unlink any link the staff has
	if(in_room != nullptr)
		in_room -> unlinkStaff();
	if(in_hospital != nullptr)
		in_hospital -> dismissStaff(*this);
}

bool staffmember::operator==(const staffmember& ref) const
{
	//compare name strings
	return (name == ref.name && surname == ref.surname);
}

staffmember::staffmember(std::string namestr, std::string surnamestr, int age)
{
	//initialize the pointers to null for the checks
	//to avoid segmentation faults
	in_hospital = nullptr;
	in_room = nullptr;
	//fill the object with data
	name = namestr;
	surname = surnamestr;
	//if method fails, set age to 0
	if(!setAge(age)) age = 0;
}

bool staffmember::setName(std::string namestr, std::string surnamestr)
{
	//when person is linked anywhere, refuse to change name
	if(in_hospital != nullptr || in_room != nullptr)
	{
		debug(staffmember::setName, object is linked - you cannot change its name);
		return false;
	}
	return person::setName(namestr, surnamestr);
	
}

bool staffmember::setType(std::string typestr)
{
	//cannot assign empty string
	if(typestr == "")
	{
		debug(staffmember::setType, provided string is empty);
		return false;
	}
	//string is not empty, set value
	else stafftype = typestr;
	return true;
}

std::string staffmember::getType() const
{
	//return a string copy
	return stafftype;
}

bool staffmember::linkToHospital(const hospital& hosp)
{
	/*
	Lock out the possibility of one-way linking, since
	hospital calls this method after adding the patient
	to its list
	*/
	if(!hosp.getStaff(name, surname).isValid())
	{
		debug(staffmember::linkToHospital, one-way linking is forbidden);
		return false;
	}
	//check if staffmember is valid
	else if(!isValid())
	{
		debug(staffmember::linkToHospital, this staffmember does not have a name);
		return false;
	}
	//check if staff has a profession
	else if(stafftype == "")
	{
		debug(staffmember::linkToHospital, this staffmember does not have a profession);
		return false;
	}
	//person has hospital assigned already
	else if(in_hospital != nullptr)
	{
		return false;
	}
	//all basic conditions are satisfied, attempt a link
	else
	{
		//link person to hospital
		in_hospital = &((hospital&)hosp);
		debug(staffmember::linkToHospital, link confirmed);
	}
	return true;
}

bool staffmember::unlinkFromHospital()
{
	//check if a link was present
	if(in_hospital == nullptr)
	{
		debug(staffmember::unlinkFromHospital, a link is not present);
		return false;
	}
	//check if hospital cleared the link already
	else if(in_hospital -> getStaff(name, surname).isValid())
	{
		debug(staffmember::unlinkFromHospital, link has to be terminated by hospital);
		return false;
	}
	//clear the link
	else in_hospital = nullptr;
	return true;
}

hospital& staffmember::getHospital() const
{
	//return a valid reference to the hospital
	if(in_hospital != nullptr) return *in_hospital;
	//if invalid reference an empty hospital
	else return empty_hospital;
}

bool staffmember::linkToRoom(const room& rm)
{
	//first check if room added this staffmember
	if(!(rm.getStaff() == *this))
	{
		debug(staffmember::linkToRoom, one-way linking is forbidden);
		return false;
	}
	//check if person is valid
	else if(!isValid())
	{
		debug(staffmember::linkToRoom, this person is invalid);
		return false;
	}
	//check if staffmember has a room
	else if(in_room != nullptr)
	{
		debug(staffmember::linkToRoom, a link is already present);
		return false;
	}
	//conditions satisfied
	else
	{
		//link person to hospital
		in_room = &((room&)rm);
		debug(staffmember::linkToRoom, link confirmed);
	}
	return true;
}

bool staffmember::unlinkFromRoom()
{
	//check if a link was present
	if(in_room == nullptr)
	{
		debug(staffmember::unlinkFromRoom, a link is not present);
		return false;
	}
	else if(in_room -> getStaff().isValid())
	{
		debug(staffmember::unlinkFromRoom, link has to be terminated by room);
		return false;
	}
	//clear the link
	else in_room = nullptr;
	return true;
}

room& staffmember::getRoom() const
{
	//return a reference to the room
	//if not pointing to nullptr
	if(in_room != nullptr) return *in_room;
	//otherwise reference an empty room
	else return empty_room;
}

/*

[][][][][!] CLASS PATIENT [!][][][][]

*/
std::ostream& operator<< (std::ostream& str, const patient& ptn)
{
	str << "PATIENT: ";
	//check if patient is valid
	if(ptn.isValid())
	{
		str << ptn.name << " " << ptn.surname << ", " << ptn.age;
		//check for condition and print if applicable
		if(ptn.condition != "") str << " | " << ptn.condition;
		else str << " | HEALTHY";
		//print out room and hospital assignments if applicable
		//uses getters for comparison to protect against nullptr access
		if(ptn.getHospital().isValid()) str << " | " << ptn.in_hospital -> getName();
		if(ptn.getRoom().isValid()) str << " | " << ptn.in_room -> getName();
	}
	//point out the patient is invalid
	else str << "NULL";
	return str;
}

patient::~patient()
{
	//unlink any link this patient has
	if(in_room != nullptr)
		in_room -> removePatient(*this);
	if(in_hospital != nullptr)
		in_hospital -> dischargePatient(*this);
}

bool patient::operator==(const patient& ref) const
{
	//compare name strings
	return (name == ref.name && surname == ref.surname);
}

patient::patient(std::string namestr, std::string surnamestr, int age)
{
	//initialize the pointers to null for the checks
	//to avoid segmentation faults
	in_hospital = nullptr;
	in_room = nullptr;
	//fill the object with data
	name = namestr;
	surname = surnamestr;
	//if method fails, set age to 0
	if(!setAge(age)) age = 0;
}

bool patient::setName(std::string namestr, std::string surnamestr)
{
	if(in_hospital != nullptr || in_room != nullptr)
	{
		debug(patient::setName, object is linked - you cannot change its name);
		return false;
	}
	return person::setName(namestr, surnamestr);
}

bool patient::setCondition(std::string conditionstr)
{
	//check if condition is not an empty string
	if(conditionstr == "")
	{
		debug(patient::setCondition, provided string is empty);
		return false;
	}
	//assign string
	else condition = conditionstr;
	return true;
}

void patient::removeCondition()
{
	//clear the string to default value
	condition = "";
}

std::string patient::getCondition() const
{
	//return a string copy
	return condition;
}

bool patient::linkToHospital(const hospital& hosp)
{
	//lock out one way linking
	if(!(hosp.getPatient(name, surname) == *this))
	{
		debug(patient::linkToHospital, one-way linking is forbidden);
		return false;
	}
	//check if person is valid
	else if(!isValid())
	{
		debug(patient::linkToHospital, this person is invalid);
		return false;
	}
	//person has hospital assigned already
	else if(in_hospital != nullptr)
	{
		return false;
	}
	//all basic conditions are satisfied, attempt a link
	else
	{
		//link person to hospital
		in_hospital = &((hospital&)hosp);
		debug(patient::linkToHospital, link confirmed);
	}
	return true;
}

bool patient::unlinkFromHospital()
{
	//check if a link was present
	if(in_hospital == nullptr)
	{
		debug(patient::unlinkFromHospital, a link is not present);
		return false;
	}
	//check if hospital cleared the link already
	else if(in_hospital -> getPatient(name, surname).isValid())
	{
		debug(patient::unlinkFromHospital, link has to be terminated by hospital);
		return false;
	}
	//clear the link
	else in_hospital = nullptr;
	return true;
}

hospital& patient::getHospital() const
{
	//return a valid reference to the hospital
	if(in_hospital != nullptr) return *in_hospital;
	//if invalid reference an empty hospital
	else return empty_hospital;
}

bool patient::linkToRoom(const room& rm)
{
	//lock out one way linking
	if(!rm.getPatient(name, surname).isValid())
	{
		debug(patient::linkToRoom, one-way linking is forbidden);
		return false;
	}
	//check if person is valid
	if(!isValid())
	{
		debug(patient::linkToRoom, this person is invalid);
		return false;
	}
	//check if person has a room
	else if(in_room != nullptr)
	{
		debug(patient::linkToRoom, a link is already present);
		return false;
	}
	//conditions satisfied
	else
	{
		//link person to hospital
		in_room = &((room&)rm);
		debug(patient::linkToRoom, link confirmed);
	}
	return true;
}

bool patient::unlinkFromRoom()
{
	//check if a link was present
	if(in_room == nullptr)
	{
		debug(patient::unlinkFromRoom, a link is not present);
		return false;
	}
	//check if room cleared the link already
	else if(in_room -> getPatient(name, surname).isValid())
	{
		debug(patient::unlinkFromRoom, link has to be terminated by room);
		return false;
	}
	//clear the link
	else in_room = nullptr;
	return true;
}

room& patient::getRoom() const
{
	//return a reference to the room
	//if not pointing to nullptr
	if(in_room != nullptr) return *in_room;
	//otherwise reference an empty room
	else return empty_room;
}

/*

[][][][][!] CLASS ROOM [!][][][][]

*/

std::ostream& operator<<(std::ostream& str, const room& rm)
{
	str << "ROOM: ";
	if(rm.name == "")
	str << "NULL";
	//if room does not have a name it's pointless to print any other info 
	else
	{
		str << rm.name;
		str << " | STAFF: ";
		if(rm.assignee != nullptr)
			str << rm.assignee -> getName() << " " << rm.assignee -> getSurname();
		else 
			str << "NOT ASSIGNED";
		str << " | PATIENTS: ";
		if(rm.patients.size() != 0) 
			str << rm.patients.size();
		else 
			str << "NONE";
	}
	return str;	
}

room::room(std::string rmnm)
{
	//initialise pointers
	assignee = nullptr;
	in_hospital = nullptr;
	//set some basic information
	name = rmnm;
}

room::~room()
{
	//clear links of objects to the room
	if(in_hospital != nullptr)
		in_hospital -> removeRoom(*this);
	if(!patients.empty())
	{
		patient* ptemp;
		auto pt = patients.begin();
		while(pt != patients.end())
		{
			//save for unlinkage
			ptemp = *pt; 
			//go to next
			pt++;
			//remove
			removePatient(*ptemp);
		}
	}
	if(assignee != nullptr)
		unlinkStaff();
	
}

bool room::setName(std::string rmnm)
{
	//check if not empty
	if(rmnm == "")
	{
		debug(room::setName, provided string is empty);
		return false;
	}
	//check if not linked to hospital
	if(in_hospital != nullptr)
	{
		debug(room::setName, object is linked - you cannot change its name);
		return false;
	}
	//assign the string
	else name = rmnm;
	return true;
}

std::string room::getName() const
{
	//return a room name
	return name;
}

bool room::addPatient(patient& ptn)
{
	//check for room validity
	if(!isValid())
	{
		debug(room::addPatient, this room is invalid);
		return false;
	}
	//check if patient does not already exist in this room
	else if(getPatient(ptn.getName(), ptn.getSurname()).isValid())
	{
		debug(room::addPatient, this patient is already present);
		return false;
	}
	//create mutual relationship, patient verified
	else
	{
		//required for patient to detect two way link
		patients.push_back(&ptn);
		//if for any reason the link fails, notify and exit
		if(!ptn.linkToRoom(*this))
		{
			debug(room::addPatient, the patient refused to link);
			patients.remove(&ptn);
			return false;
		}
	}
	return true;
}

bool room::removePatient(patient& ptn)
{
	//search for the specified patient in the room
	if( getPatient(ptn.getName(), ptn.getSurname()).getName() == "")
	{
		debug(room::removePatient, this patient is not present);
		return false;
	}
	//match found
	else
	{
		patients.remove(&ptn);
		ptn.unlinkFromRoom();
	}
	return true;
}

void room::printPatients() const
{
	std::cout << "ROOM: '" << name << "' "; 
	//empty list optimisation
	if(patients.empty())
	{
		std::cout << "IS EMPTY!" << std::endl;
		return;
	}
	std::cout << "HAS PATIENTS:" << std::endl;
	//otherwise iterate through the list
	for(patient* p : patients)
	{
		//display the dereferenced element
		std::cout << *p << std::endl;
	}
}

patient& room::getPatient(std::string nmstr, std::string snstr) const
{
	//empty list optimisation
	if(patients.empty()) return empty_patient;
	//perform a search through the list
	for(patient* p : patients)
	{
		//check element's name and surname for match
		if((*p).getName() == nmstr && (*p).getSurname() == snstr)
		//return if match found 
		return *p;
	}
	//search did not find any match
	return empty_patient;
}

bool room::linkStaff(staffmember& stm)
{
	//check for room validity
	if(!isValid())
	{
		debug(room::linkStaff, this room is invalid);
		return false;
	}
	//check if room already has any staff
	else if(assignee != nullptr)
	{
		debug(room::linkStaff, this room is already linked);
		return false;
	}
	//add a verified staff member
	else
	{
		//required for staff to detect two way link
		assignee = &stm;
		//if for any reason the link fails, notify and exit
		if(!stm.linkToRoom(*this))
		{
			debug(room::linkStaff, the staffmember refused to link);
			assignee = nullptr;
			return false;
		}
	}
	return true;
}

bool room::unlinkStaff()
{
	//if there is no staff return false
	if(assignee == nullptr)
	{
		debug(room::unlinkStaff,this room does not have staff assigned);
		return false;
	}
	//clear the assignment, set to default value
	else
	{
		staffmember* temp = assignee;
		//required for staff to detect both way unlink
		assignee = nullptr;
		temp -> unlinkFromRoom();
	}
	return true;
}

staffmember& room::getStaff() const
{
	//check if staff pointer is null
	if(assignee == nullptr) return empty_staff;
	//if it is not return a staff reference
	else return *assignee;
}

bool room::linkToHospital(const hospital& hosp)
{
	//forbid one-way linking
	if(!hosp.getRoom(name).isValid())
	{
		debug(room::linkToHospital, one-way linking is forbidden);
		return false;
	}
	//check if room is valid
	if(!isValid())
	{
		debug(room::linkToHospital, this room does not have a name);
		return false;
	}	
	//check if hospital is already linked
	else if(in_hospital != nullptr)
	{
		debug(room::linkToHospital, a hospital has already been linked);
		return false;
	}
	//link can now be established
	else
	{
		//assign pointer
		in_hospital = &((hospital&)hosp);
		debug(room::linkToHospital, link confirmed);
	}
	return true;
}

bool room::unlinkFromHospital()
{
	//if room is not linked return false
	if(in_hospital == nullptr)
	{
		debug(room::unlinkFromHospital, a link is not present); 
		return false;
	}
	//check if hospital unlinked first
	if(in_hospital -> getRoom(name).isValid())
	{
		debug(room::unlinkFromHospital, link has to be terminated by hospital);
		return false;
	}
	//clear the link
	else in_hospital = nullptr;
	return true;
}

hospital& room::getHospital() const
{
	//check if assignment is empty, return empty if it is
	if(in_hospital == nullptr) return empty_hospital;
	//if not return a reference
	else return *in_hospital;
}

bool room::isValid() const
{
	//check if name is empty
	if(name != "") return true;
	else return false;
}

/*

[][][][][!] CLASS HOSPITAL [!][][][][]

*/

std::ostream& operator<<(std::ostream& str, const hospital& hosp)
{
	str << "HOSPITAL: ";
	if(hosp.name != "")
	str << hosp.name << "";
	else
	str << "NULL";
	return str;
}

hospital::hospital(std::string hsnm)
{
	//set a name
	name = hsnm;
}

hospital::~hospital()
{
	//unlink every object associated with this hospital
	if(!roomlist.empty())
	{
		room* rtemp;
		auto rm = roomlist.begin();
		while(rm != roomlist.end())
		{
			//save for unlinkage
			rtemp = *rm;
			//advance
			rm++;
			//remove linkage
			removeRoom(*rtemp);
		}
	}
	if(!stafflist.empty())
	{
		staffmember* stemp;
		auto sm = stafflist.begin();
		while(sm != stafflist.end())
		{
			//save for unlinkage
			stemp = *sm;
			//advance
			sm++;
			//remove linkage
			dismissStaff(*stemp);
		}
	}
	if(!patients.empty())
	{
		patient* ptemp;
		auto pt = patients.begin();
		while(pt != patients.end())
		{
			//save for unlinkage
			ptemp = *pt;
			//advance
			pt++;
			//remove linkage
			dischargePatient(*ptemp);
		}
	}
	
}

bool hospital::setName(std::string hsnm)
{
	//check if the name is not empty
	if(hsnm == "")
	{
		debug(hospital::setName, provided name is an empty string);
		return false;
	}
	//set values if name is correct
	else name = hsnm;
	return true;
}

std::string hospital::getName() const
{
	return name;
}

bool hospital::registerPatient(patient& ptn)
{
	//check if hospital is valid
	if(!isValid())
	{
		debug(hospital::registerPatient, this hospital is not valid);
		return false;
	}
	//check if patient exists on patient list
	else if(getPatient(ptn.getName(), ptn.getSurname()).isValid())
	{
		debug(hospital::registerPatient, this patient is already registered);
		return false;
	}
	//patient can be added properly
	else
	{
		//for the patient to detect two-way link
		patients.push_back(&ptn);
		//if for any reason link fails, notify and exit
		if(!ptn.linkToHospital(*this))
		{
			debug(hospital::registerPatient, the patient refused to link);
			patients.remove(&ptn);
			return false;
		} 
	}
	return true;
}

bool hospital::dischargePatient(patient& ptn)
{
	//temporary value to search once
	patient& pat = getPatient(ptn.getName(), ptn.getSurname());
	//check if such patient is on the list
	if(pat.isValid())
	{
		//remove
		patients.remove(&pat);
		pat.unlinkFromHospital();
		return true;
	}
	else debug(hospital::dischargePatient, this patient is not present);
	return false;
}

void hospital::printPatients() const
{
	//display list header
	std::cout << "HOSPITAL: '" << name << "' "; 
	//empty list optimisation
	if(patients.empty())
	{
		std::cout << "HAS NO PATIENTS!" << std::endl;
		return;
	}
	std::cout << "HAS PATIENTS:" << std::endl;
	//iterate through the list
	for(patient* p : patients)
	{
		//check element's name and surname for match
		std::cout << (*p) << std::endl;
	}
}

patient& hospital::getPatient(std::string nmstr, std::string snstr) const
{
	//empty list optimisation
	if(patients.empty()) return empty_patient;
	//perform a search through the list
	for(patient* p : patients)
	{
		//check element's name and surname for match
		if((*p).getName() == nmstr && (*p).getSurname() == snstr)
		//return if match found 
		return *p;
	}
	//search did not find any match
	return empty_patient;
}

bool hospital::employStaff(staffmember& stm)
{
	//check if hospital has a name
	if(!isValid())
	{
		debug(hospital::employStaff, this hospital is invalid);
		return false;
	}
	//check if staff member is not employed here already
	else if(getStaff(stm.getName(), stm.getSurname()).isValid())
	{
		debug(hospital::employStaff, this staff member is employed already);
		return false;
	}
	//staff is now valid to employ
	else
	{
		stafflist.push_back(&stm);
		if(!stm.linkToHospital(*this))
		{
			debug(hospital::employStaff, the staffmember refused to link);
			stafflist.remove(&stm);
			return false;
		}
	}
	return true;
}

bool hospital::dismissStaff(staffmember& stm)
{
	//temp value for one search only
	staffmember& staff = getStaff(stm.getName(), stm.getSurname());
	//check if search returned valid staff
	if(staff.isValid())
	{
		stafflist.remove(&stm);
		stm.unlinkFromHospital();
		return true;
	}
	else debug(hospital::dismissStaff, this staff member is not employed);
	return false;
}

void hospital::printStaff() const
{
	//display list header
	std::cout << "HOSPITAL: '" << name << "' "; 
	//empty list optimisation
	if(stafflist.empty())
	{
		std::cout << "HAS NO STAFF!" << std::endl;
		return;
	}
	std::cout << "HAS STAFF:" << std::endl;
	//iterate through the list
	for(staffmember* s : stafflist)
	{
		//display staff member data
		std::cout << (*s) << std::endl;
	}
}

staffmember& hospital::getStaff(std::string namestr, std::string surnamestr) const
{
	//empty list optimisation
	if(stafflist.empty()) return empty_staff;
	//search for the staffmember
	for(staffmember* s : stafflist)
	{
		if((*s).getName() == namestr && (*s).getSurname() == surnamestr)
		return *s; 
	}
	//search did not succeed
	return empty_staff;
}

bool hospital::addRoom(room& rm)
{
	//unnamed hospital
	if(!isValid())
	{
		debug(hospital::addRoom, this hospital is invalid);
		return false;
	}
	//room with same name already exists
	if(getRoom(rm.getName()).isValid())
	{
		debug(hospital::addRoom, this room already exists);
		return false;
	}
	//hospital can be validly added
	else
	{
		roomlist.push_back(&rm);
		if(!rm.linkToHospital(*this))
		{
			debug(hospital::addRoom, the room refused to link);
			roomlist.remove(&rm);
			return false;
		}
	}
	return true;
}

bool hospital::removeRoom(room& rm)
{
	//temp value for one search only
	room& roomref = getRoom(rm.getName());
	//check if search returned valid room
	if(roomref.isValid())
	{
		roomlist.remove(&rm);
		rm.unlinkFromHospital();
		return true;
	}
	else debug(hospital::removeRoom, this room is not present);
	return false;
}

void hospital::printRooms() const
{
	//display list header
	std::cout << "HOSPITAL: '" << name << "' "; 
	//empty list optimisation
	if(roomlist.size() == 0)
	{
		std::cout << "HAS NO ROOMS!" << std::endl;
		return;
	}
	std::cout << "HAS ROOMS:" << std::endl;
	//iterate through the list
	for(room* r : roomlist)
	{
		//display room names
		std::cout << (*r).getName() << std::endl;
	}
}

room& hospital::getRoom(std::string nmstr) const
{
	//empty list optimisation
	if(roomlist.empty()) return empty_room;
	//perform a search through the list
	for(room* r : roomlist)
	{
		//check element's name and surname for match
		if((*r).getName() == nmstr)
		//return if match found 
		return *r;
	}
	//search did not find any match
	return empty_room;
}

void hospital::printStatus() const
{
	std::cout << "HOSPITAL: '" << name << "' HAS " << stafflist.size()
	<< " STAFF, " << patients.size();
	if(patients.size() == 1) std::cout << " PATIENT, ";
	else std::cout << " PATIENTS, ";
	std::cout << roomlist.size();
	if(roomlist.size() == 1) std::cout << " ROOM";
	else std::cout << " ROOMS";
	std::cout << std::endl;
}

bool hospital::isValid() const
{
	//check if name is empty
	if(name != "") return true;
	else return false;
}
