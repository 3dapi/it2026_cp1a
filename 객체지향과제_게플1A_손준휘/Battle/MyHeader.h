#pragma once
#include <string>
#define DOSKIP false

int InputInt(std::string announce = "");

std::string InputString(std::string announce ="");

void Messege(std::string input);

void ToNext(const bool doSkip = DOSKIP);

std::string ToSignedNumber(const int num);