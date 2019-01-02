// Kristy Li
// Multi-threading Application Project: Stimulating multi-threading with producer and consumer

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#define MAX_THREADS 2

using namespace std;

int counterLimit = 0;
int counter = 0;
int bufferSize;
int *buffer;
int in = 0;
int out = 0;

DWORD WINAPI producerThread(LPVOID);
DWORD WINAPI consumerThread(LPVOID);

HANDLE hThreads[MAX_THREADS];
DWORD id[MAX_THREADS];

DWORD waiter;

int main()
{
    srand(time(0));
    cout << "Enter the buffer size: ";
    cin >> bufferSize;
    buffer = (int *) malloc(bufferSize * sizeof(int));

    cout << "Enter the counter limit: ";
    cin >> counterLimit;

    cout << endl;

    hThreads[0] = CreateThread(NULL, 0, producerThread, (LPVOID)0, NULL, &id[0]);
    hThreads[1] = CreateThread(NULL, 0, consumerThread, (LPVOID)0, NULL, &id[1]);

    waiter = WaitForMultipleObjects(MAX_THREADS, hThreads, TRUE, INFINITE);

    for(int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreads[i]);
    }

    cout << "\nThread ended (producerThread)..." << endl;
    cout << "Thread started (consumerThread)...\n" << endl;

    system("pause");
    return 0;
}

DWORD WINAPI producerThread(LPVOID n)
{
    cout << "Thread started (producerThread)...\n" << endl;

    while(counter < counterLimit && counter < bufferSize)
    {
        while(((in + 1) % bufferSize) == out);
        int nextProduced = rand() % 10 + 1;
        Sleep(nextProduced * 400);
        buffer[in] = nextProduced;
        cout << "producerThread has produced " << nextProduced << endl;
        in = (in + 1) % bufferSize;
        counter++;
    }

    return (DWORD)n;
}

DWORD WINAPI consumerThread(LPVOID n)
{
    cout << "Thread started (consumerThread)..." << endl;

    int counter = 0;
    while (counter < counterLimit && counter < bufferSize)
    {
        while(in == out);
        Sleep(rand() % 400);
        int nextConsumed = buffer[out];
        cout << "consumerThread has consumed " << nextConsumed << endl;
        out = (out + 1) % bufferSize;
        counter++;
    }

    if (counterLimit > bufferSize)
    {
        cout << "The buffer is full." << endl;
    }

    return (DWORD)n;
}
