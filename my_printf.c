#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int my_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}


int my_puts (char *str) {
    int i = 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return (i);
}


int my_putd(int nb)
{
    int i = 0;
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        i += my_putd(nb / 10);
        i += my_putd(nb % 10);
    } else {
        my_putchar(nb + '0');
        i++;
    }
    return (i);
}



int my_putud (unsigned int nbr) {
    int len = 0;
    if (nbr > 9)
        len += my_putud(nbr / 10);
    return (len + my_putchar(nbr % 10 + '0'));   
}

int my_puto (unsigned int nbr) {
    int len = 0;
    if (nbr > 7)
        len += my_puto(nbr / 8);
    return (len + my_putchar(nbr % 8 + '0'));   
}

int my_putx (unsigned long int nbr) {
    int len = 0;
    if (nbr > 15)
        len += my_putx(nbr / 16);
    if (nbr%16 > 9 && nbr%16 < 16)
        return (len + my_putchar(nbr%16-10 + 'A'));
    else
        return (len + my_putchar(nbr % 16  + '0'));   
}

int my_printf(char * restrict format, ...) {

    va_list ap;
    char *s, c;
    int d;
    unsigned int u;
    intptr_t x;
    int len = 0;

    va_start(ap, format);

    while (*format) {
        if (*format == '%') {
            switch (*++format) {
                case 's':
                    s = va_arg(ap, char *);
                    len += my_puts(s);
                    break;

                case 'd':
                    d = va_arg(ap, int);
                    len += my_putd(d);
                    break;

                case 'c':
                    c = va_arg(ap, int);
                    len += my_putchar(c);
                    break;

                case 'u':
                    u = va_arg(ap, unsigned int);
                    len += my_putud(u);
                    break;

                case 'o':
                    u = va_arg(ap, unsigned int);
                    len += my_puto(u);
                    break;

                case 'x':
                    x = va_arg(ap, intptr_t);
                    len += my_putx(x);
                    break;
                
                case 'p':
                    x = va_arg(ap, intptr_t);
                    len += my_puts("0x") + my_putx(x);
                    break;

                default:
                    len += my_putchar('%');
            }
            format++;
        }
        if (*format != '%') {
            len += my_putchar(*format);
            format++;
        }
    }
    va_end(ap);

    return (len);
}


int main () {
    char * big = "big";
    char * small = "small";
    my_printf("%d\n", my_printf("Hello %s %p\n", big, big));
    printf("%d\n", printf("Hello %s %p\n", big, big));
    my_printf("%d\n", my_printf("Hello %s %p\n", small, small));
    printf("%d\n", printf("Hello %s %p\n", small, small));

    return(0);
}