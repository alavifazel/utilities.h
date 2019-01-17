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
#include <iostream>

#ifdef BOOST_VERSION
#include <boost/algorithm/string/classification.hpp> */
#include <boost/algorithm/string/split.hpp> */
#endif

#define DUMP(a)								\
    do { std::cout << #a " is value " << (a) << std::endl; } while(false)

namespace afutils {
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

#ifdef BOOST_VERSION

    inline std::vector<std::string> textSplit(std::string s, std::string b)
    {
      std::vector<std::string> parts;
      boost::split(parts, s, boost::is_any_of(b), boost::token_compress_on);
      return parts;
    }

#endif

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
      static const std::string t = "0123456789ABCDEF";
        std::string output;
        for (size_t i = 0; i < input.size(); i++) {
            const unsigned char c = input[i];

            output.push_back(t[c >> 0b0100]); // (c >> 4) gets the binary of the first part
            output.push_back(t[c & 0b1111]);  // (c & 0b1111) gets the binary of the second part
        }
        return output;
    }


    template <typename T> 
      std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) 
      { 
	//os << "["; 
	for (int i = 0; i < v.size(); ++i) { 
	  os << v[i]; 
	  if (i != v.size() - 1) 
            os << "  "; 
	} 
	os << '\n'; // could be "]\n"
	os << '\n';
	return os; 
      }

    template <typename T> 
      std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& v) 
      {
	// os << '[';
	for (size_t i = 0; i < v.size(); ++i){
	  // os << "["; 
	  for (size_t j = 0; j < v[i].size(); ++j) { 
	    os << v[i][j];
	    if (j != v[i].size() - 1) 
	      os << "  "; 
	  } 
	  os << '\n';
	}
	os << '\n';
	return os; 
      }

    template <typename T> 
      std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<std::vector<T>>>& v) 
      {
	for (size_t i = 0; i < v.size(); ++i){
	  // os << '[';
	  for (size_t j = 0; j < v[i].size(); ++j){
	    // os << "["; 
	    for (size_t k = 0; k < v[i][j].size(); ++k) { 
	      os << v[i][j][k];
	      if (k != v[i][j].size() - 1) 
		os << "  "; 
	    } 
	    os << '\n';
	  }
	  os << '\n';
	}	     
	return os; 
      }

}
      

#endif
