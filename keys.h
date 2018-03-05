#define MAXISZE 256

struct triplet{
 int key;
 char value1[255]; //maximum 256 bytes
 float value2;
 char client_queue_name [MAXISZE];
}
