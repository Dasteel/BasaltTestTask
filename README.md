# BasaltTestTask
![qt5](https://img.shields.io/badge/QT-5.15.2-green) ![curl-7.79.1](https://img.shields.io/badge/curl-7.88.1-green) ![platform](https://img.shields.io/badge/platform-linux-orange)

Shared library for working with [REST API](https://db.altlinux.org/api /). Searches for unique packages for each of the two branches, and also searches for packages whose version in the first branch is greater than in the second. The result of the work is recorded in json files with the names of the architecture to which the selected packages belong.

## Build from source
## Requirements
+ **Recommended Qt 5.x.x or Qt 6**
+ **Cmake v3.6 <=**
+ **Curl v7.88.1 <=**

  **Note** : The program requires the installed package 'curl' version not lower than 7.88.1

## Building
	git clone https://github.com/Dasteel/BasaltTestTask.git
	cd BasaltTestTask
	mkdir build && cd build
	cmake ..
	cmake --build .
___

## CLI Usage
	./untitled4 -b1 "branch_1" -b2 "branch_2" -o "RESULT PATH"

*RESULT PATH* - path where to save the result of the program.

*branch_1* - the name of the first branch.

*branch_2* - the name of the second branch.
