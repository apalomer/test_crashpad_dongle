#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include "crashpad_client.h"

void initializeCrashpad()
{
  const std::string dataDir = "crashpad";
  const auto db = dataDir + "/metrics/db";
  const auto metrics = dataDir + "/crash/metrics";
  std::cout << "Crashpad data dir: " << db << std::endl;
  std::cout << "Crashpad crash dir: " << metrics << std::endl;
  std::vector<std::string> args;

#ifdef _WIN32
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring crash_pad_handler(L"crashpad_handler.exe");
  std::wstring database(converter.from_bytes(db.toStdString()));
  std::wstring metric(converter.from_bytes(metrics.toStdString()));
#else
  std::string crash_pad_handler("crashpad_handler");
  std::string database(db);
  std::string metric(metrics);
#endif

  crashpad::CrashpadClient cpc;
  cpc.StartHandler(base::FilePath(crash_pad_handler),  // Relative path to a Crashpad handler executable
                   base::FilePath(database),           // Directory to Crashpad database
                   base::FilePath(metric),             // Directory where metrics files can be stored
                   "",                                 // URL of the HTTP upload server
                   {},                                 // Annonations to include in the crash report
                   args,
                   true,  // The program will be restarted if it crash
                   true);
}

int main()
{
  initializeCrashpad();
  std::cout << "Hello world" << std::endl;
  return EXIT_SUCCESS;
}
