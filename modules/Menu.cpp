#include <string>
using namespace std;

// Menu Class
class Menu{
  private:
  int optionCounter = 0;
  int indent = 0;

  public:
  // Prints Header
  void header(const string str){
    cout << str << endl;
    cout << setw(str.size()+1) << setfill('=') << " " << endl << endl;
  }

  // Prints Title
  void title(const string str){
    cout << endl << str << endl;
    cout << setw(str.size()+1) << setfill('-') << " " << endl << endl;
  }

  // Used to write a row (paragraph)
  void row(const string row){
    cout << row << endl;
  }

  // Show one option (auto-numbering) (Polymorphism: many functions with same name)
  void option(const string option){
    cout << ++this->optionCounter << ". " << option << endl;
  }
  void option(const string option, bool resetCounter){
    if(resetCounter){
      this->optionCounter=0;
    }
    this->option(option);
  }
  void option(const string option, int count){
    this->optionCounter=count-1;
    this->option(option);
  }

  // Input from User
  string input(){
    string result;

    cout << "Enter: ";
    cin >> result;

    return result;
  }
  string input(const string label){
    string result;

    cout << "Enter " << label << ": ";
    cin >> result;

    return result;
  }

  // Input and Matches with second paremeter
  bool inputMatch(const string label, const string match){
    return this->input(label) == match;
  }

  // Display a message of any type (e.g., SUCCESS, ERROR, INFO, etc)
  void message(const string type, const string message){
    cout << "[" << type << "]: " << message << endl;
  }

  // Message of SUCCESS type
  void success(const string message){
    this->message("SUCCESS", message);
  }

  // Message of ERROR type
  void error(const string message){
    this->message("ERROR", message);
  }

  // ENDs a Menu
  void end(){
    this->optionCounter = 0;
    cout << endl;
  }

  // Start a List
  void list(){
    this->indentation();
    cout << "[\n";
    this->indent++;
  }
  // End a List (Polymorphism)
  void list_end(){
    this->indent--;
    this->indentation();
    cout << "]\n";
  }
  void list_end(bool next){
    if(next){
      this->indent--;
      this->indentation();
      cout << "],\n";
    } else this->list_end();
  }

  // Start a Document
  void document(){
    this->indentation();
    cout << "{\n";
    this->indent++;
  }
  // End a Document (Polymorphism)
  void document_end(){
    this->indent--;
    this->indentation();
    cout << "}\n";
  }
  void document_end(bool next){
    if(next){
      this->indent--;
      this->indentation();
      cout << "},\n";
    } else this->document_end();
  }

  // Indent Used before every entry / document if using indentation
  void indentation(){
    for(int i=0; i<this->indent; i++){
      cout << "  ";
    }
  }

  // Display one Entry (key-value pair) of Document (Polymorphism)
  void entry(const string key, const string value){
    this->indentation();
    cout << '"' << key << '"' << ": " << '"' << value << "\",\n";
  }
  void entry(const string key, const string value, bool next){
    if(next==false){
      this->indentation();
      cout << '"' << key << '"' << ": " << '"' << value << "\"\n";
    } else this->entry(key, value);
  }
};

/*
  Abdullah Ahmad
  Dec 14th 2021
*/