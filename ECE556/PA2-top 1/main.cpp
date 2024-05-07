#include <iostream>
#include <string>
#include "fp.hpp"


int main(int argc, char** argv) {

  if (argc != 5) {
    std::cerr << "./fp [alpha value] [input.block name] [input.net name] [output file name] \n";
    exit(-1);
  }

  float alpha = std::atof(argv[1]);
  std::string input_block(argv[2]);
  std::string input_net(argv[3]);
  std::string output(argv[4]);

  fp::FP fp(alpha, input_block, input_net, output);
  fp.run();
  fp.dump();
  return 0;


}



