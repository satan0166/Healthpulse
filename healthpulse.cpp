#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <iomanip>
#include <cmath>
#include <fstream>


using namespace std;

class HealthPulse {
public:

    string name;
    int age;
    double bodyweight;
    double height;
    double targetWeight;
    double dailyCalorieIntake;
    double dailyCaloriesBurned;
    double netCalorieIntake;
    string bmiCategory;
    vector<string> dietPlan;
    vector<string> workoutPlan;
    bool workedOut;
    map<string, double> foodCalories;
    HealthPulse() : name(""), age(0), bodyweight(0.0), height(0.0), targetWeight(0.0),
                dailyCalorieIntake(0.0), dailyCaloriesBurned(0.0), netCalorieIntake(0.0), bmiCategory(""), workedOut(false) {
    initializeFoodCalories(); 
    estimateTimeToTargetWeight();  
}

    bool isUsernameExists(const string& username) {
        ifstream credentialsFile("credentials.txt");
        if (credentialsFile.is_open()) {
            string storedUsername, storedPassword;
            while (credentialsFile >> storedUsername >> storedPassword) {
                if (storedUsername == username) {
                    credentialsFile.close();
                    return true;  // Username already exists
                }
            }
            credentialsFile.close();
        }
        return false;  // Username does not exist
    }


    string username;
    string password;
    void saveCredentials(const string& username, const string& password) {
        ofstream credentialsFile("credentials.txt", ios::app);
        if (credentialsFile.is_open()) {
            credentialsFile << username << " " << password << "\n";
            credentialsFile.close();
        } else {
            cout << "Unable to save user credentials.\n";
        }
    }

    void registerUser() {
        cout << "Register a new user:\n";
        cout << "Create a username: ";
        string newUsername;
        cin >> newUsername;

        // Check if the username already exists
        if (isUsernameExists(newUsername)) {
            cout << "Username already exists. Please choose a different username.\n";
            return;
        }

        cout << "Create a password: ";
        string newPassword;
        cin >> newPassword;

        saveCredentials(newUsername, newPassword);
    }


    bool login() {
        cout << "Login to HealthPulse:\n";
        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        return validateCredentials(username, password);
    }

    bool validateCredentials(const string& username, const string& password) {
        ifstream credentialsFile("credentials.txt");
        if (credentialsFile.is_open()) {
            string storedUsername, storedPassword;
            while (credentialsFile >> storedUsername >> storedPassword) {
                if (storedUsername == username && storedPassword == password) {
                    credentialsFile.close();
                    return true;
                }
            }
            credentialsFile.close();
        }
        return false; 
    }

    void saveCredentials() {
        ofstream credentialsFile("credentials.txt", ios::app);
        if (credentialsFile.is_open()) {
            credentialsFile << username << " " << password << "\n";
            credentialsFile.close();
        } else {
            cout << "Unable to save user credentials.\n";
        }
    }



void saveUserData() {
        ofstream outFile("user_data.txt");

        if (outFile.is_open()) {
            outFile << name << "\n";
            outFile << age << "\n";
            outFile << bodyweight << "\n";
            outFile << height << "\n";
            outFile << targetWeight << "\n";
            outFile << dailyCalorieIntake << "\n";
            outFile << dailyCaloriesBurned << "\n";
            outFile << netCalorieIntake << "\n";
            outFile << bmiCategory << "\n";
            outFile << workedOut << "\n";

            outFile << dietPlan.size() << "\n";
            for (const auto& plan : dietPlan) {
                outFile << plan << "\n";
            }
            outFile << workoutPlan.size() << "\n";
            for (const auto& plan : workoutPlan) {
                outFile << plan << "\n";
            }

            outFile.close();
        } else {
            cout << "Unable to save user data to file.\n";
        }
    }
    void loadUserData() {
        ifstream inFile("user_data.txt");

        if (inFile.is_open()) {
            getline(inFile, name);
            inFile >> age >> bodyweight >> height >> targetWeight >> dailyCalorieIntake >> dailyCaloriesBurned >> netCalorieIntake;
            inFile.ignore();
            getline(inFile, bmiCategory);
            inFile >> workedOut;

            int dietPlanSize;
            inFile >> dietPlanSize;
            inFile.ignore();  
            dietPlan.clear();
            for (int i = 0; i < dietPlanSize; ++i) {
                string plan;
                getline(inFile, plan);
                dietPlan.push_back(plan);
            }

            int workoutPlanSize;
            inFile >> workoutPlanSize;
            inFile.ignore();  
            workoutPlan.clear();
            for (int i = 0; i < workoutPlanSize; ++i) {
                string plan;
                getline(inFile, plan);
                workoutPlan.push_back(plan);
            }

            inFile.close();
        } else {
            cout << "No saved user data found. Starting fresh.\n";
        }
    }

void estimateTimeToTargetWeight() {
    const double caloriesPerKg = 7700.0;
    double weightChangeCalories = fabs(targetWeight - bodyweight) * caloriesPerKg;
    
    if (netCalorieIntake != 0) {
        double estimatedDays = weightChangeCalories / fabs(netCalorieIntake);
        
        cout << "\nEstimated time to achieve target weight: ";
        if (netCalorieIntake > 0) {
            cout << "Losing ";
        } else {
            cout << "Gaining ";
        }

        cout << fabs(targetWeight - bodyweight) << " kg";

        if (estimatedDays < 7) {
            cout << " in less than a week.";
        } else {
            int estimatedWeeks = static_cast<int>(estimatedDays / 7);
            cout << " in approximately " << estimatedWeeks << " weeks.";
        }
        cout << endl;
    }
}
    void welcomeMessage() {
        cout << "Welcome to HealthPulse!" << endl;
        cout << "Embark on a journey to better health and well-being." << endl;
        cout << "Let's get started on your personalized health and fitness plan." << endl;
        cout << "Please enter your name: ";
        cin.ignore();  
        getline(cin, name);
    }

