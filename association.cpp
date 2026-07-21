#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;


//------------------------------------------------------------------------------
// PROBLEM 1: Association — Appointment Mangement
//here 3 - Doctor , Patients , Appointment (main classes)
//  Doctor - has many patients 
//         - has many appointments
//Patient  - has many doctors
//         - has many appointments
//Appointments -  doctor
//             - client
//             - room (aggregation relationship)
//here doctor and the patients both use appointment class - so we'll first make it
//appointment uses a Room class . so first it 

class Room{
    private:
    string number;
    int floor;

    public:
    Room(const string &number ,const int &floor) : number(number) , floor(floor) {};

    string getRoomNo() const{
        return number;
    }

    int getFloors() const{
        return floor;
    }
};

//forward Declation 
class Doctor;
class Patient;


class Appointment{
    private:
    Doctor *doctor;
    Patient *patient;
    Room *room;
    string time;

    public:
    Appointment(Doctor *doctor, Patient *patient, Room *room, const string &time);

    Doctor* getDoctor() const{
        return doctor;
    }

    void setDoctor(Doctor *doctor) {
        this->doctor = doctor;
    }

    Patient* getPatient() const{
        return patient;
    }

    void setPatient(Patient *&patient){
        this->patient = patient;
    }

};

class Doctor{
    private:
    string name;
    string specialization;
    // vector<Patient*>patients;
    vector<Appointment*>appointments;

    public:
    Doctor(const string &name, const string &specialization): name(name), specialization(specialization){};

    void addAppointment(Appointment *appo){
        appointments.push_back(appo);
    }

    string getDocName() const{
        return name;
    }

    vector<Patient*> getPatients() const; 

    string getSpecialization() const{
        return specialization;
    }
  };

class Patient{
    private:
    string name;
    vector<Appointment*> appointments;

    public:
    Patient(const string &name): name(name) {};

    void addAppointment(Appointment *appo){
        appointments.push_back(appo);
    }   

    vector<Doctor*> getDoctors() const;

    string getName() const{ return name;}
    vector<Appointment*> getAppointments() const { return appointments;}
    
};

Appointment::Appointment(Doctor *doctor, Patient *patient, Room *room, const string &time):
doctor(doctor), patient(patient), room(room), time(time)
{
 doctor->addAppointment(this);
 patient->addAppointment(this);
}

vector<Patient*> Doctor::getPatients() const{
    //give the patients details to doctor therough the all appointments books by the patient
    vector<Patient*>patients;
    for(auto &appo : appointments){
        Patient *p = appo->getPatient();
        
        if(find(patients.begin(), patients.end(), p) == patients.end()){
            patients.push_back(p);
        }
    }
    return patients;
}

 vector<Doctor*> Patient::getDoctors() const{
    vector<Doctor*>doctors;
    for(auto &appo : appointments){
        Doctor *d = appo->getDoctor();
       if(find(doctors.begin(), doctors.end(), d) == doctors.end()){
        doctors.push_back(d);
      }
        
    }
    return doctors;
 }



// ========================2..  Design Online Course Platform=========================
// Problem: Build a course platform where instructors create courses and students enroll in them.
//  This exercise practices unidirectional and one-to-many associations.

// Requirements:

// Instructor with a name and a list of Course objects they teach. An addCourse(course) method that adds the course and sets the instructor on the course.
// Course with a title, an Instructor reference, and a list of enrolled Student objects. An enrollStudent(student) 
// method that adds the student and sets the enrolled course on the student.
// Student with a name and an enrolledCourse reference
//  (the course they're currently taking). A getInstructorName() method that navigates through the course to return the instructor's name.


class Instructor;
class Student;


//course -> 1 to M - students
//       -> 1 to M - instructors
class Course{
    private:
        string courseName;
        vector<Instructor*>insructors;
        vector<Student*>enrolled;
        string time;
        string description;
        double amount;

    public:
    Course(Instructor* instructor, Student* student, const string &courseName, const string &time, const string &description, double amount);

    string getcourseName() const{
        return courseName;
    }

    string getcourseDesc() const{
        return description;
    }

    vector<Student*> getenrolledStudents() const {
        return enrolled;
    }

