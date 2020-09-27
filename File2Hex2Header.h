#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

template <class _Ty, size_t _Size>
constexpr size_t countof(const _Ty(&)[_Size]) noexcept {
	return _Size;
}

void string_replace(std::string& strBig, const std::string& strsrc, const std::string& strdst)
{
	std::string::size_type pos = 0;
	std::string::size_type srclen = strsrc.size();
	std::string::size_type dstlen = strdst.size();

	while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}

void GetPathOrURLShortName(std::string strFullName, std::string& filename, std::string& name, std::string& suffix_str)
{
	if (strFullName.empty())
	{
		return;
	}
	string_replace(strFullName, "/", "\\");
	//1.获取不带路径的文件名
	std::string::size_type iPos = strFullName.find_last_of('\\') + 1;
	filename = strFullName.substr(iPos, strFullName.length() - iPos);

	//2.获取不带后缀的文件名
	name = filename.substr(0, filename.rfind("."));

	//3.获取后缀名
	suffix_str = filename.substr(filename.find_last_of('.') + 1);

}


std::string readfile(std::string fullname)
{
	std::fstream in(fullname.c_str(), std::ios::in | std::ios::binary);
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
void writefile(char* ctx, int len, std::string fullname)
{
	FILE* file = nullptr;
	fopen_s(&file, fullname.c_str(), "w");
	if (file)
	{
		fwrite(ctx, 1, len, file);
		fclose(file);
	}
}
void writefile(std::string ctx, std::string fullname)
{
	std::fstream out(fullname.c_str(), std::ios::out | std::ios::binary);
	if (out.is_open())
	{
		out << ctx;
	}
	out.close();
}

std::string Str2hex(std::string ctx, std::string _name)
{
	std::stringstream result;
	result << "#ifdef _MSC_VER" << "\n";
	result << "__declspec(align(4))" << "\n";
	result << "#else" << "\n";
	result << "__attribute__((aligned(4)))" << "\n";
	result << "#endif" << "\n";
	result << "//constexpr int bufsize = " << ctx.size() << ";" << "\n";
	result << "static const unsigned char " << _name << "[] = {" << "\n";
	unsigned char* data = (unsigned char*)ctx.data();
	for (size_t i = 0; i < ctx.length(); i++)
	{
		if (i != 0 && i % 20 == 0)
		{
			result << "\n";
		}
		char sub[7];
		sprintf_s(sub, " 0x%02x,", data[i]);
		result << sub;
	}
	result << "};";
	return result.str();
}

void File2Header(std::string fullname,std::string headerfile)
{
	std::string _filename, _name, _suffix_str;
	GetPathOrURLShortName(fullname, _filename, _name, _suffix_str);
	auto ctx = readfile(fullname);
	auto hex = Str2hex(ctx, _name);
	std::fstream out(headerfile.c_str(), std::ios::out | std::ios::binary);

	if (out.is_open())
	{
		out << "#pragma once" << "\n" << "\n";
		out << hex << "\n";
	}
	out.close();
}