    void provideCalorieRecommendation() {
    const double calorieDeficitThreshold = 500.0;
    double calorieDeficit = (targetWeight - bodyweight) * 7700.0/1000.0;  

    if (targetWeight < bodyweight) {
        // User wants to lose weight
        double lowerThreshold = calorieDeficit - calorieDeficitThreshold;
        double upperThreshold = calorieDeficit + calorieDeficitThreshold;

        if (netCalorieIntake < lowerThreshold) {
            cout << "Your current daily calorie intake may be too low for a healthy weight loss. Consider increasing your calorie intake." << endl;
        } else if (netCalorieIntake > upperThreshold) {
            cout << "Your current daily calorie intake may be too high for a healthy weight loss. Consider reducing your calorie intake." << endl;
        } else {
            cout << "Your daily calorie intake is within a healthy range for your weight loss goal. Keep up the good work!" << endl;
        }
    } else if (targetWeight > bodyweight) {
        // User wants to gain weight
        double lowerThreshold = calorieDeficit - calorieDeficitThreshold;
        double upperThreshold = calorieDeficit + calorieDeficitThreshold;

        if (netCalorieIntake < lowerThreshold) {
            cout << "Your current daily calorie intake may be too low for a healthy weight gain. Consider increasing your calorie intake." << endl;
        } else if (netCalorieIntake > upperThreshold) {
            cout << "Your current daily calorie intake may be too high for a healthy weight gain. Consider reducing your calorie intake." << endl;
        } else {
            cout << "Your daily calorie intake is within a healthy range for your weight gain goal. Keep up the good work!" << endl;
        }
    } else {
        // User wants to maintain current weight
        double lowerThreshold = calorieDeficit - calorieDeficitThreshold;
        double upperThreshold = calorieDeficit + calorieDeficitThreshold;

        if (netCalorieIntake < lowerThreshold) {
            cout << "Your current daily calorie intake may be too low for maintaining your weight. Consider increasing your calorie intake." << endl;
        } else if (netCalorieIntake > upperThreshold) {
            cout << "Your current daily calorie intake may be too high for maintaining your weight. Consider reducing your calorie intake." << endl;
        } else {
            cout << "Your daily calorie intake is within a healthy range for maintaining your weight. Keep up the good work!" << endl;
        }
    }

}


