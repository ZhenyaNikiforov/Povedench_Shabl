/*- Задание-3 (цепочка ответственности) -*/

#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

class LogMessage
{
private:
  string type = "";

public:
  LogMessage(const string &type)
  {
    this->type = type;
  };

  string message(const string &message)
  {
    return message;
  };

  string getType()
  {
    return this->type;
  };
};

class handlesErrors
{
private:
  LogMessage *ptrLM;

public:
  handlesErrors(LogMessage *ptrLM)
  {
    this->ptrLM = ptrLM;
    this->fatalError();
  };

  void fatalError()
  {
    if (this->ptrLM->getType() == "Fatal error")
    {
      string message = "Fatal`naya oshibka";
      throw invalid_argument(this->ptrLM->message(message));
      return;
    }
    this->error();
  };

  void error()
  {
    if (this->ptrLM->getType() == "Error")
    {
      string message = "soobshenie prostoj oshibki";
      ofstream outFile("error.txt");
      outFile << this->ptrLM->message(message);
      outFile.close();
      return;
    }
    this->warning();
  };

  void warning()
  {
    if (this->ptrLM->getType() == "Warning")
    {
      string warning = "Warning: soobschenie";
      cout << this->ptrLM->message(warning) << endl;
      return;
    }
    this->unknowMessage();
  };

  void unknowMessage()
  {
    if (this->ptrLM->getType() == "Unknow message")
    {
      string message = "Neizvestnoe soobchenie";
      throw invalid_argument(this->ptrLM->message(message));
      return;
    }
  }
};

int main()
{
  string fatalError = "Fatal error";
  string error = "Error";
  string warning = "Warning";
  string unknowMessage = "Unknow message";

  LogMessage *LogFatalError = new LogMessage(fatalError);
  LogMessage *LogError = new LogMessage(error);
  LogMessage *LogWarning = new LogMessage(warning);
  LogMessage *LogUnknowMessage = new LogMessage(unknowMessage);

  try
  {
    handlesErrors HEF(LogFatalError);
  }
  catch (const invalid_argument &e)
  {
    cout << e.what() << endl;
  }

  handlesErrors HEE(LogError);
  handlesErrors HEW(LogWarning);

  try
  {
    handlesErrors HEU(LogUnknowMessage);
  }
  catch (const invalid_argument &e)
  {
    cout << e.what() << endl;
  }

  delete LogFatalError;
  delete LogError;
  delete LogWarning;
  delete LogUnknowMessage;

  return 0;
}