// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include "EthernetInterface.h"
#include "iothub_client_sample_http.h"
#include "NTPClient.h"

int setupRealTime(void)
{
	int result;

	(void)printf("setupRealTime begin\r\n");
	if (EthernetInterface::connect())
	{
		(void)printf("Error initializing EthernetInterface.\r\n");
		result = __LINE__;
	}
	else
	{
		(void)printf("setupRealTime NTP begin\r\n");
		NTPClient ntp;
		if (ntp.setTime("0.pool.ntp.org") != 0)
		{
			(void)printf("Failed setting time.\r\n");
			result = __LINE__;
		}
		else
		{
			(void)printf("set time correctly!\r\n");
			result = 0;
		}
		(void)printf("setupRealTime NTP end\r\n");
		EthernetInterface::disconnect();
	}
	(void)printf("setupRealTime end\r\n");

	return result;
}

int main(void)
{
	(void)printf("Initializing mbed specific things...\r\n");

	if (EthernetInterface::init())
	{
		(void)printf("Error initializing EthernetInterface.\r\n");
		return -1;
	}

	if (setupRealTime() != 0)
	{
		(void)printf("Failed setting up real time clock\r\n");
		return -1;
	}

	iothub_client_sample_http_run();

	return 0;
}
