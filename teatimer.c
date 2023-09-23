#include <errno.h>
#include <libnotify/notify.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void notify(char *notification_text) {
  NotifyNotification *TeaNotification;
  notify_init("Teatimer");
  TeaNotification = notify_notification_new("tea", notification_text, NULL);
  notify_notification_show(TeaNotification, NULL);
  g_object_unref(G_OBJECT(TeaNotification));
  notify_uninit();

  // // TODO: implement better playback
  system("aplay -q ~/Audio/alert.wav");
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    notify("Usage: tea MINUTES [NOTIFICATION]\n");
    exit(EXIT_FAILURE);
  }

  char *endptr;
  errno = 0;
  int minutes = strtol(argv[1], &endptr, 10);
  int seconds = minutes * 60;

  if (errno) {
    notify("strtol conversion error");
    perror("strtol");
    exit(EXIT_FAILURE);
  }

  if (*endptr) {
    notify("Error: No or wrong runtime given");
    exit(EXIT_FAILURE);
  }

  sleep(seconds);
  notify(argv[2]);

  return 0;
}
