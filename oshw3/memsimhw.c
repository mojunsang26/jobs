//
// Virual Memory Simulator Homework
// Two-level page table system
// Inverted page table with a hashing system
// Student Name:
// Student Number:
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define PAGESIZEBITS 12 // page size = 4Kbytes
#define VIRTUALADDRBITS 32 // virtual address space size = 4Gbytes


struct pageTableEntry {
	int level; // page table level (1 or 2)
	char valid;
	struct pageTableEntry *secondLevelPageTable; // valid if this entry is for the first level page table(level = 1)
	int frameNumber; // valid if this entry is for the second level page table(level = 2)
};
struct pageTableEntry *(* firstPageEntry);    //엔트리 테이블의 테이블이므로 **  ( 프로세스 수 만큼 동적할당 후 각프로세스의 첫 10비트만큼 동적할당)

struct framePage {
	int number; // frame number
	int pid; // Process id that owns the frame
	int virtualPageNumber; // virtual page number using the frame
	struct framePage *lruLeft; // for LRU circular doubly linked list
	struct framePage *lruRight; // for LRU circular doubly linked list
};


struct invertedPageTableEntry {
	int pid; // process id
	int virtualPageNumber; // virtual page number
	int frameNumber; // frame number allocated
	struct invertedPageTableEntry *next;
};


struct procEntry {
	char *traceName; // the memory trace name
	int pid; // process (trace) id
	int ntraces; // the number of memory traces
	int num2ndLevelPageTable; // The 2nd level page created(allocated);
	int numIHTConflictAccess; // The number of Inverted Hash Table Conflict Accesses
	int numIHTNULLAccess; // The number of Empty Inverted Hash Table Accesses
	int numIHTNonNULLAcess; // The number of Non Empty Inverted Hash Table Accesses
	int numPageFault; // The number of page faults
	int numPageHit; // The number of page hits
	struct pageTableEntry *firstLevelPageTable;
	FILE *tracefp;
};


struct framePage *oldestFrame; // the oldest frame pointer

int firstLevelBits, phyMemSizeBits, numProcess;

