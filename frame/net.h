#ifndef __NET_H__
#define __NET_H__

extern int accept_fd(int sockfd);
extern int setnonbloking(int fd);
extern int init_net();
extern int close_fd(int fd);

#endif
