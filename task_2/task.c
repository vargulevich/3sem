/*
Write a duplex pipe implementation.
typedef struct {
  int txd[2]; 
  int rxd[2]; 
} dpipe_t;
1) This pipe should connect some process with his child, for continuous communication.
2) Be careful with opened descriptors.
3) When one process is terminated, the other should also exit.
*/
