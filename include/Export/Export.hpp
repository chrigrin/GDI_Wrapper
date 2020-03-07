#pragma once

#ifndef GDIWRAPPER
#define GDIWRAPPER_API __declspec(dllexport)
#else
#define GDIWRAPPER_API __declspec(dllimport)
#endif