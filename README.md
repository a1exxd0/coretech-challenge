# coretech-challenge
Want to participate? [Click here!](https://www.coretechsec.com/operation-packet-storm) Feel free to look at my work and suggest things (or nick it for your own - please credit :) and thank you for looking!)

# Goals for the challenge
Most of all for me this is a learning experience. I'll be testing this for Ubuntu only, and will try make it as rigorous a project as possible. This means trying to stick to proper modern C++ consistently, as well as looking to employ multithreading and externam libraries where appropriate.

In terms of data I'll need to extract:
- Average packet size
- Total volume of data transmitted
- Most frequent destination IP
- Total number of packets broken down by transport layer protocol
- Any additional insights or anomalies

# Build instructions
Resolve your dependencies first! You'll need [GTest](https://github.com/google/googletest) and [Google Benchmark](https://github.com/google/benchmark) installed to build this. You'll also need [pcapplusplus](https://pcapplusplus.github.io/docs/install/linux) installed. For GTest and PcapPlusPlus, I'll provide instruction:
```sh
sudo apt update
sudo apt install libgtest-dev

sudo apt-get install libpcap-dev
git clone https://github.com/seladb/PcapPlusPlus --branch v23.09
cd PcapPlusPlus
cmake -S . -B build
cmake --build build
sudo cmake --install build
```
Then to build, navigate to the repository top directory, and run:
```sh
mkdir build
cd build
cmake ..
# build for release
cmake --build . --config release
```

### todo
Finish build instructions