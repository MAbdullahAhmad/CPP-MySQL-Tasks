// Headers
#include "mysql_connection.h"
#include <stdlib.h>
#include <string.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

// Connection Class
class Connection{
  public:
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  // Constructor
  Connection(){
   // Connect to Database
    try {
      this->driver = get_driver_instance();
      con = driver->connect("tcp://127.0.0.1:3306", "root", "");
      con->setSchema("c_plus_plus");
    } catch (sql::SQLException &e) {
      this->publish_error(e);
    }
  }

  // Runs a query (returns true of successful)
  bool query(const string sql){
    try {
      stmt = con->createStatement();
      res = stmt->executeQuery(sql);
      return true;
    } catch (sql::SQLException &e) {
      if(e.getErrorCode()==0){
        return true;
      }
      this->publish_error(e);
      return true;
    }
  }

  // Helper function to print SQL errors when they are in the way
  void publish_error(sql::SQLException& e){
    if(e.getErrorCode()==0){
      return;
    }
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }
};