    vector<Instructor*> getinstructors() const{
        return insructors;
    }

    void enrollStudent(Student *student){
        if(find(enrolled.begin() , enrolled.end(), student) == enrolled.end()){
            enrolled.push_back(student);
        } 
    }

    void addInstructor(Instructor *instructor){
        if(find(insructors.begin(), insructors.end(), instructor) == insructors.end()){
            insructors.push_back(instructor);
        }
    }
};

//Student -> 1 to M Course
//         -> 1 to M instructors (according to enrolled course)

class Student{
    private:
    string name;
    string qualification;
    string city;
    string state;
    string country;
    vector<Course*> courses;
    
    public:
    Student(const string &name ,const string &qualification,const string &city,const string &state,const string &country): name(name), qualification(qualification), city(city), state(state), country(country){};
    
    string getName() const{
        return name;
    }

    vector<Course*> getCourses() const{
        return courses;
    }

    vector<Instructor*> getInstructors() const; //this details come from the courses

    void addCourse(Course* course){
        //let's check if course previously existed or not
        //if exist you can't take otherwise yes
        if(find(courses.begin() , courses.end() , course) == courses.end()){
            courses.push_back(course);
            course->enrollStudent(this); //now course knows that this student is enrolled in the course
            //instructor also needs to know that student is enrolled in his course
            
            return ;
        }
        return ;
    }
} ;

//Instructor -> 1 to M (Courses) - create
//              -> 1 to M(students) - students which are enrolled in therir couurse

class Instructor{
    private:
    string name;
    string qualification;
    string specialization;
    vector<Course*>courses;

    public:
    Instructor(const string &name, const string &qualification, const string &specs): name(name), qualification(qualification), specialization(specs){};

    void addCourse(Course * course){
        if(find(courses.begin(), courses.end(), course) == courses.end()){
            courses.push_back(course);
            course->addInstructor(this); //now course know that instructor is added to that course
            return ;
        }
        return ;
    }

    string getName() const{
        return name;
    }

    vector<Course*> getAllCourses() const{
        return courses;
    }

    vector<Student*> getAllStudents() const;  //this details come from the courses;

};


Course::Course(Instructor* instructor, Student* student, const string &courseName, const string &time, const string &description, double amount):
        courseName(courseName),time(time), description(description), amount(amount){
            insructors.push_back(instructor);
            enrolled.push_back(student);
            instructor->addCourse(this);
            student->addCourse(this);
        }


vector<Instructor*> Student::getInstructors() const{
   vector<Instructor*> res;
   for(auto &course: courses){
    //one course can have multiple instructors 
    for(auto &inst : course->getinstructors()){
        if(find(res.begin(), res.end() , inst) == res.end()){
            res.push_back(inst);
        }
     }
   }
   return res;
}

vector<Student*> Instructor:: getAllStudents() const{
    vector<Student*> res;
    for(auto &course : courses){
        for(auto &student : course->getenrolledStudents()){
            if(find(res.begin(), res.end(), student) == res.end()){
                res.push_back(student);
            }
        }
    }
    return res;
}



