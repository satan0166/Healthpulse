#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

class HealthPulse {
public:
    string name;
    double bodyweight;
    double height;
    double targetWeight;
    string medicalHistory;
    string bmiCategory;
    vector<pair<double, string>> weightHistory;
    vector<string> dietPlanHistory;
    map<string, vector<string>> weeklyExercisePlan;
    map<string, string> waterIntakeRecommendations;

    HealthPulse() : name(""), bodyweight(0.0), height(0.0), targetWeight(0.0), medicalHistory(""), bmiCategory("") {}

    void welcomeMessage() {
        cout << "Welcome to Health Pulse!" << endl;
        cout << "Let's get started on your journey to better health." << endl;
        cout << "Please enter your name: ";
        getline(cin, name);
    }

    void collectHealthData() {
        cout << "Hello, " << name << "!" << endl;
        cout << "Please provide some health-related information." << endl;

        do {
            cout << "Enter your current bodyweight (in kilograms): ";
            if (!(cin >> bodyweight) || bodyweight <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (bodyweight <= 0);

        do {
            cout << "Enter your height (in meters): ";
            if (!(cin >> height) || height <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (height <= 0);

        do {
            cout << "Enter your target weight (in kilograms): ";
            if (!(cin >> targetWeight) || targetWeight <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (targetWeight <= 0);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter your medical history (if any): ";
        getline(cin, medicalHistory);

        // Check for specific medical conditions
        if (medicalHistory.find("sugar") != string::npos || medicalHistory.find("diabetes") != string::npos) {
            recommendLowSugarDiet();
        } else {
            calculateBMI();
            PersonalizedDietPlan();
            initializeWeeklyExercisePlan();
        }

        recommendWaterIntake();
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

        weightHistory.push_back(make_pair(bodyweight, getCurrentDate()));
    }

    string getCurrentDate() {
        return "2023-09-15";
    }

    void recommendLowSugarDiet() {
        // Create a diet plan with low sugar recommendations
        dietPlanHistory.clear();
        dietPlanHistory.push_back("Limit your sugar intake to less than 25 grams per day.");
        dietPlanHistory.push_back("Choose sugar-free or low-sugar alternatives.");
        dietPlanHistory.push_back("Include plenty of fresh vegetables and lean proteins in your diet.");
        dietPlanHistory.push_back("Consult a healthcare professional or nutritionist for a personalized diet plan.");

        // Set the BMI category to "Special Dietary Needs"
        bmiCategory = "Special Dietary Needs";

        // Initialize an exercise plan
        initializeExercisePlan("Low-Impact Exercises", "Low-Impact Exercises", "Low-Impact Exercises");

        cout << "\nSince you have a history of sugar-related issues, we recommend a low-sugar diet plan for you." << endl;
    }

    void PersonalizedDietPlan() {
        dietPlanHistory.clear();

        if (bmiCategory == "Underweight") {
            // Existing diet plan for underweight individuals
            dietPlanHistory.push_back("Include more whole grains, such as oats, brown rice, and quinoa.");
            dietPlanHistory.push_back("Consume protein-rich foods like lean meats (chicken, turkey), beans, and dairy (low-fat yogurt).");
            dietPlanHistory.push_back("Incorporate healthy fats like avocados, nuts, and olive oil for extra calories.");
            dietPlanHistory.push_back("Snack on nuts, seeds, and dried fruits for additional energy.");
        } else if (bmiCategory == "Healthy Weight") {
            // Existing diet plan for healthy weight individuals
            dietPlanHistory.push_back("Explore a variety of colorful fruits and vegetables to ensure a wide range of nutrients.");
            dietPlanHistory.push_back("Incorporate whole grains like whole wheat bread, brown rice, and quinoa for sustained energy.");
            dietPlanHistory.push_back("Include lean protein sources such as chicken, fish, and tofu.");
            dietPlanHistory.push_back("Don't forget to stay hydrated with plenty of water throughout the day.");
        } else if (bmiCategory == "Overweight") {
            // Existing diet plan for overweight individuals
            dietPlanHistory.push_back("Focus on portion control to manage calorie intake.");
            dietPlanHistory.push_back("Choose low-fat dairy products like skim milk and yogurt.");
            dietPlanHistory.push_back("Opt for lean protein sources such as grilled chicken and fish.");
            dietPlanHistory.push_back("Increase your intake of fibrous foods like vegetables and whole grains.");
            dietPlanHistory.push_back("Limit sugary drinks and snacks to reduce empty calories.");
        } else if (bmiCategory == "Obese" || bmiCategory == "Special Dietary Needs") {
            // Diet plan for obese individuals or those with special dietary needs
            dietPlanHistory.push_back("Consume a high-fiber diet with plenty of fruits, vegetables, and whole grains.");
            dietPlanHistory.push_back("Include lean protein sources like chicken, turkey, and fish.");
            dietPlanHistory.push_back("Avoid high-calorie, sugary, and processed foods.");
            dietPlanHistory.push_back("Regularly monitor portion sizes and practice portion control.");
            dietPlanHistory.push_back("Consult a healthcare professional or nutritionist for a personalized diet plan.");
        }
    }

    void initializeWeeklyExercisePlan() {
        weeklyExercisePlan.clear();

        if (bmiCategory == "Underweight") {
            initializeExercisePlan("Yoga", "Pilates", "Bodyweight Exercises");
        } else if (bmiCategory == "Healthy Weight") {
            initializeExercisePlan("Cardio", "Strength Training", "Yoga");
        } else if (bmiCategory == "Overweight" || bmiCategory == "Special Dietary Needs") {
            initializeExercisePlan("Cardio", "Swimming", "Cycling");
        } else if (bmiCategory == "Obese") {
            initializeExercisePlan("Cardio", "Strength Training", "Aqua Aerobics");
        }
    }

    void initializeExercisePlan(const string& exercise1, const string& exercise2, const string& exercise3) {
        weeklyExercisePlan["Week 1"].push_back(exercise1);
        weeklyExercisePlan["Week 1"].push_back(exercise2);
        weeklyExercisePlan["Week 1"].push_back(exercise3);
    }

    void recommendWaterIntake() {
        waterIntakeRecommendations["Underweight"] = "Drink at least 8 glasses (64 ounces) of water per day.";
        waterIntakeRecommendations["Healthy Weight"] = "Drink at least 8 glasses (64 ounces) of water per day.";
        waterIntakeRecommendations["Overweight"] = "Drink at least 8 glasses (64 ounces) of water per day.";
        waterIntakeRecommendations["Obese"] = "Drink at least 8 glasses (64 ounces) of water per day.";
        waterIntakeRecommendations["Special Dietary Needs"] = "Drink at least 8 glasses (64 ounces) of water per day.";
    }

    void displayDietPlan() {
        cout << "\nDiet Plan for " << name << " (BMI Category: " << bmiCategory << "):\n";
        for (const auto& plan : dietPlanHistory) {
            cout << "- " << plan << endl;
        }
    }

    void displayExercisePlan() {
        cout << "\nExercise Plan for " << name << " (BMI Category: " << bmiCategory << "):\n";
        for (const auto& plan : weeklyExercisePlan) {
            cout << plan.first << ":\n";
            for (const auto& exercise : plan.second) {
                cout << "- " << exercise << endl;
            }
        }
    }

    void displayWaterIntakeRecommendation() {
        cout << "\nWater Intake Recommendation for " << name << " (BMI Category: " << bmiCategory << "):\n";
        cout << waterIntakeRecommendations[bmiCategory] << endl;
    }
};

int main() {
    HealthPulse healthPulse;

    healthPulse.welcomeMessage();
    healthPulse.collectHealthData();

    cout << "\nUser Data:\n";
    cout << "Name: " << healthPulse.name << endl;
    cout << "Bodyweight: " << healthPulse.bodyweight << " kg\n";
    cout << "Height: " << healthPulse.height << " meters\n";
    cout << "Target Weight: " << healthPulse.targetWeight << " kg\n";
    cout << "Medical History: " << healthPulse.medicalHistory << "\n";
    cout << "BMI Category: " << healthPulse.bmiCategory << "\n";

    healthPulse.displayDietPlan();
    healthPulse.displayExercisePlan();
    healthPulse.displayWaterIntakeRecommendation();

    return 0;
}
