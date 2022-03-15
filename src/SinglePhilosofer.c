#include "pch.h"
#include <stdio.h>
#define TIMESTOEAT 3
int main(int argc, char* argv[])
{
	INT size = sizeof(INT);
	PCHAR snum1 = (PCHAR)malloc(size);
	PCHAR snum2 = (PCHAR)malloc(size);
	if (argc != 2) {
		printf("Incorrect number of arguments\n");
		return 0;
	}
	int myId = atoi(argv[1]);
	sprintf_s(snum1,size,"%d", myId - 1);
	sprintf_s(snum2, size, "%d", myId % 5);
	//itoa(myId % 5,snum2, 10);
	HANDLE hMyMutex1 = CreateMutexA(
		NULL, // default security attributes
		FALSE, // initially not owned
		snum1);
	HANDLE hMyMutex2 = CreateMutexA(
		NULL, // default security attributes
		FALSE, // initially not owned
		snum2);// get the handle to the mutex  // get the result wathear the mutex is free or not 
	DWORD waitResult1;
	DWORD waitResult2;
	for (int i = 0;i < TIMESTOEAT;i++) {
		while (TRUE) { // if the mutex is free it catch the mutex
			waitResult1 = WaitForSingleObject(
				hMyMutex1,
				0);
			if (waitResult1 == WAIT_OBJECT_0) {
				Sleep(1000);
				waitResult2 = WaitForSingleObject(
					hMyMutex2,
					0);
				if (waitResult2 == WAIT_OBJECT_0) {
					printf("Philosof %d, eat = %dth time\n", myId, i);
					ReleaseMutex(hMyMutex2);
					ReleaseMutex(hMyMutex1);
					break;
				}
				ReleaseMutex(hMyMutex2);
				ReleaseMutex(hMyMutex1);
			}
			waitResult2 = WaitForSingleObject(
				hMyMutex2,
				0);
			if (waitResult2 == WAIT_OBJECT_0) {
				waitResult1 = WaitForSingleObject(
					hMyMutex1,
					0);
				if (waitResult1 == WAIT_OBJECT_0) {
					printf("Philosof %d, eat = %dth time\n", myId, i);
					ReleaseMutex(hMyMutex1);
					ReleaseMutex(hMyMutex2);
					break;
				}
				ReleaseMutex(hMyMutex1);
				ReleaseMutex(hMyMutex2);
			}
		}
	}
	CloseHandle(hMyMutex1);
	CloseHandle(hMyMutex2);
	return 1;
}
