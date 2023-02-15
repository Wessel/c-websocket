#include "../../include/ws.h"
#include "../../include/active.h"

void onopen(ws_cli_conn_t* client) {
  char* cli;
  cli = ws_getaddress(client);

  connections[connections_head] = cli;
  connections_head += 1;

  int i = 0;
  while (connections[i] != NULL) {
    printf("\n%s\n", connections[i]);
    i += 1;
  }

  printf("Connection opened to:\t\t%s\n", cli);
}