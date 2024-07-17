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
To run, paste the `packet-storm.pcap` file into `testfiles/` and navigate to your build directory. Run:
```sh
src/ctc
```

# READ THESE NOTES
I am very aware this is flawed. Ideally, I'd spend more time on this but work is catching up a bit so won't be able to do that :( 

Let's hope it'll suffice for now! In future I could implement a multithreaded sort through std::sort and execution parameters, or maybe leverage some kind of filter for bad packets. I looked at the source code for the Pcap files and this looks like a pain to handle and so I didn't want to spend more time than necessary on it, so as a temporary solution I've moved the std output to `/dev/null` to ignore, and restored stream after.

Further analysis of data found that TCP and UDP protocols made up all 1,000,000 of the entries for transport layer packets.

Ideally I would have also tested and benchmarked this more rigorously, but again time constraints!