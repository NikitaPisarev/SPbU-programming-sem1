#pragma once

// quick sorting of a segment [leftIndex, rightIndex] in an array
void quickSort(int array[], int leftIndex, int rightIndex);

// Tests
// returns:
// -1 - the first test failed
// -2 - the second test failed
// -3 - third test failed
// 0 - tests passed
int testQuickSort();