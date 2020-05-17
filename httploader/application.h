#pragma once

namespace HttpLoader {

class Application : public QCoreApplication {
 public:
  Application(int& argc, char** argv);
};

}  // namespace HttpLoader
