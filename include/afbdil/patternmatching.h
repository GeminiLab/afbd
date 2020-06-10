#pragma once

#include "def.h"

#include <iostream>

using namespace afbd;

void reportDefect(std::shared_ptr<afbd::Module> module, std::string str, bool is_error, int line);
void clkCheck(std::shared_ptr<afbd::Module> module);
void typeCheck(std::shared_ptr<afbd::Module> module);
void passCheck(std::shared_ptr<afbd::Module> module);
void blockCheck(std::shared_ptr<afbd::Module> module);

