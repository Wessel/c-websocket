/* main.c */
/*
  Project description
*/
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <time.h>


#include "../include/utils.h"
/* Libtap for tests */
#include "../include/libtap.h"

#include "../include/ws.h"
#include "../include/json.h"

#include "./events/events.c"

#include "../include/active.h"

size_t connections_size = 100;
int connections_head = 0;
char* connections[100] = {};

#ifdef MAIN
  #define DEBUG 1
#endif

// Define the structure to store the arguments
struct arguments {
  int port;
  int timeout;
};

// Define the argument parser
static struct argp_option options[] = {
  {"port", 'p', "PORT", 0, "Port number"},
  {"timeout", 't', "TIMEOUT", 0, "Timeout in seconds"},
  {0}
};

static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  struct arguments* arguments = state->input;
  switch (key) {
  case 'p':
    arguments->port = atoi(arg);
    break;
  case 't':
    arguments->timeout = atoi(arg);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, 0, 0 };

int main(int argc, char *argv[], char *env[]) {
  struct arguments args;

  // Set default values for the arguments
  args.port = 8080;
  args.timeout = 10;

  // Parse the arguments
  argp_parse(&argp, argc, argv, 0, 0, &args);


  struct ws_events events;
  events.onopen = &onopen;
  events.onclose = &onclose;
  events.onmessage = &onmessage;

  ws_socket(&events, args.port, 0, args.timeout);

  return 0;
}
