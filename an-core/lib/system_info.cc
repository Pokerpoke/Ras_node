#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

#include "system_info.h"

namespace an
{
namespace core
{

system_info::system_info()
{
}

int system_info::popen_to_char(const char *cmd, char *out)
{
	FILE *fp;
	unsigned int index = 0;

	if ((fp = popen(cmd, "r")) == NULL)
	{
		fprintf(stderr, "Pipe open failed.");
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		while (!feof(fp))
		{
			out[index] = fgetc(fp);
			if (out[index] != '\0')
			{
				index++;
			}
		}
		out = strtok(out, "\n");
	}

	pclose(fp);

	return 0;
}

int system_info::os_info(char *out)
{
	const char *cmd = "uname -sr";

	popen_to_char(cmd, out);

	return 0;
}

int system_info::memory_used(long &out)
{
	char temp[80];

	const char *cmd = "free | grep Mem";
	popen_to_char(cmd, temp);
	strtok(temp, ":");
	strtok(NULL, " ");
	out = atoi(strtok(NULL, " "));

	return 0;
}

int system_info::memory_total(long &out)
{
	char temp[80];

	const char *cmd = "free | grep Mem";
	popen_to_char(cmd, temp);
	strtok(temp, ":");
	out = atoi(strtok(NULL, " "));

	return 0;
}

system_info::~system_info()
{
}
}
}
