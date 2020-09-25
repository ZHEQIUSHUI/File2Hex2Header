#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

std::string readfile(std::string filename)
{
	std::fstream in(filename.c_str(), std::ios::in | std::ios::binary);
	std::stringstream ctx;
	if (in.is_open())
	{
		char ch;
		while (in.get(ch))
			ctx.put(ch);
	}
	in.close();
	return ctx.str();
}
void writefile(char* ctx, int len, std::string filename)
{
	FILE* file = nullptr;
	fopen_s(&file, filename.c_str(), "w");
	if (file)
	{
		fwrite(ctx, 1, len, file);
		fclose(file);
	}
}
void writefile(std::string ctx, std::string filename)
{
	std::fstream out(filename.c_str(), std::ios::out | std::ios::binary);
	if (out.is_open())
	{
		out << ctx;
	}
	out.close();
}

std::string Str2hex(std::string ctx)
{
	std::stringstream result;
	result << "#ifdef _MSC_VER" << std::endl;
	result << "__declspec(align(4))" << std::endl;
	result << "#else" << std::endl;
	result << "__attribute__((aligned(4)))" << std::endl;
	result << "#endif" << std::endl;
	result << "static const unsigned char buf[]={" << std::endl;
	for (size_t i = 0; i < ctx.length(); i++)
	{
		char sub[100];
		sprintf_s(sub, " 0x%0x,", (unsigned char)ctx[i]);
		result << sub;
		if (i != 0 && i % 20 == 0)
		{
			result << "\n";
		}
	}
	result << "};";
	return result.str();
}

void File2Header(std::string filename,std::string headerfile)
{
	auto ctx = readfile(filename);
	auto hex = Str2hex(ctx);
	std::fstream out(headerfile.c_str(), std::ios::out | std::ios::binary);

	if (out.is_open())
	{
		out << "#pragma once" << std::endl << std::endl;
		out << hex << std::endl;
	}
	out.close();
}
