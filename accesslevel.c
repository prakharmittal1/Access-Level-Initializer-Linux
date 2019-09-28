#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "accesslevel.h"
#include <stdlib.h>

//library functions

int set_access_level(int pid, int new_level)
{
	//return new_level on success and -1 otherwise
	long temp = syscall(335, pid, new_level);
	int temp2 = (int)temp;
	return temp2;
}

int get_access_level(int pid)
{
	//return access level on success, -1 if fails
	printf("\nInside get_access_level library function pid : %d", pid);

	long temp = syscall(336, pid);

	int finally = (int)temp;
	return finally;
}




//harness functions


//{ call number, number of parameters, parameter1, parameter2} 
int* retrieve_set_access_params (int pid, int new_level)
{
	//return an int array of 2-4 values that can be used to make the set_access_level syscall
	//syscall(335, PID, newlevel) returns a long integer
	int *params = malloc(4);
	params[0] = 332;
	params[1] = 2;
	params[2] = pid;
	params[3] = new_level;
	return params;
}


int* retrieve_get_access_params(int pid)
{
	//return an int array of 2-4 values that can be used to make the get_access_level syscall
	int *params = malloc(3);
	params[0] = 333;
	params[1] = 1;
	params[2] = pid;
	return params;
}


int interpret_set_access_result (int ret_value)
{
	//after making the sys call, pass the return value from the syscall to this function call.
	//This should return set_access_level's interpretation of the sys call completing with return value ret_value
	if(ret_value == -1)
	{
		printf("The access level was not able to be modified.\n");
		return ret_value;
	}
	if(ret_value >= 0)
	{
		printf("The access level was changed to be %d\n.", ret_value);
		return ret_value;
	}
	return -1;

}


int interpret_get_access_result (int ret_value)
{
	//same as above but for get_access_level
	if(ret_value == -1)
	{
		printf("The retrieval of the access level failed.\n");
		return ret_value;
	}
	if(ret_value >= 0)
	{
		printf("The access level is %d\n", ret_value);
		return ret_value;
	}
	 return -1;
}
