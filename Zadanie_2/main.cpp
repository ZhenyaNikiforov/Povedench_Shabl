#include <iostream>
#include <fstream>

class Observer
{
public:
  ~Observer() {}; //"золотое" правило?
  virtual void onWarning(const std::string &message) {}
  virtual void onError(const std::string &message) {}
  virtual void onFatalError(const std::string &message) {}
};

class ObsWarn : public Observer
{
public:
  void onWarning(const std::string &message) override
  {
    std::cout << message << std::endl;
  }
};

class ObsErr : public Observer
{
public:
  void onError(const std::string &message) override
  {
    std::ofstream outFile("error.txt");
    outFile << message;
    outFile.close();
  }
};

class ObsFatErr : public Observer
{
public:
  void onFatalError(const std::string &message) override
  {
    std::ofstream outFile("fatalError.txt");
    outFile << message;
    outFile.close();

    std::cout << message << std::endl;
  }
};

class publisher
{
private:
  Observer *ptrWarn;
  Observer *ptrErr;
  Observer *ptrFatErr;

public:
  publisher(Observer *ptrWarn, Observer *ptrErr, Observer *ptrFatErr)
  {
    this->ptrWarn = ptrWarn;
    this->ptrErr = ptrErr;
    this->ptrFatErr = ptrFatErr;
  };
  void warning(const std::string &message)
  {
    this->ptrWarn->onWarning(message);
  };

  void error(const std::string &message)
  {
    this->ptrErr->onError(message);
  };

  void fatalError(const std::string &message)
  {
    this->ptrFatErr->onFatalError(message);
  };
};

int main()
{
  Observer *warn = new ObsWarn;
  Observer *err = new ObsErr;
  Observer *fatErr = new ObsFatErr;

  std::string warning = "Warning!";
  std::string error = "ERROR!";
  std::string fatalError = "FATAL ERROR!!!";

  publisher PBL(warn, err, fatErr);

  PBL.warning(warning);
  PBL.error(error);
  PBL.fatalError(fatalError);

  delete warn;
  delete err;
  delete fatErr;

  return 0;
}