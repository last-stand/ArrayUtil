typedef struct ArrayUtil ArrayUtil;
struct ArrayUtil {
	void *base;
	int typeSize;
	int length;
};

typedef struct{
char name[3];
int roll;
float percentage;
} student;

int areEqual(ArrayUtil, ArrayUtil);
ArrayUtil create(int , int);
ArrayUtil resize(ArrayUtil, int);
int findIndex(ArrayUtil, void*);
void dispose(ArrayUtil);
typedef int (MatchFunc)(void *, void *);
typedef char* String;
void* findFirst(ArrayUtil, MatchFunc*, void*);
void* findLast(ArrayUtil, MatchFunc*, void*);
int count(ArrayUtil ,MatchFunc*, void*);