int main()
{

    




    // ==============2.  Online Course Platform - Test Cases ==========================

    // --- Setup: Students ---
    // Student std1("Shyam",    "B.E",                          "Ahmedabad", "Gujarat", "India");
    // Student std2("Rahul",    "Diploma in Computer Engg",      "Sanand",    "Gujarat", "India");
    // Student std3("Radha",    "B.E",                          "Jamnagar",  "Gujarat", "India");
    // Student std4("Mayur",    "Diploma in Computer Engg",      "Vadodara",  "Gujarat", "India");
    // Student std5("Sanju",    "B.E",                          "Ahmedabad", "Gujarat", "India");
    // Student std6("Nandani",  "Diploma in Computer Engg",      "Bharuch",   "Gujarat", "India");
    // Student std7("Pooja",    "B.E",                          "Surat",     "Gujarat", "India");
    // Student std8("Khushi",   "Diploma in Computer Engg",      "Gandhinagar","Gujarat","India");

    // // --- Setup: Instructors ---
    // Instructor inst1("Dr. Arjun Mehta",   "Ph.D in Computer Science",     "Data Structures & Algorithms");
    // Instructor inst2("Prof. Sneha Patel", "M.Tech in AI",                  "Machine Learning");
    // Instructor inst3("Dr. Rohan Shah",    "Ph.D in Electronics",           "Embedded Systems");
    // Instructor inst4("Prof. Kavita Desai","M.Sc in Mathematics",           "Discrete Mathematics");
    // Instructor inst5("Dr. Vikram Joshi",  "Ph.D in Software Engineering",  "System Design");

    // // --- Setup: Courses ---
    // // inst1 teaches 3 courses; std1 is in 2 courses; std2 is in 2 courses
    // Course course1(&inst1, &std1, "Data Structures",    "10:00 AM", "Learn about data structures",              100.0);
    // Course course2(&inst1, &std2, "Algorithms",         "11:00 AM", "Advanced algorithm design",                120.0);
    // Course course3(&inst2, &std1, "Machine Learning",   "02:00 PM", "Introduction to machine learning",         150.0);
    // Course course4(&inst2, &std3, "Deep Learning",      "03:00 PM", "Neural networks and deep learning",        180.0);
    // Course course5(&inst3, &std4, "Embedded Systems",   "09:00 AM", "Explore embedded systems design",          120.0);
    // Course course6(&inst4, &std5, "Discrete Math",      "08:00 AM", "Discrete mathematical structures",          80.0);
    // Course course7(&inst5, &std6, "System Design",      "04:00 PM", "Learn system design principles",           200.0);
    // // enroll more students into existing courses
    // //course1.getenrolledStudents(); // verify accessible
    // std5.addCourse(&course1);  // Sanju also joins Data Structures
    // std6.addCourse(&course3);  // Nandani also joins Machine Learning
    // inst1.addCourse(&course3); // inst1 also teaches Machine Learning

    // cout << "\n========== TEST 1: inst1's Courses ==========\n";
    // // Expected: Data Structures, Algorithms, Machine Learning
    // for(auto &c : inst1.getAllCourses())
    //     cout << "  " << c->getcourseName() << "\n";

    // cout << "\n========== TEST 2: inst1's Students (unique) ==========\n";
    // // Expected: Shyam (course1), Rahul (course2), Sanju (course1 via addCourse), Nandani (course3 via addCourse)
    // for(auto &s : inst1.getAllStudents())
    //     cout << "  " << s->getName() << "\n";

    // cout << "\n========== TEST 3: std1's (Shyam) Courses ==========\n";
    // // Expected: Data Structures, Machine Learning
    // for(auto &c : std1.getCourses())
    //     cout << "  " << c->getcourseName() << "\n";

    // cout << "\n========== TEST 4: std1's (Shyam) Instructors ==========\n";
    // // Expected: inst1 (Data Structures), inst2 (Machine Learning)
    // for(auto &i : std1.getInstructors())
    //     cout << "  " << i->getName() << "\n";

    // cout << "\n========== TEST 5: inst2's Students ==========\n";
    // // Expected: Shyam (course3), Radha (course4), Nandani (course3 via addCourse)
    // for(auto &s : inst2.getAllStudents())
    //     cout << "  " << s->getName() << "\n";

    // cout << "\n========== TEST 6: Duplicate enroll guard (std1 tries to join course1 again) ==========\n";
    // size_t before = std1.getCourses().size();
    // std1.addCourse(&course1);
    // size_t after = std1.getCourses().size();
    // cout << "  Courses before: " << before << "  after: " << after
    //      << (before == after ? "  [PASS - no duplicate]" : "  [FAIL - duplicate added]") << "\n";

    // cout << "\n========== TEST 7: inst5's Courses & Students ==========\n";
    // for(auto &c : inst5.getAllCourses())
    //     cout << "  Course: " << c->getcourseName() << "\n";
    // for(auto &s : inst5.getAllStudents())
    //     cout << "  Student: " << s->getName() << "\n";

    // cout << "\n========== TEST 8: std3's (Radha) Instructors ==========\n";
    // // Expected: inst2 (Deep Learning)
    // for(auto &i : std3.getInstructors())
    //     cout << "  " << i->getName() << "\n";

 return 0;
}