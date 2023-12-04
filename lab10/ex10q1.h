typedef struct {
    char type;
    int maxWait;
    char* id;
} Student;

typedef struct {
    Student* start;
    Student* end;
    Student* head;
    int capacity;
    int length;
} Ring;

char** parser(void);
Ring* init_ring(void);
Student* init_student(char type, int maxWait, char* id);
void push_front(Ring* ring, Student student);
void push_back(Ring* ring, Student student);
void push_at(Ring* ring, Student student, int pos);
Student* dequeue(Ring* ring);
int dequeue_last(Ring* ring);
void increase_ring_size(Ring* ring);
void print_student(Student* student);
void print_ring(Ring* ring);
void free_ring(Ring* ring);