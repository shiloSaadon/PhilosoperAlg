#include "pch.h"
#define EXE_FILENAME "D:\\Projects\\VisualStudioProjects\\SystemOperationProject\\Release\\SinglePhilosofer.exe"  // the singlePhilosofer path
#define NUM_PROCESSES 5

int main()
{
	PCHAR id = (PCHAR)malloc(sizeof(INT));
	STARTUPINFOA si; // the screen settings -> auto fill by the system
	PROCESS_INFORMATION pi[NUM_PROCESSES]; // process information -> auto fill by the system
	HANDLE* Mutexes[5];
	for (int i = 0;i < NUM_PROCESSES;i++) {
		Mutexes[i] = CreateMutexA(
			NULL, // default security attributes
			FALSE, // initially not owned
			id);
	}
	INT size = strlen(EXE_FILENAME) + 3;
	PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
	ZeroMemory(&si, sizeof(si)); // initialize the memory to zero (clean the vars)
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi)); // initialize the memory to zero (clean the vars)
	// create argument string
	for (int i = 0;i < NUM_PROCESSES;i++) {
		sprintf_s(param, size, "%s %d", EXE_FILENAME, i+1); // put the data inside param
		// Start the child process.
		CreateProcessA(NULL,
			param, // Command line
			NULL, // Process handle not inheritable
			NULL, // Thread handle not inheritable
			FALSE, // Set handle inheritance to FALSE
			0, // No creation flags
			NULL, // Use parent's environment block
			NULL, // Use parent's starting directory
			&si, // Pointer to STARTUPINFO structure
			&pi[i]); // Pointer to PROCESS_INFORMATION structure
	}
	WaitForMultipleObjects(
		NUM_PROCESSES,
		pi,
		TRUE,
		INFINITE);
	for (int i = 0;i < NUM_PROCESSES;i++) {
		ReleaseMutex(Mutexes[i]);
	}
	for (int i = 0; i < NUM_PROCESSES; i++)
	{
		CloseHandle(pi[i].hProcess);
		CloseHandle(pi[i].hThread);
	}
	free(param);
	return 0;

}