    void collectHealthData() {
        cout << "Hello,  "<< name << "!" << endl;
        cout << "Let's begin by gathering some health-related information." << endl;

        // Validate age input
        do {
            cout << "Enter your age: ";
            if (!(cin >> age) || age < 18 || age > 99) {
                cout << "Invalid input. Please enter a valid age between 18 and 99: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (age < 18 || age > 99);

        // Validate bodyweight input
        do {
            cout << "Enter your current bodyweight (in kilograms): ";
            if (!(cin >> bodyweight) || bodyweight <= 0 || bodyweight > 500) {
                cout << "Invalid input. Please enter a positive number between 0 and 500: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (bodyweight <= 0 || bodyweight > 500);

        // Validate height input
        do {
            cout << "Enter your height (in meters): ";
            if (!(cin >> height) || height <= 0 || height > 2.5) {
                cout << "Invalid input. Please enter a positive number between 0 and 2.5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (height <= 0 || height > 2.5);

        do {
            cout << "Enter your target weight (in kilograms): ";
            if (!(cin >> targetWeight) || targetWeight <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (targetWeight <= 0);

        do {
            cout << "Did you work out today? (1 for Yes, 0 for No): ";
            if (!(cin >> workedOut) || (workedOut != 0 && workedOut != 1)) {
                cout << "Invalid input. Please enter 1 for Yes or 0 for No: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (workedOut != 0 && workedOut != 1);

        calculateBMI();
        calculateCaloriesBurned();
        calculateCaloriesIntake();
        calculateNetCalorieIntake();
        //provideCalorieRecommendation();
        generateDietPlan();
        generateWorkoutPlan();
        calculateWaterIntake();
    }

    void calculateBMI() {
        double bmi = bodyweight / (height * height);

        if (bmi < 18.5) {
            bmiCategory = "Underweight";
        } else if (bmi < 24.9) {
            bmiCategory = "Healthy Weight";
        } else if (bmi < 29.9) {
            bmiCategory = "Overweight";
        } else {
            bmiCategory = "Obese";
        }
    }

    void calculateCaloriesBurned() {
    double totalCaloriesBurned = 0.0;
    cout << "Please enter your exercises and reps to calculate calories burned (type '0' for reps to finish):" << endl;
    while (true) {
        string exercise;
        int reps;
        cout << "Enter exercise: ";
        cin.ignore();  // Clear the newline character
        getline(cin, exercise);
        if (exercise == "0") {
            break;
        }
        cout << "Enter reps: ";
        if (!(cin >> reps) || reps < 0) {
            cout << "Invalid input for reps. Please enter a non-negative number or '0' to finish: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Calculate calories burned for each exercise (you can add your own formula here)
        double caloriesBurnedPerExercise = reps * 0.1;
        totalCaloriesBurned += caloriesBurnedPerExercise;
    }
    dailyCaloriesBurned = totalCaloriesBurned;
}

   void calculateCaloriesIntake() {
    double totalCaloriesIntake = 0.0;
    cout << "Please select food items or drinks to calculate calories intake (enter the corresponding number, enter '0' to finish):" << endl;

    int foodChoice;
    while (true) {
        cout << "Available Options:" << endl;
        int optionCount = 1;
        for (const auto& food : foodCalories) {
            cout << optionCount << ". " << food.first << endl;
            optionCount++;
        }

  cout << "Enter your choice (enter '0' to finish): ";
        if (!(cin >> foodChoice)) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (foodChoice == 0) {
            // User selected '0' to finish
            break;
        }

        if (foodChoice < 1 || foodChoice > optionCount - 1) {
            cout << "Invalid input. Please enter a valid number or '0' to finish." << endl;
            continue;
        }
        // Get the food item based on the user's choice
        auto foodIt = foodCalories.begin();
        advance(foodIt, foodChoice - 1);

        string food = foodIt->first;
        double calories = foodIt->second;

        // Assume a standard quantity for simplicity
        const double standardQuantity = 100.0;

        // Calculate calories based on standard quantity
        calories = (calories * standardQuantity) / 100.0;

        totalCaloriesIntake += calories;
                cout << "Calories for " << food << ": " << calories << " calories" << endl;
    }

    dailyCalorieIntake = totalCaloriesIntake;
}




    void calculateNetCalorieIntake() {
        netCalorieIntake = dailyCalorieIntake - dailyCaloriesBurned;
    }

    void calculateWaterIntake() {
        double suggestedWaterIntake = (bodyweight * 30.0);

        if (bmiCategory == "Obese") {
            suggestedWaterIntake *= 1.1;
        }

        cout << "\nWater Intake Recommendation for " << name << ":\n";
        cout << "Based on your body weight and BMI, it is recommended that you consume at least " << suggestedWaterIntake << " milliliters of water per day.\n";
    }

   void generateDietPlan() {
    dietPlan.clear();

    cout << "Do you have any food allergies? Select an option:" << endl;
    cout << "1. No allergies" << endl;
    cout << "2. Dairy allergy" << endl;
    cout << "3. Nut allergy";

    int allergyChoice;
    while (true) {
        cout << "Enter your choice (1, 2, or 3): ";
        if (!(cin >> allergyChoice) || (allergyChoice != 1 && allergyChoice != 2 && allergyChoice != 3)) {
            cout << "Invalid input. Please enter 1, 2, or 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    if (allergyChoice == 1) {
        if (bmiCategory == "Underweight") {
            dietPlan.push_back("Breakfast: Scrambled eggs with avocado");
            dietPlan.push_back("Lunch: Quinoa salad with chickpeas");
            dietPlan.push_back("Snack: Almonds and a banana");
            dietPlan.push_back("Dinner: Grilled salmon with steamed broccoli");
        } else if (bmiCategory == "Healthy Weight") {
            dietPlan.push_back("Breakfast: Greek yogurt with berries");
            dietPlan.push_back("Lunch: Grilled chicken with mixed vegetables");
            dietPlan.push_back("Snack: Carrot and cucumber sticks with hummus");
            dietPlan.push_back("Dinner: Baked cod with quinoa");
        } else if (bmiCategory == "Overweight") {
            dietPlan.push_back("Breakfast: Oatmeal with nuts and honey");
            dietPlan.push_back("Lunch: Turkey and vegetable stir-fry");
            dietPlan.push_back("Snack: Sliced apples with peanut butter");
            dietPlan.push_back("Dinner: Lean beef with asparagus and brown rice");
        } else if (bmiCategory == "Obese") {
            dietPlan.push_back("Breakfast: Whole-grain toast with avocado and poached eggs");
            dietPlan.push_back("Lunch: Spinach and quinoa stuffed peppers");
            dietPlan.push_back("Snack: Mixed nuts and dried fruits");
            dietPlan.push_back("Dinner: Grilled tofu with sautéed kale and quinoa");
        }
    } else {
        dietPlan.push_back("We have created a custom diet plan based on your allergies:");
        dietPlan.push_back("Breakfast: Oatmeal with fruits (allergy-friendly)");
        dietPlan.push_back("Lunch: Grilled chicken salad (allergy-friendly)");
        dietPlan.push_back("Snack: Greek yogurt with honey (allergy-friendly)");
        dietPlan.push_back("Dinner: Baked salmon with vegetables (allergy-friendly)");
    }
}
void generateWorkoutPlan() {
    workoutPlan.clear();

    if (age < 30) {
        workoutPlan.push_back("Your workout plan for your age group (under 30):");
        workoutPlan.push_back("Monday: Full Body Workout");
        workoutPlan.push_back("- Bench Press: 4 sets x 8-10 reps");
        workoutPlan.push_back("- Tricep Dips: 3 sets x 10-12 reps");
        workoutPlan.push_back("Tuesday: Back and Biceps");
        workoutPlan.push_back("- Pull-Ups or Lat Pulldowns: 4 sets x 8-10 reps");
        workoutPlan.push_back("- Bicep Curls: 3 sets x 10-12 reps");
        workoutPlan.push_back("Wednesday: Legs and Abs");
        workoutPlan.push_back("- Squats: 4 sets x 8-10 reps");
        workoutPlan.push_back("- Leg Raises: 3 sets x 10-12 reps");
        workoutPlan.push_back("Thursday: Shoulders and Cardio");
        workoutPlan.push_back("- Overhead Press: 4 sets x 8-10 reps");
        workoutPlan.push_back("- Cardio: 30 minutes of running or cycling");
        workoutPlan.push_back("Friday: Rest day (relax and recover)");
        workoutPlan.push_back("Saturday: Full Body Workout");
        workoutPlan.push_back("- Deadlifts: 4 sets x 6-8 reps");
        workoutPlan.push_back("Sunday: Rest day (relax and recover)");
        workoutPlan.push_back("- Push-Ups: 3 sets x 10-12 reps");
    } else {
        workoutPlan.push_back("Your workout plan for your age group (30 and above):");
        workoutPlan.push_back("Monday: Low-Impact Workout");
        workoutPlan.push_back("Tuesday: Stretching and Yoga");
        workoutPlan.push_back("Wednesday: Low-Impact Workout");
        workoutPlan.push_back("Thursday: Stretching and Yoga");
        workoutPlan.push_back("Friday: Rest day (relax and recover)");
        workoutPlan.push_back("Saturday: Low-Impact Workout");
        workoutPlan.push_back("Sunday: Rest day (relax and recover)");
    }
}


    void displayUserData() {
        cout << "\nUser Data:\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << " years\n";
        cout << "Bodyweight: " << bodyweight << " kg\n";
        cout << "Height: " << height << " meters\n";
        cout << "Target Weight: " << targetWeight << " kg\n";
        cout << "BMI Category: " << bmiCategory << "\n";
    }

    void displayCaloriesInfo() {
        cout << "\nCalories Information:\n";
        cout << "Daily Calorie Intake: " << dailyCalorieIntake << " calories\n";
        cout << "Daily Calories Burned: " << dailyCaloriesBurned << " calories\n";
        cout << "Net Calorie Intake (Intake vs. Burnt): " << netCalorieIntake << " calories\n";
    }

    void displayDietPlan() {
        cout << "\nDiet Plan for " << name << " (BMI Category: " << bmiCategory << "):\n";
        for (const auto& plan : dietPlan) {
            cout << "- " << plan << endl;
        }
    }

    void displayWorkoutPlan() {
        cout << "\nWorkout Plan for " << name << " (BMI Category: " << bmiCategory << "):\n";
        for (const auto& plan : workoutPlan) {
            cout << "- " << plan << endl;
        }
    }

    void initializeFoodCalories() {
        // You can add food items and their calorie values to the map here.
        foodCalories["Egg"] = 68.0;
        foodCalories["Apple"] = 95.0;
        foodCalories["Chicken Breast"] = 165.0;
        foodCalories["Salmon"] = 206.0;
        foodCalories["Broccoli"] = 55.0;
        foodCalories["Quinoa"] = 222.0;
        foodCalories["Rajma Chawal"] = 450.0;
        foodCalories["Butter Chicken"] = 350.0;
        foodCalories["Paneer Tikka"] = 175.0;
        foodCalories["Samosa"] = 175.0;
        foodCalories["Chole Bhature"] = 450.0;
        foodCalories["Pani Puri"] = 175.0;
        foodCalories["Gulab Jamun"] = 225.0;
        foodCalories["Masala Dosa"] = 225.0;
        foodCalories["Chicken Biryani"] = 425.0;
        foodCalories["Pav Bhaji"] = 350.0;
        foodCalories["Malai Kofta"] = 225.0;
        foodCalories["Aloo Paratha"] = 225.0;
        foodCalories["Vegetable Biryani"] = 350.0;
        foodCalories["Roti"] = 90.0;
        foodCalories["Palak Paneer"] = 222.0;
        foodCalories["Mango"] = 150.0;
        foodCalories["Banana"] = 105.0;
        foodCalories["Orange"] = 62.0;
        foodCalories["Watermelon"] = 46.0;
        foodCalories["Pineapple"] = 82.0;
        foodCalories["Pomegranate"] = 83.0;
        foodCalories["Oats"] = 147.0;
        foodCalories["Masala Tea"] = 150.0;
        foodCalories["Filter Coffee"] = 80.0;
        foodCalories["Lemon Rice"] = 222.0;
        foodCalories["Lemon Water"] = 10.6;
        // Add more food items as needed.
    }
};
int main() {
    HealthPulse healthPulse;

    bool isLoggedIn = false;
    while (!isLoggedIn) {
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                healthPulse.registerUser();
                break;
            case 2:
                isLoggedIn = healthPulse.login();
                if (!isLoggedIn) {
                    cout << "Invalid username or password. Try again.\n";
                }
                break;
            default:
                cout << "Invalid choice. Please choose again.\n";
                break;
        }
    }

    // Load user data or create a new user
    healthPulse.loadUserData();
    if (healthPulse.name.empty()) {
        healthPulse.welcomeMessage();
        healthPulse.collectHealthData();
    }

    // Display user data
    healthPulse.displayUserData();
    healthPulse.displayCaloriesInfo();
    healthPulse.provideCalorieRecommendation();
    healthPulse.displayDietPlan();
    healthPulse.displayWorkoutPlan();
    healthPulse.estimateTimeToTargetWeight();

    // Save user data
    healthPulse.saveUserData();
    
    return 0;
}