#include <iostream>
#include <fstream>

class LogCommand
{
public:
  virtual ~LogCommand() = default;
  virtual void print(const std::string &message) = 0;
};

class LogCommandConsole : public LogCommand
{
public:
  void print(const std::string &message) override
  {
    std::cout << message << std::endl;
  }
};

class LogCommandFile : public LogCommand
{
public:
  void print(const std::string &message) override
  {
    std::ofstream outFile("out.txt");

    if (outFile.is_open() != true)
    {
      outFile.close();
      return;
    }

    outFile << message;
    outFile.close();
    std::cout << "file sozdan i zapisan." << std::endl;
    return;
  }
};

void print(LogCommand *ptr)
{
  std::string message = "Privet!";
  ptr->print(message);
};

int main()
{
  LogCommand *LCC = new LogCommandConsole;
  LogCommand *LCF = new LogCommandFile;

  print(LCC);
  print(LCF);

  delete LCC;
  delete LCF;

  return 0;
}