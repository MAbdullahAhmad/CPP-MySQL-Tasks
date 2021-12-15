// Headers
#include <iostream>
#include <iomanip>
#include "modules/Connection.cpp"
#include "modules/Menu.cpp"

using namespace std;

// Functions
string displayMenu();
void addTask();
void allTasks();
void removeTask();

// Objects
Connection *myCon;
Menu *menu;

// Main
int main(){
  // Variables
  string command;

  // Creating Instances
  menu = new Menu();
  myCon = new Connection();

  // Print Header
  menu->header("Todo App");

  // Menu Loop
  while (true) {
    command = displayMenu();
    menu->end();

    if (command == "4"){
      menu->row("Goodbye...");
      break;
    }if (command == "1"){
      addTask();
    } else if (command == "2"){
      allTasks();
    } else if (command == "3"){
      removeTask();
    }
  }
  return 0;
}

// Function: Display Menu
string displayMenu(){
  menu->title("Main Menu:");
  menu->row("Select any One Option:");
  menu->option("Add a Task");
  menu->option("View all Tasks");
  menu->option("Remove a Task");
  menu->option("Quit");
  return menu->input("Your Choice");
}

// Function Add Task
void addTask(){
  string taskName;
  string taskDescription;
  string sql;

  menu->title("Add Task:");
  taskName = menu->input("Name of Task");
  taskDescription = menu->input("Description: ");

  sql = "INSERT INTO tasks(task, description) VALUES ('" + taskName + "', '" + taskDescription + "')";

  if(myCon->query(sql)){
    menu->success("Task Added Successfully!");
  } else {
    menu->error("Unable to Add Task!");
  }
  menu->end();
}

// Function : All Tasks
void allTasks(){
  menu->title("All Tasks:");
  menu->row("Your Tasks are as follow:");

  myCon->query("SELECT * from tasks");

  menu->list();
  while(myCon->res->next()){
    menu->document();
    menu->entry("id", myCon->res->getString("id"));
    menu->entry("task", myCon->res->getString("task"));
    menu->entry("description", myCon->res->getString("task"), false);
    menu->document_end(true);
  }
  menu->list_end();
}

// Function: Remove Task
void removeTask(){
  string sql;
  int id;
  menu->title("Remove Task:");

  cout << "Enter Task-ID: ";
  cin >> id;

  sql = "DELETE FROM tasks WHERE id=" + to_string(id);

  if(myCon->query(sql)){
    menu->success("Task Removed Successfully!");
  } else {
    menu->error("Unable to Removed Task!");
  }
  menu->end();
}


/*
  Two modules are used in this program (that are in modules directory)
*/
