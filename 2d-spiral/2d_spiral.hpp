int const kZero = 0;
int const kOne = 1;

bool Term(int a, int b, int c, int d) { return (a < b and c == d); }

int** MakeSpiral(int n) {
  int** massiv = new int*[n];
  int x = kZero;
  int y = kZero;
  int x0 = kZero;
  int y0 = kZero;
  int x1 = kZero;
  int y1 = kZero;
  for (int i = kZero; i < n; i++) {
    massiv[i] = new int[n];
  }
  for (int i = kOne; i <= n * n; i++) {
    massiv[x][y] = i;
    if (Term(y, n - y1 - kOne, x, x0)) {
      y++;
    } else if (Term(y0, y, x, n - x1 - kOne)) {
      y--;
    } else if (Term(x, n - x1 - kOne, y, n - y1 - kOne)) {
      x++;
    } else {
      x--;
    }
    if (((x == x0 + kOne) and (y == y0) and (y0 != n - y1 - kOne))) {
      x0++;
      x1++;
      y0++;
      y1++;
    }
  }
  return massiv;
}