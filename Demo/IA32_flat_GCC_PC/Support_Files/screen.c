static unsigned int pos = 0;

void screen_clear()
{
	char *pv = (char*)0xb8000;
	unsigned int i;

	for (i = 0; i < 80 * 25 * 2; i += 2) {
		pv[i] = ' ';
		pv[i + 1] = 0x07;
	}
	pos = 0;
}

void screen_putchar(int c)
{
	char *pv = (char*)0xb8000;
	if (pos >= 80 * 25 * 2) screen_clear();
	if (c == '\n') {
		pos = (pos / 160 + 1) * 160;
	}
	else {
		pv[pos] = c;
		pv[pos + 1] = 0x07;
		pos += 2;
	}
}

void screen_puts(const char *s)
{
	unsigned int i;
	for (i = 0; s[i] != '\0'; i++) screen_putchar(s[i]);
}

void screen_puthex(unsigned int x)
{
    char x2c[] = "0123456789abcdef";
    char s[20], *ps;

    if (x == 0) screen_putchar('0');
    else {
        s[19] = '\0';
        ps = s + 18;
        for (; x; x /= 16, ps--) *ps = x2c[x % 16];
        screen_puts(ps + 1);
    }
}
