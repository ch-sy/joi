
#include "joi.h"
#include <iostream>
#include <entityx/entityx.h>
#include <filesystem>

int main(int argc, char* argv[]) {
  std::filesystem::create_directory("../log");
  FLAGS_log_dir = "../log";
  google::InitGoogleLogging(argv[0]);
  LOG(INFO) << "Start journey on ice";
	Joi joi;
	joi.run();
	return 0;
}