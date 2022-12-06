#include <unistd.h>

void printf(const char* format, ...) {
  int* args = &format + 1;

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      if (*format == 'd') {
        int i = *args++;
        char buffer[16];
        sprintf(buffer, "%d", i);
        write(1, buffer, strlen(buffer));
      } else if (*format == 's') {
        char* s = (char*)*args++;
        write(1, s, strlen(s));
      }
    } else {
      write(1, format, 1);
    }

    format++;
  }
}

int main()
{
  printf(" %d %s\n",13,"abc");
}