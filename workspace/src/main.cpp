//============================================================================
// Name        : test1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <mysql/mysql.h>
#include <vector>
#include <string>
#include <stdlib.h>

#include "introInter.h"
#include "mainInter.h"


int main() {
	IntroInterface ii;
	MainInterface mi;
	ii.setMainInterface(mi);
	mi.setIntroInterface(ii);
	ii.hello();
	return 0;
}
