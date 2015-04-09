/******************************************************************************
**  main.cpp
**  SpiraFRP v1.0.0
**
**  Created by ktnyt on 2015/04/04
**  Copyright (c) 2015 Kotone Itaya. All rights reserved.
**
**  This file is part of SpiraFRP.
**
**  SpiraFRP is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  SpiraFRP is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with SpiraFRP.  If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

#include <iostream>
#include "spira.hpp"

int main() {
  spira::stream<std::string> streamA;
  spira::stream<std::string> streamB(spira::DUPLICATES::SKIP);
  spira::stream<std::string> streamC(streamA, spira::DUPLICATES::SKIP);
  spira::stream<std::string> stream1(streamB, streamC); // Merge
  spira::stream<int> stream2(stream1, std::function<int(std::string)>([](std::string value){return value.length();})); // Map (string -> int)
  spira::stream<std::pair<std::string, int> > stream3(stream1, stream2); // Zip both
  spira::stream<std::pair<std::string, int> > stream4(stream1, stream2, spira::SAMPLED_BY::FIRST); // Zip first
  spira::stream<std::pair<std::string, int> > stream5(stream1, stream2, spira::SAMPLED_BY::SECOND); // Zip second
  spira::stream<std::string> stream6(stream1, std::function<bool(std::string)>([](std::string value){return value == "Hoge";})); // Filter
  spira::stream<int> stream7(stream2, 100, std::function<int(int, int)>([](int v1, int v2){return v1 + v2;})); // Scan
  spira::stream<bool> stream8(stream7, std::function<bool(int)>([](int value){return value < 110;})); // Map (int -> bool)
  spira::stream<int> stream9(stream7, stream8, spira::TAKE_WHILE::TRUE); // While

  streamA.bind([](std::string value){std::cout << "Stream A: " << value << std::endl;});
  streamB.bind([](std::string value){std::cout << "Stream B: " << value << std::endl;});
  streamC.bind([](std::string value){std::cout << "Stream C: " << value << std::endl;});
  stream1.bind([](std::string value){std::cout << "Stream 1: " << value << std::endl;});
  stream2.bind([](int value){std::cout << "Stream 2: " << value << std::endl;});
  stream3.bind([](std::pair<std::string, int> value){std::cout << "Stream 3: " << value.first << ":" << value.second << std::endl;});
  stream4.bind([](std::pair<std::string, int> value){std::cout << "Stream 4: " << value.first << ":" << value.second << std::endl;});
  stream5.bind([](std::pair<std::string, int> value){std::cout << "Stream 5: " << value.first << ":" << value.second << std::endl;});
  stream6.bind([](std::string value){std::cout << "Stream 6 captured " << value << std::endl;});
  stream7.bind([](int value){std::cout << "Stream 7: " << value << std::endl;});
  stream8.bind([](bool value){std::cout << "Stream 8: " << value << std::endl;});
  stream9.bind([](int value){std::cout << "Stream 9: " << value << std::endl;});

  streamA.push("Hoge");
  streamB.push("Fuga");
  streamB.push("Fuga");
  streamC.push("Hoge");
  streamC.push("Fuga");
  streamC.push("Hogera");

  return 0;
}
