#include <errno.h>
#include <libnotify/notify.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *endptr;
  errno = 0;
  int minutes = strtol(argv[1], &endptr, 10);

  if (endptr == argv[1]) {
    // perror("strtol error");	# FIX: returns "Success" on error (errno 0?)
    printf("strtol error");
    exit(EXIT_FAILURE);
  }

  int seconds = minutes * 60;

  sleep(seconds);

  NotifyNotification *notif;
  notify_init("teatimer");
  notif = notify_notification_new("tea", argv[2], NULL);
  notify_notification_show(notif, NULL);
  g_object_unref(G_OBJECT(notif));
  notify_uninit();

  // TODO: implement better playback
  system("aplay -q ~/Audio/alert.wav");
  return 0;
}
