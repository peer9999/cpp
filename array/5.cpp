void f(int **&arr, int x, int y) {
    int i, j;
    cout << endl;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                cout << " " << arr[i][j];
            }
        }
    }
}
