// TO-DO APPLICATION USIING C++
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Task {
public:
    string description;
    bool isCompleted;
    time_t reminder;

    Task(string desc) {
        description = desc;
        isCompleted = false;
        reminder = 0;
    }
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(string description) {
        Task newTask(description);
        tasks.push_back(newTask);
        cout << "Task added: " << description << endl;
    }

    void editTask(int index, string newDescription) {
        if (index < 0 || index >= tasks.size()) {
            cout << "Invalid task index!" << endl;
            return;
        }
        tasks[index].description = newDescription;
        cout << "Task edited: " << newDescription << endl;
    }

    void deleteTask(int index) {
        if (index < 0 || index >= tasks.size()) {
            cout << "Invalid task index!" << endl;
            return;
        }
        cout << "Task removed: " << tasks[index].description << endl;
        tasks.erase(tasks.begin() + index);
    }

    void completeTask(int index) {
        if (index < 0 || index >= tasks.size()) {
            cout << "Invalid task index!" << endl;
            return;
        }
        tasks[index].isCompleted = true;
        cout << "Task completed: " << tasks[index].description << endl;
    }

    void setReminder(int index, time_t reminderTime) {
        if (index < 0 || index >= tasks.size()) {
            cout << "Invalid task index!" << endl;
            return;
        }
        tasks[index].reminder = reminderTime;
        cout << "Reminder set for task: " << tasks[index].description << endl;
    }

    void displayTasks() {
        if (tasks.empty()) {
            cout << "No tasks to display!" << endl;
            return;
        }
        cout << "\n--- To-Do List ---" << endl;
        for (int i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].description 
                 << (tasks[i].isCompleted ? " [Completed]" : "") 
                 << (tasks[i].reminder ? " [Reminder set]" : "") << endl;
        }
        cout << "------------------\n" << endl;
    }

    void checkReminders() {
        time_t now = time(0);
        for (int i = 0; i < tasks.size(); ++i) {
            if (tasks[i].reminder != 0 && tasks[i].reminder <= now) {
                cout << "Reminder: " << tasks[i].description << " is due now!" << endl;
                tasks[i].reminder = 0;  // Reset reminder after notifying
            }
        }
    }
};

int main() {
    ToDoList toDoList;
    int choice;

    do {
        toDoList.checkReminders();  // Check reminders before displaying the menu

        cout << "1. Add Task\n2. Edit Task\n3. Delete Task\n4. Complete Task\n5. Set Reminder\n6. Display Tasks\n7. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string description;
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, description);
            toDoList.addTask(description);
            break;
        }
        case 2: {
            int index;
            string newDescription;
            toDoList.displayTasks();
            cout << "Enter task index to edit: ";
            cin >> index;
            cout << "Enter new task description: ";
            cin.ignore();
            getline(cin, newDescription);
            toDoList.editTask(index - 1, newDescription);
            break;
        }
        case 3: {
            int index;
            toDoList.displayTasks();
            cout << "Enter task index to delete: ";
            cin >> index;
            toDoList.deleteTask(index - 1);
            break;
        }
        case 4: {
            int index;
            toDoList.displayTasks();
            cout << "Enter task index to complete: ";
            cin >> index;
            toDoList.completeTask(index - 1);
            break;
        } 
        case 5: {
            int index;
            int hour, minute;
            toDoList.displayTasks();
            cout << "Enter task index to set reminder: ";
            cin >> index;
            cout << "Enter reminder time (hour and minute): ";
            cin >> hour >> minute;

            time_t now = time(0);
            tm* localtm = localtime(&now);
            localtm->tm_hour = hour;
            localtm->tm_min = minute;
            localtm->tm_sec = 0;

            time_t reminderTime = mktime(localtm);
            toDoList.setReminder(index - 1, reminderTime);
            break;
        }
        case 6:
            toDoList.displayTasks();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);   
}
