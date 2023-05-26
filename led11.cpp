#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int gpio_export(unsigned int gpio) {
  int fd, len;
  char buf[64];

  fd = open("/sys/class/gpio/export", O_WRONLY);
  if (fd < 0) {
    perror("gpio/export");
    return fd;
  }
  len = snprintf(buf, sizeof(buf), "%d", gpio);
  write(fd, buf, len);
  close(fd);

  return 0;
}

int gpio_unexport(unsigned int gpio) {
  int fd, len;
  char buf[64];

  fd = open("/sys/class/gpio/unexprot", O_WRONLY);
  if (fd < 0) {
    perror("gpio/export");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%d", gpio);
  write(fd, buf, len);
  close(fd);
  return 0;
}

int gpio_set_dir(unsigned int gpio, std::string dirStatus) {
  int fd;
  char buf[64];
  printf("%d\n",gpio);

  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("gpio/direction");
    return fd;
  }
  if (dirStatus == "out") {
    write(fd, "out", 4);
  } else {
    write(fd, "in", 3);
  }
  close(fd);
  return 0;
}

int gpio_set_value(unsigned int gpio, int value) {
  int fd;
  char buf[64];

  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("gpio/set-value");
    return fd;
  }
  if (value == 0) {
    write(fd, "0", 2);
  } else {
    write(fd, "1", 2);
  }
  close(fd);
  return 0;
}

int main(int argc, char *argv[]) {
  std::map<std::string, int> led = {
      {"LED1", 466},
      {"LED2", 396},
      {"LED3", 429},
      {"LED4", 398},
  };
  std::map<std::string, int> power = {{"on", 1}, {"off", 0}};

  int ledCode = led[argv[1]];
  int powerCode = power[argv[2]];
  gpio_export(ledCode);
  gpio_set_dir(ledCode, "out");
  gpio_set_value(ledCode, powerCode);

  return 0;
}


