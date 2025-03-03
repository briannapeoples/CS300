 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <string>
 #include <map>
 #include <vector>
 #include <algorithm>
 
 using namespace std;
 
 struct Course {
     string courseNumber;
     string courseTitle;
     vector<string> prerequisites;
 };
 
 void loadDataStructure(const string& fileName, map<string, Course>& courses) {
 
     courses.clear();
 
     ifstream inFile(fileName);
     if (!inFile.is_open()) {
         throw runtime_error("Could not open file: " + fileName);
     }
 
     string line;
     while (getline(inFile, line)) {
         if (line.empty()) {
             continue;
         }
 
         vector<string> tokens;
         string token;
         stringstream ss(line);
         while (getline(ss, token, ',')) {
             tokens.push_back(token);
         }
 
         if (tokens.size() < 2) {
             continue;
         }
 
         Course course;
         course.courseNumber = tokens[0];
         course.courseTitle  = tokens[1];
 
         for (size_t i = 2; i < tokens.size(); ++i) {
             if (!tokens[i].empty()) {
                 course.prerequisites.push_back(tokens[i]);
             }
         }
 
         courses[course.courseNumber] = course;
     }
 
     inFile.close();
 }
 

 void printCourseList(const map<string, Course>& courses) {
     for (const auto& pair : courses) {
         const Course& c = pair.second;
         cout << c.courseNumber << ", " << c.courseTitle << endl;
     }
 }
 
 void printCourseInformation(const map<string, Course>& courses, const string& courseNumber) {
 
     auto it = courses.find(courseNumber);
     if (it == courses.end()) {
         cout << "Course not found." << endl;
         return;
     }
 
     const Course& course = it->second;
     cout << course.courseNumber << ", " << course.courseTitle << endl;
 
     if (course.prerequisites.empty()) {
         cout << "Prerequisites: None" << endl;
     } else {
         cout << "Prerequisites: " << endl;
         for (const auto& prereqNumber : course.prerequisites) {
             auto pit = courses.find(prereqNumber);
             if (pit != courses.end()) {
                 cout << "  " << pit->second.courseNumber << ", "
                      << pit->second.courseTitle << endl;
             } else {
                 cout << "  " << prereqNumber << " (not found)" << endl;
             }
         }
     }
 }
 
 int main() {
 
     map<string, Course> courses;
 
     bool isDataLoaded = false;
 
     cout << "Welcome to the course planner." << endl << endl;
 
     int choice = 0;
     while (choice != 9) {
 
         cout << "1. Load Data Structure." << endl;
         cout << "2. Print Course List." << endl;
         cout << "3. Print Course." << endl;
         cout << "9. Exit" << endl << endl;
         cout << "What would you like to do? ";
 
         cin >> choice;
 
         if (!cin) {
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             cout << "Invalid selection. Please try again." << endl << endl;
             continue;
         }
 
         switch (choice) {
 
             case 1: {
                 cout << "Enter the name of the data file to load: ";
                 string fileName;
                 cin >> fileName;
 
                 try {
                     loadDataStructure(fileName, courses);
                     isDataLoaded = true;
                     cout << "Data loaded successfully!" << endl << endl;
                 }
                 catch (exception& e) {
                     cout << "Error: " << e.what() << endl << endl;
                 }
 
                 break;
             }
 
             case 2: {
                 if (!isDataLoaded) {
                     cout << "No data loaded. Please load data first." << endl << endl;
                 } else {
                     printCourseList(courses);
                     cout << endl;
                 }
                 break;
             }
 
             case 3: {
                 if (!isDataLoaded) {
                     cout << "No data loaded. Please load data first." << endl << endl;
                 } else {
                     cout << "What course do you want to know about? ";
                     string courseNumber;
                     cin >> courseNumber;
                     printCourseInformation(courses, courseNumber);
                     cout << endl;
                 }
                 break;
             }
 
             case 9:
                 cout << "Thank you for using the course planner!" << endl;
                 break;
 
             default:
                 cout << choice << " is not a valid option." << endl << endl;
                 break;
         }
     }
 
     return 0;
 }
 