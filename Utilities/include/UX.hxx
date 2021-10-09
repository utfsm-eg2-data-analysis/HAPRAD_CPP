#ifndef UX_HXX
#define UX_HXX

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** Global variables ***/

TString gTargetOption;
TString gParticle;

TString gProDir = getenv("PRODIR");

/*** Input-related functions ***/

void printUsage() {
  std::cout << "GetRC program. Usage is: " << std::endl;
  std::cout << std::endl;
  std::cout << "./GetRC -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetRC -t[D, A]" << std::endl;
  std::cout << "    filters liquid target or solid targets" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetRC -p[eta, omega]" << std::endl;
  std::cout << "    selects particle analysis" << std::endl;
  std::cout << std::endl;
}

void parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./GetRC -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:p:")) != -1) switch (c) {
      case 'h':
        printUsage();
        exit(0);
        break;
      case 't':
        gTargetOption = optarg;
        break;
      case 'p':
        gParticle = optarg;
        break;
      default:
        std::cerr << "Unrecognized argument. Execute ./GetRC -h to print help." << std::endl;
        exit(0);
        break;
    }
}

void printOptions() {
  std::cout << "Executing GetRC program. The chosen parameters are: " << std::endl;
  std::cout << "  gTargetOption = " << gTargetOption << std::endl;
  std::cout << "  gParticle     = " << gParticle << std::endl;
  std::cout << std::endl;
}

#endif
