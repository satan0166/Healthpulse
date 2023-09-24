#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <ctime>

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
    map<string, vector<pair<string, int>>> weeklyExercisePlan;
    map<string, double> weeklyProgress;

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

        bodyweight = getPositiveInput("Enter your current bodyweight (in kilograms): ");
        height = getPositiveInput("Enter your height (in meters): ");
        targetWeight = getPositiveInput("Enter your target weight (in kilograms): ");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter your medical history (if any): ";
        getline(cin, medicalHistory);

        calculateBMI();
        PersonalizedDietPlan();
        initializeWeeklyExercisePlan();
    }

    double getPositiveInput(const string& prompt) {
        double input;
        do {
            cout << prompt;
            if (!(cin >> input) || input <= 0) {
                cout << "Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (input <= 0);
        return input;
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
        time_t now = time(0);
        tm* ltm = localtime(&now);
        string date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
        return date;
    }

    void PersonalizedDietPlan() {
        dietPlanHistory.clear();

        if (bmiCategory == "Underweight") {
            dietPlanHistory.push_back("Include more whole grains, such as oats, brown rice, and quinoa.");
            dietPlanHistory.push_back("Consume protein-rich foods like lean meats (chicken, turkey), beans, and dairy (low-fat yogurt).");
            dietPlanHistory.push_back("Incorporate healthy fats like avocados, nuts, and olive oil for extra calories.");
            dietPlanHistory.push_back("Snack on nuts, seeds, and dried fruits for additional energy.");
        } else if (bmiCategory == "Healthy Weight") {
            dietPlanHistory.push_back("Explore a variety of colorful fruits and vegetables to ensure a wide range of nutrients.");
            dietPlanHistory.push_back("Incorporate whole grains like whole wheat bread, brown rice, and quinoa for sustained energy.");
            dietPlanHistory.push_back("Include lean protein sources such as chicken, fish, and tofu.");
            dietPlanHistory.push_back("Don't forget to stay hydrated with plenty of water throughout the day.");
        } else if (bmiCategory == "Overweight") {
            dietPlanHistory.push_back("Focus on portion control to manage calorie intake.");
            dietPlanHistory.push_back("Choose low-fat dairy products like skim milk and yogurt.");
            dietPlanHistory.push_back("Opt for lean protein sources such as grilled chicken and fish.");
            dietPlanHistory.push_back("Increase your intake of fibrous foods like vegetables and whole grains.");
            dietPlanHistory.push_back("Limit sugary drinks and snacks to reduce empty calories.");
        } else if (bmiCategory == "Obese") {
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
            initializeExercisePlan("Strength Training: Push-ups, Squats, Lunges", 5);
        } else if (bmiCategory == "Healthy Weight") {
            initializeExercisePlan("Cardio: Running, Cycling\nStrength Training: Push-ups, Squats", 5);
        } else if (bmiCategory == "Overweight") {
            initializeExercisePlan("Cardio: Brisk Walking, Swimming, Cycling", 10);
        } else if (bmiCategory == "Obese") {
            initializeExercisePlan("Cardio: Swimming, Cycling, Running\nStrength Training: Bodyweight exercises", 15);
        }
    }

    void initializeExercisePlan(const string& exerciseName, int repsOrDuration) {
        vector<pair<string, int>> dailyExercises;

        vector<string> days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
        for (const string& day : days) {
            dailyExercises.push_back(make_pair(exerciseName, repsOrDuration));
        }

        weeklyExercisePlan["Week 1"] = dailyExercises;
    }

    void trackWeeklyProgress() {
        cout << "Enter your weight for this week: ";
        double currentWeight = getPositiveInput("");
        weeklyProgress[getCurrentDate()] = currentWeight;

        displayWeeklyProgress();
    }

    void displayWeeklyProgress() {
        cout << "\nWeekly Progress for " << name << ":\n";
        for (const auto& entry : weeklyProgress) {
            cout << entry.first << ": " << entry.second << " kg" << endl;
        }
    }

    void generateMealPlan() {
        // Implement meal plan generation based on dietary requirements and preferences.
        // This is a placeholder for a more complex feature.
        cout << "\nGenerating a personalized meal plan for " << name << "...\n";
        // You can add your meal plan generation logic here.
        cout << "Meal plan: Breakfast - Oatmeal, Lunch - Grilled Chicken Salad, Dinner - Baked Salmon" << endl;
    }
};

int main() {
    HealthPulse healthPulse;

    healthPulse.welcomeMessage();
    healthPulse.collectHealthData();

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Track Weekly Progress\n";
        cout << "2. Display Diet Plan\n";
        cout << "3. Display Exercise Plan\n";
        cout << "4. Generate Meal Plan\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                healthPulse.trackWeeklyProgress();
                break;
            case 2:
                healthPulse.displayDietPlan();
                break;
            case 3:
                healthPulse.displayExercisePlan();
                break;
            case 4:
                healthPulse.generateMealPlan();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option.\n";
                break;
        }
    }
}