void initPhyMem(struct framePage *phyMem, int nFrame) {
	int i;
	for (i = 0; i < nFrame; i++) {
		phyMem[i].number = i;
		phyMem[i].pid = -1;
		phyMem[i].virtualPageNumber = -1;
		phyMem[i].lruLeft = &phyMem[(i - 1 + nFrame) % nFrame];
		phyMem[i].lruRight = &phyMem[(i + 1 + nFrame) % nFrame];
	}
	oldestFrame = &phyMem[0];
}
void secondLevelVMSim(struct procEntry *procTable, struct framePage *phyMemFrames) {
	
	while (첫번째로 끝나는 프로세스 생길때까지) {
		int i;

		for (i = 0; i < 프로세스개수; ++) {

			//n번째 가상주소 읽어오기
			unsigned addr;
			char rw;
			fscanf(file, "%x %c", %addr, %rw);

			//앞에 10비트로 첫번째 페이지테이블 접근                -> 10비트 일반화 필요
			int firstIndex = addr >> 22;
			int temp = addr << 10;
			int secondIndex = temp >> 22;

			//첫번째페이지엔트리에서 얻은 결과와 10~20번째비트로 두번째페이지테이블 엔트리접근
			if (firstPageEntry[firstIndex])[i].secondLevelPageTable   != NULL) {//두번째페이지테이블 존재
				if ((firstPageEntry[firstIndex])[i].secondLevelPageTable[secondIndex].frameNumber != NULL) {
					procTable[i].numPageHit++;
				}
				else {
					procTable[i].numPageFault++;
				}
			}
			else {
				//두번째 테이블 구성
			}
	
		}
	}
	
	
	for (i = 0; i < numProcess; i++) {
		printf("**** %s *****\n", procTable[i].traceName);
		printf("Proc %d Num of traces %d\n", i, procTable[i].ntraces);
		printf("Proc %d Num of second level page tables allocated %d\n",i,procTable[i].num2ndLevelPageTable);
			printf("Proc %d Num of Page Faults %d\n", i, procTable[i].numPageFault);
		printf("Proc %d Num of Page Hit %d\n", i, procTable[i].numPageHit);
		assert(procTable[i].numPageHit + procTable[i].numPageFault == procTable[i].ntraces);
	}
}
void invertedPageVMSim(struct procEntry *procTable, struct framePage *phyMemFrames, int nFrame) {
	int i;
	for (i = 0; i < numProcess; i++) {
		printf("**** %s *****\n", procTable[i].traceName);
		printf("Proc %d Num of traces %d\n", i, procTable[i].ntraces);
		printf("Proc %d Num of Inverted Hash Table Access Conflicts %d\n",i,procTable[i].numIHTConflictAccess);
		printf("Proc %d Num of Empty Inverted Hash Table Access	%d\n",i,procTable[i].numIHTNULLAccess);
		printf("Proc %d Num of Non-Empty Inverted Hash Table Access %d\n",i,procTable[i].numIHTNonNULLAcess);
		printf("Proc %d Num of Page Faults %d\n", i, procTable[i].numPageFault);
		printf("Proc %d Num of Page Hit %d\n", i, procTable[i].numPageHit);
		assert(procTable[i].numPageHit + procTable[i].numPageFault == procTable[i].ntraces);
		assert(procTable[i].numIHTNULLAccess + procTable[i].numIHTNonNULLAcess == procTable[i].ntraces);
	}
}
int main(int argc, char *argv[]) {
	int i;
	if (argc < 4) {
		printf("Usage : %s firstLevelBits PhysicalMemorySizeBits TraceFileNames\n", argv[0]); exit(1);
	}
	firstLevelBits = argv[1];
	phyMemSizeBits = argv[2];
	int secondLevelBits = 20 - firstLevelBits;
	if (phyMemSizeBits < PAGESIZEBITS) {
		printf("PhysicalMemorySizeBits %d should be larger than PageSizeBits %d\n", phyMemSizeBits, PAGESIZEBITS); exit(1);
	}
	if (VIRTUALADDRBITS - PAGESIZEBITS - firstLevelBits <= 0) {
		printf("firstLevelBits %d is too Big\n", firstLevelBits); exit(1);
	}



	// initialize procTable for two-level page table
	for (i = 0; i < numProcess; i++) {
		// opening a tracefile for the process
		printf("process %d opening %s\n", i, argv[i + 3]);
	}
	int nFrame = (1 << (phyMemSizeBits - PAGESIZEBITS)); assert(nFrame > 0);
	


	//phyMem 동적할당 해주고
	initPhyMem(struct framePage *phyMem, nFrame);    //물리주소공간 초기화

	/*  firstPageTable 프로세스 수만큼 동적할당*/

	
	struct pageTableEntry * firstLevelPage ;    //동적할당
	

	//1st level page table 구성
	for (int i = 0; i < secondVPN; i++) {
		firstLevelPage[i].level = 1;
		firstLevelPage[i].valid = "?";
		struct pageTableEntry *secondLevelPageTable;
	}


	printf("\nNum of Frames %d Physical Memory Size %ld bytes\n", nFrame, (1L << phyMemSizeBits));



	printf("=============================================================\n");
	printf("The 2nd Level Page Table Memory Simulation Starts .....\n");
	printf("=============================================================\n");

	secondLevelVMSim(struct procEntry *procTable, struct framePage *phyMemFrames);
	
	
	
	
	
	
	
	// initialize procTable for the inverted Page Table
	for (i = 0; i < numProcess; i++) {
		// rewind tracefiles
		rewind(procTable[i].tracefp);
	}
	printf("=============================================================\n");
	printf("The Inverted Page Table Memory Simulation Starts .....\n");
	printf("=============================================================\n");
	invertedPageVMSim(struct procEntry *procTable, struct framePage *phyMemFrames, int nFrame);


	return(0);
}