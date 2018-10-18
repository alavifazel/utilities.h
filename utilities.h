#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <thread>
#include <sstream>
#include <cstring>
#include <string>
#include <bitset>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace afutil {
    inline std::string executeCommand(const char *cmd)
    {
        std::array<char, 128> buffer;
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
          throw std::runtime_error("popen() failed!");
        }
        while (!feof(pipe.get())) {
            if (fgets(buffer.data(), 128, pipe.get()) != nullptr) {
                result += buffer.data();
            }
        }
        return result;
    }

    inline std::vector<std::string> textSplit(std::string s, std::string b)
    {
      std::vector<std::string> parts;
      boost::split(parts, s, boost::is_any_of(b), boost::token_compress_on);
      return parts;
    }

    inline void sleep(int x){
      std::this_thread::sleep_for(std::chrono::milliseconds(x));
    }


    inline std::bitset<8> char_to_bin(const char c)
    {
        std::bitset<8> x(c);
        return x;
    }

    inline std::string string_to_hex(const std::string input)
    {
        static const string t = "0123456789ABCDEF";
        std::string output;
        for (size_t i = 0; i < input.size(); i++) {
            const unsigned char c = input[i];

            output.push_back(t[c >> 0b0100]); // (c >> 4) gets the binary of the first part
            output.push_back(t[c & 0b1111]);  // (c & 0b1111) gets the binary of the second part
        }
        return output;
    }
}

#endif
